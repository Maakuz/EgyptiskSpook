TextureCube skyMap;
SamplerState sState;

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float3 texCoord : TEXCOORD;
};

float4 main(VS_OUT input) : SV_Target
{
   // return float4(1, 1, 0, 1);
	return skyMap.Sample(sState, input.texCoord);
}