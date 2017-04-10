struct VS_IN {
	float3 pos : POSITION;
	float2 dimensions : DIMENSIONS;
};

struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 dimensions : DIMENSIONS;
};

VS_OUT main(VS_IN input) {
	VS_OUT output = (VS_OUT) 0;
	output.pos = float4(input.pos, 1);
	output.dimensions = input.dimensions;
	return output;
}