cbuffer LightViewProjection
{
    matrix view;
    matrix projection;
}

float4 main( float3 pos : POSITION ) : SV_POSITION
{
    float4 newPos = float4(pos, 1);

    newPos = mul(newPos, view);
    newPos = mul(newPos, projection);
    return newPos;
}