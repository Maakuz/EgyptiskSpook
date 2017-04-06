struct PS_IN
{
	float4 pos : SV_POSITION;
	float2 uv : TEX_COORD;
};

Texture2D tex : register(t0);
SamplerState sampState : register(s0);

float4 main(PS_IN input) : SV_TARGET
{
	return tex.Sample(sampState, input.uv);
}