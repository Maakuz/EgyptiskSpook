struct GS_OUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEX_COORD;
};

[maxvertexcount(4)]
void main(
	point float4 input[1] : SV_POSITION, 
	inout TriangleStream<GS_OUT> output
)
{
	GS_OUT element = (GS_OUT) 0;
	element.pos = input[0];
	element.uv = float2(0, 1);
	output.Append(element);
	element.pos.y += 0.3f;
	element.uv = float2(0, 0);
	output.Append(element);
	element.pos.y -= 0.3f;
	element.pos.x += 0.3f;
	element.uv = float2(1, 1);
	output.Append(element);
	element.pos.y += 0.3f;
	element.uv = float2(1, 0);
	output.Append(element);
}