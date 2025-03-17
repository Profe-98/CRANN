//CategoricalCrossEntropyLoss.hlsl

#pragma Target 5.0

RWStructuredBuffer<double> Predictions : register(u7);
RWStructuredBuffer<double> Actuals : register(u8);
RWStructuredBuffer<double> CategoricalCrossEntropy : register(u9);
void CalculateCCE()
{
    uint c;
    double loss = 0.0;
    for(c = 0; c < 3; ++c)
    {
        loss +=  -1*(Actuals[c]*log(Predictions[c]));
    }
    CategoricalCrossEntropy[0] = loss;
}

[numThreads(1, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    CalculateCCE();
}