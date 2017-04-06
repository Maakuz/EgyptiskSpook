struct GSOutput
{
	float4 pos : SV_POSITION;
};

[maxvertexcount(4)]
void main(
	point float4 input[1] : SV_POSITION, 
	inout TriangleStream< GSOutput > output
)
{
	GSOutput element;
	element.pos = input[0];
	output.Append(element);
	element.pos.x + 10;
	output.Append(element);
	element.pos.y - 10;
	output.Append(element);
	element.pos.x - 10;
	output.Append(element);
}