//AdjustModel.hlsl

#pragma Target 5.0

RWStructuredBuffer<double> CategoricalCrossEntropyLoss : register(u3);
RWStructuredBuffer<double> WeightsOutput : register(u4);
RWStructuredBuffer<double> BiasOutput : register(u5);
RWStructuredBuffer<double> WeightsHidden : register(u6);
RWStructuredBuffer<double> BiasHidden : register(u7);



[numThreads(1, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    uint index = DTid.x;
    
}