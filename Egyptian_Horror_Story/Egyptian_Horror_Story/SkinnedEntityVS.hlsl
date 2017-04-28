struct VS_IN
{
    float3 pos : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
    float4 weight : WEIGHT;
    int4 jointIndex : INDEX;
};


struct VS_OUT
{
    float4 pos : SV_POSITION;
    float4 wPos : WORLDPOS;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

cbuffer WVP : register(b0)
{
    matrix world;
    matrix view;
    matrix projection;
};

cbuffer skeleton : register(b1)
{
    int parent[100];
    matrix globalBindInv[100];
}


VS_OUT main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0;

    float4 newPos;
    float3 newNorm;

    int i = input.jointIndex.x;

    newPos.x = mul(globalBindInv[i], float4(input.pos, 1)) * input.weight.x;
   
    i = input.jointIndex.y;
    newPos.y = mul(globalBindInv[i], float4(input.pos, 1)) * input.weight.y;
    
    i = input.jointIndex.z;
    newPos.z = mul(globalBindInv[i], float4(input.pos, 1)) * input.weight.z;
   
    i = input.jointIndex.w;
    newPos.w = mul(globalBindInv[i], float4(input.pos, 1)) * input.weight.w;

    output.pos = float4(input.pos, 1);

    output.pos = mul(output.pos, world);
    
    output.wPos = output.pos;

    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);

    output.normal = input.normal;
    output.uv = input.uv;

    return output;
}