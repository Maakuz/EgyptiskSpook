cbuffer LightViewProjection : register (b0)
{
    matrix view;
    matrix projection;
}

cbuffer translation : register(b1)
{
    matrix translation;
}

float4 main( float3 pos : POSITION ) : SV_POSITION
{
    float4 newPos = float4(pos, 1);

    newPos = mul(newPos, translation);
    newPos = mul(newPos, view);
    newPos = mul(newPos, projection);
    return newPos;
}