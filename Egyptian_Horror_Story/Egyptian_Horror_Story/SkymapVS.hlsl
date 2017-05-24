struct VS_IN
{
    float3 pos : POSITION;
};

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float3 texCoord : TEXCOORD;
};

cbuffer VP : register(b0)
{
    matrix view;
    matrix projection;
};

cbuffer transformBuffer : register(b1)
{
    matrix transform;
};

VS_OUT main(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

    output.pos = float4(input.pos, 1);
    
    output.pos = mul(output.pos, transform);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection).xyww;

    output.texCoord = input.pos;

	return output;
}