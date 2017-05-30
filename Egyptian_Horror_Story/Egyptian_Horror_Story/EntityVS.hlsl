struct VS_IN
{
    float3 pos : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};


struct VS_OUT
{
    float4 pos : SV_POSITION;
    float4 wPos : WORLDPOS;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

cbuffer VP : register(b0)
{
    matrix view;
    matrix projection;
};

cbuffer translation : register(b1)
{
    matrix translation;
}

VS_OUT main(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

    output.pos = float4(input.pos, 1);
    
    output.pos = mul(output.pos, translation);

    output.wPos = output.pos;

    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);

    output.normal = input.normal;
    output.normal = normalize((float3)mul(float4(input.normal, 0), translation));
    
    output.uv = input.uv;

    return output;
}