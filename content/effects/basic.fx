cbuffer CBufferPerObject {
	float4x4 WVP : WORLDVIEWPROJECTION;
};

Texture2D DiffuseTexture;

SamplerState TrilinearSampler {
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

struct VS_In {
	float4 o_position: POSITION;
	float2 texture_coords: TEXCOORD;
};

struct VS_Out {
	float4 h_position: SV_Position;
	float2 texture_coords: TEXCOORD;
};

VS_Out vertex_shader(VS_In input) {
	VS_Out output = (VS_Out)0;
	output.h_position = mul(input.o_position, WVP);
	output.texture_coords = input.texture_coords;
	return output;
}

float4 pixel_shader(VS_Out input) : SV_Target {
	float4 texel = DiffuseTexture.Sample(TrilinearSampler, input.texture_coords);
	return texel;
}

technique11 main11 {
	pass p0 {
		SetVertexShader(CompileShader(vs_5_0, vertex_shader()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, pixel_shader()));
	}
}