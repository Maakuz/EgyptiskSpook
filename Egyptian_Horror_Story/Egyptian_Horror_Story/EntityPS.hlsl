struct VS_OUT
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};




float4 main(VS_OUT input) : SV_TARGET
{




	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}