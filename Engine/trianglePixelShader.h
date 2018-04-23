#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//
//   fxc /nologo /Emain /T ps_4_0_level_9_3 /Fh trianglePixelShader.h /Fo
//    trianglePixelShader.cso /Vn g_trianglepsshader /Od /Zi
//    src\core\trianglePixelShader.hlsl
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_POSITION              0   xyzw        0      POS  float       
// COLOR                    0   xyz         1     NONE  float   xyz 
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_TARGET                0   xyzw        0   TARGET  float   xyzw
//
//
// Level9 shader bytecode:
//
    ps_2_x
    def c0, 1, 0, 0, 0
    dcl t0.xyz  // input<4,5,6>

#line 7 "D:\work\repos\jonsGitHub\VelocityZero\Engine\src\core\trianglePixelShader.hlsl"
    mul r0, t0.xyzx, c0.xxxy
    add r0, r0, c0.yyyx  // ::main<0,1,2,3>
    mov oC0, r0  // ::main<0,1,2,3>

// approximately 3 instruction slots used
ps_4_0
dcl_input_ps linear v1.xyz
dcl_output o0.xyzw

#line 7 "D:\work\repos\jonsGitHub\VelocityZero\Engine\src\core\trianglePixelShader.hlsl"
mov o0.w, l(1.000000)  // main<3: 1f>
mov o0.xyz, v1.xyzx  // main<0,1,2>
ret 
// Approximately 3 instruction slots used
#endif

const BYTE g_trianglepsshader[] =
{
     68,  88,  66,  67,  63,  27, 
    169, 119, 182, 248, 120, 112, 
     91, 137,  82,  21, 240,  15, 
    156, 123,   1,   0,   0,   0, 
     95,  13,   0,   0,   7,   0, 
      0,   0,  60,   0,   0,   0, 
     88,   2,   0,   0, 172,   2, 
      0,   0,   3,  12,   0,   0, 
    127,  12,   0,   0, 215,  12, 
      0,   0,  43,  13,   0,   0, 
     65, 111, 110,  57,  20,   2, 
      0,   0,  20,   2,   0,   0, 
      0,   2, 255, 255, 240,   1, 
      0,   0,  36,   0,   0,   0, 
      0,   0,  36,   0,   0,   0, 
     36,   0,   0,   0,  36,   0, 
      0,   0,  36,   0,   0,   0, 
     36,   0,   1,   2, 255, 255, 
    254, 255, 101,   0,  68,  66, 
     85,  71,  40,   0,   0,   0, 
     92,   1,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
    120,   0,   0,   0,   5,   0, 
      0,   0, 124,   0,   0,   0, 
      2,   0,   0,   0,  52,   1, 
      0,   0, 164,   0,   0,   0, 
     68,  58,  92, 119, 111, 114, 
    107,  92, 114, 101, 112, 111, 
    115,  92, 106, 111, 110, 115, 
     71, 105, 116,  72, 117,  98, 
     92,  86, 101, 108, 111,  99, 
    105, 116, 121,  90, 101, 114, 
    111,  92,  69, 110, 103, 105, 
    110, 101,  92, 115, 114,  99, 
     92,  99, 111, 114, 101,  92, 
    116, 114, 105,  97, 110, 103, 
    108, 101,  80, 105, 120, 101, 
    108,  83, 104,  97, 100, 101, 
    114,  46, 104, 108, 115, 108, 
      0, 171,  40,   0,   0,   0, 
      0,   0, 255, 255, 156,   1, 
      0,   0,   0,   0, 255, 255, 
    180,   1,   0,   0,   7,   0, 
      0,   0, 192,   1,   0,   0, 
      7,   0,   0,   0, 208,   1, 
      0,   0,   6,   0,   0,   0, 
    224,   1,   0,   0, 109,  97, 
    105, 110,   0, 105, 110, 112, 
    117, 116,   0, 112, 111, 115, 
    105, 116, 105, 111, 110,   0, 
      1,   0,   3,   0,   1,   0, 
      4,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,  99, 111, 
    108, 111, 114,   0, 171, 171, 
      1,   0,   3,   0,   1,   0, 
      3,   0,   1,   0,   0,   0, 
      0,   0,   0,   0, 175,   0, 
      0,   0, 184,   0,   0,   0, 
    200,   0,   0,   0, 208,   0, 
      0,   0,   5,   0,   0,   0, 
      1,   0,   7,   0,   1,   0, 
      2,   0, 224,   0,   0,   0, 
      1,   0,   0,   0,   4,   0, 
      5,   0,   6,   0, 255, 255, 
      1,   0,   3,   0,   1,   0, 
      4,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   1,   0, 
      2,   0,   3,   0,   4,   0, 
      0,   0,   0,   0,   1,   0, 
      2,   0,   3,   0, 164,   0, 
      0,   0, 169,   0,   0,   0, 
    240,   0,   0,   0,   1,   0, 
      0,   0,   0,   1,   0,   0, 
      0,   0,   0,   0, 164,   0, 
      0,   0,  12,   1,   0,   0, 
      2,   0,   0,   0,  28,   1, 
      0,   0,  77, 105,  99, 114, 
    111, 115, 111, 102, 116,  32, 
     40,  82,  41,  32,  72,  76, 
     83,  76,  32,  83, 104,  97, 
    100, 101, 114,  32,  67, 111, 
    109, 112, 105, 108, 101, 114, 
     32,  57,  46,  50,  57,  46, 
     57,  53,  50,  46,  51,  49, 
     49,  49,   0, 171, 171, 171, 
     81,   0,   0,   5,   0,   0, 
     15, 160,   0,   0, 128,  63, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     31,   0,   0,   2,   0,   0, 
      0, 128,   0,   0,   7, 176, 
      5,   0,   0,   3,   0,   0, 
     15, 128,   0,   0,  36, 176, 
      0,   0,  64, 160,   2,   0, 
      0,   3,   0,   0,  15, 128, 
      0,   0, 228, 128,   0,   0, 
     21, 160,   1,   0,   0,   2, 
      0,   8,  15, 128,   0,   0, 
    228, 128, 255, 255,   0,   0, 
     83,  72,  68,  82,  76,   0, 
      0,   0,  64,   0,   0,   0, 
     19,   0,   0,   0,  98,  16, 
      0,   3, 114,  16,  16,   0, 
      1,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   5, 130,  32,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0, 128,  63, 
     54,   0,   0,   5, 114,  32, 
     16,   0,   0,   0,   0,   0, 
     70,  18,  16,   0,   1,   0, 
      0,   0,  62,   0,   0,   1, 
     83,  68,  66,  71,  79,   9, 
      0,   0,  84,   0,   0,   0, 
     42,   1,   0,   0,  91,   1, 
      0,   0,  96,   1,   0,   0, 
      5,   1,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  16,   0, 
      0,   0,  11,   0,   0,   0, 
    180,   4,   0,   0,   3,   0, 
      0,   0, 188,   5,   0,   0, 
      7,   0,   0,   0,   4,   6, 
      0,   0,   3,   0,   0,   0, 
    144,   6,   0,   0,   4,   0, 
      0,   0, 204,   6,   0,   0, 
    124,   7,   0,   0, 148,   7, 
      0,   0,   0,   0,   0,   0, 
     78,   0,   0,   0,  78,   0, 
      0,   0, 186,   0,   0,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 
      3,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  10,   0, 
      0,   0,   0,   0, 128,  63, 
      0,   0, 128,  63,   0,   0, 
    128,  63,   0,   0, 128,  63, 
      0,   0, 128,  63,   0,   0, 
    128,  63,   0,   0,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      6,   0,   0,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
     16,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  54,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   2,   0,   0,   0, 
    255, 255, 255, 255,   7,   0, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0, 128, 255, 255, 255, 127, 
    255, 255, 127, 255, 255, 255, 
    127, 127,   0,   0,   0,   0, 
      0,   0,   0,   0,   8,   0, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0, 128, 255, 255, 255, 127, 
    255, 255, 127, 255, 255, 255, 
    127, 127,   0,   0,   0,   0, 
      0,   0,   0,   0,   9,   0, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0, 128, 255, 255, 255, 127, 
    255, 255, 127, 255, 255, 255, 
    127, 127,   0,   0,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      6,   0,   0,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
     16,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,  62,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      6,   0,   0,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
     16,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      4,   0,   0,   0,   3,   0, 
      0,   0, 255, 255, 255, 255, 
    255, 255, 255, 255,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      4,   0,   0,   0,   3,   0, 
      0,   0, 255, 255, 255, 255, 
    255, 255, 255, 255,   3,   0, 
      0,   0,   1,   0,   0,   0, 
      4,   0,   0,   0,   3,   0, 
      0,   0, 255, 255, 255, 255, 
    255, 255, 255, 255,   3,   0, 
      0,   0,   2,   0,   0,   0, 
      4,   0,   0,   0,   3,   0, 
      0,   0, 255, 255, 255, 255, 
    255, 255, 255, 255,   3,   0, 
      0,   0,   3,   0,   0,   0, 
      4,   0,   0,   0,   3,   0, 
      0,   0, 255, 255, 255, 255, 
    255, 255, 255, 255,   3,   0, 
      0,   0,   4,   0,   0,   0, 
      4,   0,   0,   0,   3,   0, 
      0,   0, 255, 255, 255, 255, 
    255, 255, 255, 255,   3,   0, 
      0,   0,   5,   0,   0,   0, 
      4,   0,   0,   0,   3,   0, 
      0,   0, 255, 255, 255, 255, 
    255, 255, 255, 255,   3,   0, 
      0,   0,   6,   0,   0,   0, 
      5,   0,   0,   0,   3,   0, 
      0,   0, 255, 255, 255, 255, 
    255, 255, 255, 255,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      5,   0,   0,   0,   3,   0, 
      0,   0, 255, 255, 255, 255, 
    255, 255, 255, 255,   2,   0, 
      0,   0,   1,   0,   0,   0, 
      5,   0,   0,   0,   3,   0, 
      0,   0, 255, 255, 255, 255, 
    255, 255, 255, 255,   2,   0, 
      0,   0,   2,   0,   0,   0, 
      5,   0,   0,   0,   3,   0, 
      0,   0, 255, 255, 255, 255, 
    255, 255, 255, 255,   2,   0, 
      0,   0,   3,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      1,   0,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      5,   0,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      1,   0,   0,   0,   1,   0, 
      0,   0, 255, 255, 255, 255, 
      6,   0,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      1,   0,   0,   0,   2,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,   2,   0, 
      0,   0,   8,   0,   0,   0, 
     15,   0,   0,   0,  15,   1, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   8,   0, 
      0,   0,  12,   0,   0,   0, 
     30,   1,   0,   0,   0,   0, 
      0,   0,   6,   0,   0,   0, 
     18,   0,   0,   0,   5,   0, 
      0,   0, 175,   0,   0,   0, 
      0,   0,   0,   0,   6,   0, 
      0,   0,   7,   0,   0,   0, 
      4,   0,   0,   0, 164,   0, 
      0,   0,   0,   0,   0,   0, 
      6,   0,   0,   0,  18,   0, 
      0,   0,   5,   0,   0,   0, 
    175,   0,   0,   0,   0,   0, 
      0,   0,   6,   0,   0,   0, 
      7,   0,   0,   0,   4,   0, 
      0,   0, 164,   0,   0,   0, 
      0,   0,   0,   0,   7,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
     85,   0,   0,   0,   5,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   4,   0, 
      0,   0, 164,   0,   0,   0, 
      4,   0,   0,   0,   1,   0, 
      0,   0,   8,   0,   0,   0, 
      0,   0,   0,   0,   8,   1, 
      0,   0,   7,   0,   0,   0, 
      1,   0,   0,   0,  12,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
      4,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
    255, 255, 255, 255,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   3,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0, 255, 255, 255, 255, 
      3,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   4,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      4,   0,   0,   0,   7,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   7,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,   1,   0,   0,   0, 
      2,   0,   0,   0,  68,  58, 
     92, 119, 111, 114, 107,  92, 
    114, 101, 112, 111, 115,  92, 
    106, 111, 110, 115,  71, 105, 
    116,  72, 117,  98,  92,  86, 
    101, 108, 111,  99, 105, 116, 
    121,  90, 101, 114, 111,  92, 
     69, 110, 103, 105, 110, 101, 
     92, 115, 114,  99,  92,  99, 
    111, 114, 101,  92, 116, 114, 
    105,  97, 110, 103, 108, 101, 
     80, 105, 120, 101, 108,  83, 
    104,  97, 100, 101, 114,  46, 
    104, 108, 115, 108, 115, 116, 
    114, 117,  99, 116,  32,  73, 
    110, 112, 117, 116,  32, 123, 
     13,  10,   9, 102, 108, 111, 
     97, 116,  52,  32, 112, 111, 
    115, 105, 116, 105, 111, 110, 
     32,  58,  32,  83,  86,  95, 
     80,  79,  83,  73,  84,  73, 
     79,  78,  59,  13,  10,   9, 
    102, 108, 111,  97, 116,  51, 
     32,  99, 111, 108, 111, 114, 
     32,  58,  32,  67,  79,  76, 
     79,  82,  59,  13,  10, 125, 
     59,  13,  10,  13,  10, 102, 
    108, 111,  97, 116,  52,  32, 
    109,  97, 105, 110,  40,  73, 
    110, 112, 117, 116,  32, 105, 
    110, 112, 117, 116,  41,  32, 
     58,  32,  83,  86,  95,  84, 
     65,  82,  71,  69,  84, 123, 
     13,  10,   9, 114, 101, 116, 
    117, 114, 110,  32, 102, 108, 
    111,  97, 116,  52,  40, 105, 
    110, 112, 117, 116,  46,  99, 
    111, 108, 111, 114,  46, 114, 
     44,  32, 105, 110, 112, 117, 
    116,  46,  99, 111, 108, 111, 
    114,  46, 103,  44,  32, 105, 
    110, 112, 117, 116,  46,  99, 
    111, 108, 111, 114,  46,  98, 
     44,  32,  49,  41,  59,  13, 
     10, 125,  13,  10,  71, 108, 
    111,  98,  97, 108, 115,  73, 
    110, 112, 117, 116,  58,  58, 
    112, 111, 115, 105, 116, 105, 
    111, 110,  73, 110, 112, 117, 
    116,  58,  58,  99, 111, 108, 
    111, 114,  77, 105,  99, 114, 
    111, 115, 111, 102, 116,  32, 
     40,  82,  41,  32,  72,  76, 
     83,  76,  32,  83, 104,  97, 
    100, 101, 114,  32,  67, 111, 
    109, 112, 105, 108, 101, 114, 
     32,  57,  46,  50,  57,  46, 
     57,  53,  50,  46,  51,  49, 
     49,  49,   0, 109,  97, 105, 
    110,   0, 112, 115,  95,  52, 
     95,  48,   0,  83,  84,  65, 
     84, 116,   0,   0,   0,   3, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   2, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   1,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   2,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,  82,  68,  69,  70,  80, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,  28,   0,   0, 
      0,   0,   4, 255, 255,   5, 
      1,   0,   0,  28,   0,   0, 
      0,  77, 105,  99, 114, 111, 
    115, 111, 102, 116,  32,  40, 
     82,  41,  32,  72,  76,  83, 
     76,  32,  83, 104,  97, 100, 
    101, 114,  32,  67, 111, 109, 
    112, 105, 108, 101, 114,  32, 
     57,  46,  50,  57,  46,  57, 
     53,  50,  46,  51,  49,  49, 
     49,   0, 171, 171, 171,  73, 
     83,  71,  78,  76,   0,   0, 
      0,   2,   0,   0,   0,   8, 
      0,   0,   0,  56,   0,   0, 
      0,   0,   0,   0,   0,   1, 
      0,   0,   0,   3,   0,   0, 
      0,   0,   0,   0,   0,  15, 
      0,   0,   0,  68,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   3,   0,   0, 
      0,   1,   0,   0,   0,   7, 
      7,   0,   0,  83,  86,  95, 
     80,  79,  83,  73,  84,  73, 
     79,  78,   0,  67,  79,  76, 
     79,  82,   0, 171, 171,  79, 
     83,  71,  78,  44,   0,   0, 
      0,   1,   0,   0,   0,   8, 
      0,   0,   0,  32,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   3,   0,   0, 
      0,   0,   0,   0,   0,  15, 
      0,   0,   0,  83,  86,  95, 
     84,  65,  82,  71,  69,  84, 
      0, 171, 171
};
