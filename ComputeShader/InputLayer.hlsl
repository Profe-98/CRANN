//InputLayer.hlsl

#pragma Target 5.0

RWStructuredBuffer<double> InputRGB : register(u0);
RWStructuredBuffer<double> OutputRGB : register(u1);

[numThreads(3, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    uint index = DTid.x;
    OutputRGB[index] = InputRGB[index];
}