struct GS_IN {
	float4 pos : SV_POSITION;
	float2 dimensions : DIMENSIONS;
};

struct GS_OUT
{
	float4 pos : SV_POSITION;
	float4 wPos : WORLDPOS;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
};

cbuffer VP : register(b0)
{
	float4x4 world;
	float4x4 view;
	float4x4 projection;
};

float4 camera : register(b1);

[maxvertexcount(4)]
void main(
	point GS_IN input[1] : SV_POSITION, 
	inout TriangleStream<GS_OUT> output
)
{
	float4x4 vpMatrix = mul(view, projection);
	float3 cameraToPos = (input[0].pos - camera).xyz;
	float scalar = saturate(length(cameraToPos) / 2.f);

	float4 right =	normalize(float4(cross(cameraToPos, float3(0, 1, 0)), 0)) * input[0].dimensions.x * scalar;
	float4 up =		normalize(float4(cross(cameraToPos, right.xyz), 0)) * input[0].dimensions.y * scalar;
	float4 pos;

	GS_OUT element = (GS_OUT) 0;
	element.normal = normalize((camera - input[0].pos).xyz);
	// somethign is wrong with the textures
	pos = input[0].pos - up - right;
	element.pos = mul(pos, vpMatrix);
	element.uv = float2(0, 1);
	element.wPos = pos;
	output.Append(element);

	pos = input[0].pos + up - right;
	element.pos = mul(pos, vpMatrix);
	element.uv = float2(0, 0);
	element.wPos = pos;
	output.Append(element);
	
	pos = input[0].pos - up + right;
	element.pos = mul(pos, vpMatrix);
	element.uv = float2(1, 1);
	element.wPos = pos;
	output.Append(element);

	pos = input[0].pos + up + right;
	element.pos = mul(pos, vpMatrix);
	element.uv = float2(1, 0);
	element.wPos = pos;
	output.Append(element);
}