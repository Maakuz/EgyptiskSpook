texture2D tex : register(t0);
SamplerState sSampler;

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float4 wPos : WORLDPOS;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

cbuffer lightBuffer
{
    float4 lightPos;
    float4 lightDir;
};


float4 main(VS_OUT input) : SV_TARGET
{
    float4 lightToPos = lightPos - input.wPos;
    float specularIntensity = 0.3;

  //  if (length(lightToPos) > 7.f)
    //    return 0;

    //float specularity = pow(saturate(dot(norm.xyz, H)), specularIntensity);

    float diffuse = saturate(dot(normalize(lightToPos.xyz), input.normal) - 0.3);

    return tex.Sample(sSampler, input.uv) * diffuse;
}