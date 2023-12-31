
struct VTX_IN
{
    float3 vPos : POSITION;
    float4 vColor : COLOR;
    float2 vTex : TEXCOORD0;
};

struct VTX_OUT
{
    float4 vPos : SV_Position;
    float4 vColor : COLOR;
    float2 vTex : TEXCOORD0;
};

cbuffer TRANSFORM : register(b0)
{
    float3 cbPos;
    int padd1;
    float3 cbScale;
    int padd2;
    float4x4 cbRotMat;
};

cbuffer PERSPECTIVE : register(b2)
{
    float4x4 cbWorld;
    float4x4 cbView;
    float4x4 cbProj;
};

VTX_OUT VS_Test(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    output.vPos = float4(_in.vPos, 1.f);
    
    // Scale, Rotate and Translate
    // https://gamedev.stackexchange.com/questions/29260/transform-matrix-multiplication-order
    output.vPos.xyz *= cbScale;
    output.vPos = mul(output.vPos, cbRotMat);
    output.vPos = output.vPos + float4(cbPos, 0.f);

    output.vPos = mul(output.vPos, cbWorld);
    output.vPos = mul(output.vPos, cbView);
    output.vPos = mul(output.vPos, cbProj);
    
    output.vColor = _in.vColor;
    output.vTex = _in.vTex;
    
    return output;
}
