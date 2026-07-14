cbuffer CameraBuffer : register(b0)
{
    matrix u_ViewProjection;
};

cbuffer TransformBuffer : register(b1)
{
    matrix u_Transform;
};

Texture2D t_Texture : register(t0);
SamplerState s_Sampler : register(s0);

struct VS_Input
{
    float3 pos : POSITION;
    float4 col : COLOR;
    float2 uv : TEXCOORD;
};

struct PS_Input
{
    float4 pos : SV_POSITION;
    float4 col : COLOR;
    float2 uv : TEXCOORD;
};

PS_Input VS_Main(VS_Input vertex)
{
    PS_Input vsOut;
    vsOut.pos = mul(float4(vertex.pos, 1.0f), u_Transform);
    vsOut.pos = mul(vsOut.pos, u_ViewProjection);
    vsOut.col = vertex.col;
    vsOut.uv = vertex.uv;
    return vsOut;
}

float4 PS_Main(PS_Input pixel) : SV_TARGET
{
    float4 texColor = t_Texture.Sample(s_Sampler, pixel.uv);
    return texColor * pixel.col;
}