Texture2D Texture : register(t0);
sampler TextureSampler : register(s0);

void SpriteVertexShader(inout float4 color : COLOR0,
                        inout float2 texCoord : TEXCOORD0,
                        inout float4 position : SV_Position)
//SV_Position
{
    position = float4(position.x, position.y, position.z, 1);

}


float4 SpritePixelShader(float4 color : COLOR0,
                         float2 texCoord : TEXCOORD0) : SV_Target0
{
    return Texture.Sample(TextureSampler, texCoord) * color;
}
