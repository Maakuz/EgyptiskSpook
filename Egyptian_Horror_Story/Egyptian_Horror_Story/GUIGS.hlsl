struct GS_IN {
	float4 pos : SV_POSITION;
	float2 dimensions : DIMENSIONS;
};

struct GS_OUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEX_COORD;
};

[maxvertexcount(4)]
void main(
	point GS_IN input[1] : SV_POSITION,
	inout TriangleStream<GS_OUT> output
)
{
	float w = input[0].dimensions[0], h = input[0].dimensions[1];
	GS_OUT element = (GS_OUT)0;
	element.pos = input[0].pos;
	element.uv = float2(0, 1);
	output.Append(element);
	element.pos.y += h;
	element.uv = float2(0, 0);
	output.Append(element);
	element.pos.y -= h;
	element.pos.x += w;
	element.uv = float2(1, 1);
	output.Append(element);
	element.pos.y += h;
	element.uv = float2(1, 0);
	output.Append(element);
}