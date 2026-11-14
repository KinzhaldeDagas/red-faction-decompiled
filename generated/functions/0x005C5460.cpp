// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C5460 rf_renderer_project_clip_vertex_cached
// UNREALRED VERIFIED [renderer-overlays-20261028]: If flagsbyte+25 has either bit1(projected) or bit2(rejected),returns flags unchanged. With byte0x663F06 set and cameraZ<=0,ORs rejectedbit2 and does not project. Otherwise ORs projectedbit1,sets reciprocalZ+20 to1/z or FLT_MAX for z0. Captures that reciprocal locally; if globaldepthbias0x1E014E0 nonzero and z>20*bias,replaces stored reciprocal with1/(z-bias),but screenXY still uses ORIGINAL reciprocal. Computes normalizedx=x/z+1,y=1-y/z; with0x663F06 clamps each0..2. Stores screenX+12=normalizedx*0x18CD1C8+viewportX0x187CCBC,screenY+16=normalizedy*0x18CD290+viewportY0x187CCC0. Returns full flagsbyte. Does not refresh outcode or cameraXYZ; cached flags suppress recalculation after position changes.
char __cdecl rf_renderer_project_clip_vertex_cached(int a1)
{
  float v2; // [esp+0h] [ebp-1Ch]
  float v3; // [esp+4h] [ebp-18h]
  float v4; // [esp+8h] [ebp-14h]
  float v5; // [esp+Ch] [ebp-10h]
  float v6; // [esp+10h] [ebp-Ch]
  float v7; // [esp+14h] [ebp-8h]
  float v8; // [esp+18h] [ebp-4h]

  if ( (*(_BYTE *)(a1 + 25) & 3) != 0 )
    return *(_BYTE *)(a1 + 25);
  if ( byte_663F06 && *(float *)(a1 + 8) <= 0.0 )
  {
    *(_BYTE *)(a1 + 25) |= 2u;
  }
  else
  {
    *(_BYTE *)(a1 + 25) |= 1u;
    if ( *(float *)(a1 + 8) == 0.0 )
      *(float *)(a1 + 20) = 3.4028235e38;
    else
      *(float *)(a1 + 20) = 1.0 / *(float *)(a1 + 8);
    v6 = *(float *)(a1 + 20);
    if ( unk_1E014E0 != 0.0 && *(float *)(a1 + 8) > unk_1E014E0 * 20.0 )
      *(float *)(a1 + 20) = 1.0 / (*(float *)(a1 + 8) - unk_1E014E0);
    v7 = *(float *)a1 * v6 + 1.0;
    v8 = 1.0 - *(float *)(a1 + 4) * v6;
    if ( byte_663F06 )
    {
      if ( v7 <= 0.0 )
        v5 = 0.0;
      else
        v5 = *(float *)a1 * v6 + 1.0;
      if ( v5 >= 2.0 )
        v4 = 2.0;
      else
        v4 = v5;
      v7 = v4;
      if ( v8 <= 0.0 )
        v3 = 0.0;
      else
        v3 = 1.0 - *(float *)(a1 + 4) * v6;
      if ( v3 >= 2.0 )
        v2 = 2.0;
      else
        v2 = v3;
      v8 = v2;
    }
    *(float *)(a1 + 12) = v7 * unk_18CD1C8 + (double)unk_187CCBC;
    *(float *)(a1 + 16) = v8 * unk_18CD290 + (double)unk_187CCC0;
  }
  return *(_BYTE *)(a1 + 25);
}

