struct GS_OUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEX_COORD;
};

cbuffer VP : register(b0)
{
	float4x4 world; // identity matrix
	float4x4 view;
	float4x4 projection;
};

float4x4 camera : register(b1);

[maxvertexcount(4)]
void main(
	point float4 input[1] : SV_POSITION, 
	inout TriangleStream<GS_OUT> output
)
{
	float4x4 vpMatrix = mul(view, projection);
	float testSize = .3f;
	float4 pos;
	float4 cameraRight = camera[0], cameraUp = camera[1];

	GS_OUT element = (GS_OUT) 0;

	pos = input[0] + cameraUp * -testSize + cameraRight * -testSize;
	element.pos = mul(pos, vpMatrix);
	element.uv = float2(0, 1);
	output.Append(element);

	pos = input[0] + cameraUp * testSize + cameraRight * -testSize;
	element.pos = mul(pos, vpMatrix);
	element.uv = float2(0, 0);
	output.Append(element);
	
	pos = input[0] + cameraUp * -testSize + cameraRight * testSize;
	element.pos = mul(pos, vpMatrix);
	element.uv = float2(1, 1);
	output.Append(element);

	pos = input[0] + cameraUp * testSize + cameraRight * testSize;
	element.pos = mul(pos, vpMatrix);
	element.uv = float2(1, 0);
	output.Append(element);
}