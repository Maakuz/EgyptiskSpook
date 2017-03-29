struct VS_IN {
	float3 pos : POSITION;
	float3 color : COLOR;
};

struct VS_OUT {
	float4 pos : SV_POSITION;
	float3 color : COLOR;
};

cbuffer WVP
{
    matrix world;
    matrix view;
    matrix projection;
};

VS_OUT main( VS_IN input )
{
	VS_OUT output = (VS_OUT) 0;
	output.pos = float4(input.pos, 1.0f);
    output.pos = mul(output.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
	output.color = input.color;
	return output;
}