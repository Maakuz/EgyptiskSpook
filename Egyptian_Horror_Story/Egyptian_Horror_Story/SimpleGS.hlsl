struct GS_IN {
	float4 pos : SV_POSITION;
	float3 color : COLOR;
};

struct GS_OUT
{
	float4 pos : SV_POSITION;
	float3 color : COLOR;
};

[maxvertexcount(3)]
void main(
	triangle GS_IN input[3] : SV_POSITION, 
	inout TriangleStream< GS_OUT > output
)
{
	GS_OUT element = (GS_OUT) 0;
	for (uint i = 0; i < 3; i++)
	{
		element.pos = input[i].pos;
		element.color = input[i].color;
		output.Append(element);
	}
}