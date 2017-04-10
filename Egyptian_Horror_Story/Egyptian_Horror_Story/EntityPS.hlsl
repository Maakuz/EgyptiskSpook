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
    float specularIntensity = 3000.f;
    float outerCone = 0.8f;
    float innerCone = 0.94f;
    float innerMinusOuter = innerCone - outerCone;
    
    float diffuse = 0;
    float specularity = 0;
    float ambient = 0.1;

    float cosAngle = dot(-normalize(lightToPos), normalize(lightDir));

    float spot = saturate((cosAngle - outerCone) / innerMinusOuter);

    float lambert = max(dot(input.normal, normalize(lightToPos)), 0.f);

    if (cosAngle > 0.6f)
    {
        diffuse = saturate(dot(normalize(lightToPos.xyz), input.normal) - 0.3); //* spot; //* lambert
       
        float3 cameraToPos = lightPos.xyz - input.wPos.xyz;
        float3 H = normalize(input.normal + cameraToPos);

        specularity = pow(saturate(dot(input.normal.xyz, H)), specularIntensity);  //* spot;
    }





   

    return tex.Sample(sSampler, input.uv) * saturate(diffuse + specularity + ambient);
}