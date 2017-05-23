struct VS_IN
{
    float3 pos : POSITION;
};

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float3 texCoord : TEXCOORD;
};



VS_OUT main(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

	return output;
}