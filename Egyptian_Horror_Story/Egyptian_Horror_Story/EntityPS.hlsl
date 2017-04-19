texture2D tex : register(t0);
SamplerState sSampler;

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float4 wPos : WORLDPOS;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

cbuffer lightBuffer : register(b0)
{
    float4 lightPos;
    float4 lightDir;
};

cbuffer cameraPos : register(b1)
{
    float4 camPos;
}


float4 main(VS_OUT input) : SV_TARGET
{
    float4 lightToPos = input.wPos - lightPos;
    float specularIntensity = 400.f;
    float outerCone = 0.8f;
    float innerCone = 0.95f;
    float innerMinusOuter = innerCone - outerCone;
    
    float diffuse = 0;
    float specularity = 0;
    float ambient = 0.1;

    //Kanske ska vara negativ
    float cosAngle = dot(normalize(lightToPos.xyz), normalize(lightDir.xyz));

    float falloff = saturate((cosAngle - outerCone) / innerMinusOuter);

    float lambert = max(dot(input.normal, normalize(-lightToPos.xyz)), 0.f);

    if (lambert > 0)
    {
        diffuse = lambert; //* falloff;


        //Skrik på Jakob Nyberg var formeln kommer ifrån!
        float3 posToCam = camPos.xyz - input.wPos.xyz;
       // float3 H = normalize(lightDir.xyz + posToCam); // kanske rättare?
        float3 H = normalize(posToCam - lightDir.xyz);

        specularity = pow(saturate(dot(input.normal.xyz, H)), specularIntensity) * falloff;

        //float3 posToLight = lightPos.xyz - input.wPos.xyz;
        //float3 r = reflect(normalize(posToLight), input.normal.xyz);
        //specularity = pow(dot(normalize(posToCam), normalize(r)), specularIntensity) * falloff;

    }

    return tex.Sample(sSampler, input.uv) * (saturate(diffuse + ambient) + specularity);
}