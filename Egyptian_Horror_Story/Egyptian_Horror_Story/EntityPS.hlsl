texture2D tex : register(t0);
texture2D shadowMap : register(t1);
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

cbuffer lightVP : register(b2)
{
    //OPTIMERING
    matrix lView;
    matrix lProjection;
}


float4 main(VS_OUT input) : SV_TARGET
{
    float4 lighting = float4(1, 1, 1, 1);
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
        diffuse = lambert * falloff;


        //Creds till Jakob Nyberg för formeln han stal!
        float3 posToCam = camPos.xyz - input.wPos.xyz;
        float3 H = normalize(posToCam - lightDir.xyz);

        specularity = pow(saturate(dot(input.normal.xyz, H)), specularIntensity) * falloff;
    }

    float attenuation = (1.f / (0.01 * max(20, pow(length(lightToPos.xyz), 2))));
    
    diffuse *= attenuation;
    specularity *= attenuation;
    lighting = saturate(diffuse + ambient) + specularity;

    //*******************SHADOW MAPPING FINALLY*********************
    if (falloff > 0)
    {
        float4 posFromLight = input.wPos;

        posFromLight = mul(posFromLight, lView);
        posFromLight = mul(posFromLight, lProjection);

        posFromLight /= posFromLight.w;

	    //Convert to texture coords
        posFromLight.x = (posFromLight.x * 0.5) + 0.5;
        posFromLight.y = (posFromLight.y * -0.5) + 0.5;


        float depth = shadowMap.Sample(sSampler, posFromLight.xy).x;

        if (depth < posFromLight.z - 0.0001)
            lighting *= float4(0.3, 0.3, 0.3, 1);
    }

    //*****************SHADOW MAPPING FINALLY END*******************

    //return shadowMap.Sample(sSampler, input.uv);
    return tex.Sample(sSampler, input.uv) * lighting;
}