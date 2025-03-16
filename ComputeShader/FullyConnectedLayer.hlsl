//FullyConnectedLayer.hlsl

#pragma Target 5.0

RWStructuredBuffer<double> Input : register(u2);
RWStructuredBuffer<double> Weights : register(u3);
RWStructuredBuffer<double> Output : register(u4);
cbuffer ConstantBuffer : register(b0) {double bias; };
cbuffer ConstantBuffer : register(b1) {bool adjust; };


double ReLU(double x)
{
    if(x > 0.0)
        return x;
    return 0.0;
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

[numThreads(3, 3, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    uint index_inputs = DTid.x;
    uint index_weights_cols = DTid.y;

    if(adjust == true)
    {
        
    }
    else
    {
        double z = LinearTransformation(index_inputs);
        Output[index_inputs] = ReLU(z);
    }
}