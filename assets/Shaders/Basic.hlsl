struct VS_Input
{
    float3 pos : POSITION;
    float4 col : COLOR;
};

struct PS_Input
{
    float4 pos : SV_POSITION;
    float4 col : COLOR;
};

PS_Input VS_Main(VS_Input vertex)
{
    PS_Input vsOut;
    vsOut.pos = float4(vertex.pos, 1.0f);
    vsOut.col = vertex.col;
    return vsOut;
}

float4 PS_Main(PS_Input pixel) : SV_TARGET
{
    return pixel.col;
}