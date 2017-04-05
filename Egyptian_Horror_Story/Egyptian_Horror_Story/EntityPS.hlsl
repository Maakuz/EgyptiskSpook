texture2D tex : register(t0);
SamplerState sSampler;

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};




float4 main(VS_OUT input) : SV_TARGET
{
    return tex.Sample(sSampler, input.uv);
}