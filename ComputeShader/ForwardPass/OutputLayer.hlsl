//OutputLayer.hlsl

#pragma Target 5.0

RWStructuredBuffer<double> Input : register(u5);
RWStructuredBuffer<double> Weights : register(u6);
RWStructuredBuffer<double> Predictions : register(u7);
RWStructuredBuffer<double> Actuals : register(u8);
cbuffer ConstantBuffer : register(b2) { double bias; };
cbuffer ConstantBuffer : register(b2) { double learningrate; };

void SoftMax()
{
    double e = 2.718281828459; //2, 718 281 828 459 045 235 360 287 471 352
    double exp_sum = 0.0;
    for(uint iter = 0; iter < 3; ++iter)
    {
        exp_sum += pow(e, Predictions[iter]);
    }
    for(uint iter2 = 0; iter2 < 3; ++iter)
    {
        Predictions[iter] = Predictions[iter] / exp_sum;
    }

}


double LinearTransformation(uint j) // Matrix multiplication can be applied here.
{
    double val = bias;
    uint k = 0;

    while(k < 6)
    {
        val += Input[k/3] * Weights[j+k];
        k += 3;
    }
    return val;
}


[numThreads(3, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    uint index_inputs = DTid.x;

    double zi = LinearTransformation(index_inputs);
    Predictions[index_inputs] = zi;
    if(index_inputs == 3)
    {
        SoftMax();
    }
}