TextureCube skyMap;
SamplerState sState;

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float3 texCoord : TEXCOORD;
};

cbuffer fadeoutBuffer : register(b4)
{
    float fadeout;
}

float4 main(VS_OUT input) : SV_Target
{
	return skyMap.Sample(sState, input.texCoord) * fadeout;
}