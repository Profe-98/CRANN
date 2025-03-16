//OutputLayer.hlsl

#pragma Target 5.0

RWStructuredBuffer<double> Input : register(u5);
RWStructuredBuffer<double> Weights : register(u6);
RWStructuredBuffer<double> Output : register(u7);
RWStructuredBuffer<double> actuals : register(u8);
cbuffer ConstantBuffer : register(b2) { double bias; };
cbuffer ConstantBuffer : register(b2) { double learningrate; };

void GradientDescent(double err, uint row)
{
    uint c; 
    for(c = 0; c < 3; ++c)
    {

    }
}

void SoftMax()
{
    double e = 2.718281828459; //2, 718 281 828 459 045 235 360 287 471 352
    double exp_sum = 0.0;
    for(uint iter = 0; iter < 3; ++iter)
    {
        exp_sum += pow(e, Output[iter]);
    }
    for(uint iter2 = 0; iter2 < 3; ++iter)
    {
        Output[iter] = Output[iter] / exp_sum;
    }

}


double LinearTransformation(uint j) // Matrix multiplication can be applied here.
{
    double val = 0.0;
    uint k = 0;

    while(k < 6)
    {
        val += Input[k/3] * Weights[j+k];
        k += 3;
    }
    return val + bias;
}


[numThreads(3, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    uint index_inputs = DTid.x;

    double zi = LinearTransformation(index_inputs);
    Output[index_inputs] = zi;
    if(index_inputs == 3)
    {
        SoftMax();
    }
    //double error = CalculateError(prediction, actuals[index_inputs]);
}