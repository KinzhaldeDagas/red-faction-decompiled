// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00582420 rf_quaternion_from_matrix3x3
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This destination float4,args matrix (reads only first9 floats,translation ignored). Trace=m0+m4+m8. Trace>=0 computes root=sqrt(trace+1),w=root/2,scale=.5/root,x=(m7-m5)*scale,y=(m2-m6)*scale,z=(m3-m1)*scale. Negative trace chooses largest diagonal m0/m4/m8,sets corresponding component sqrt(1+largest-otherTwo)/2,uses symmetric sums for other vector components and matching antisymmetric difference forw. No orthogonalization,clamp of sqrt argument,zero-root guard or final quaternion normalization. Reads/writes interleaved,so arbitrary input/output overlap unsupported. Returns destination;used on affine first9 floats by scene attachment update.
float *__thiscall rf_quaternion_from_matrix3x3(float *this, float *a2)
{
  float v3; // [esp+4h] [ebp-24h]
  float v4; // [esp+8h] [ebp-20h]
  float v5; // [esp+Ch] [ebp-1Ch]
  float v6; // [esp+14h] [ebp-14h]
  int v8; // [esp+1Ch] [ebp-Ch]
  float v9; // [esp+20h] [ebp-8h]
  float v10; // [esp+24h] [ebp-4h]
  float v11; // [esp+24h] [ebp-4h]
  float v12; // [esp+24h] [ebp-4h]
  float v13; // [esp+24h] [ebp-4h]
  float v14; // [esp+24h] [ebp-4h]
  float v15; // [esp+24h] [ebp-4h]
  float v16; // [esp+24h] [ebp-4h]
  float v17; // [esp+24h] [ebp-4h]

  v9 = *a2 + a2[4] + a2[8];
  if ( v9 < 0.0 )
  {
    v8 = *a2 < (double)a2[4];
    if ( a2[3 * v8 + v8] < (double)a2[8] )
      v8 = 2;
    if ( v8 )
    {
      if ( v8 == 1 )
      {
        v4 = a2[4] - (a2[8] + *a2) + 1.0;
        v14 = rf_sqrt_float(v4);
        *(this + 1) = v14 * 0.5;
        v15 = 0.5 / v14;
        *(this + 2) = (a2[5] + a2[7]) * v15;
        *this = (a2[1] + a2[3]) * v15;
        *(this + 3) = (a2[2] - a2[6]) * v15;
      }
      else
      {
        v3 = a2[8] - (*a2 + a2[4]) + 1.0;
        v16 = rf_sqrt_float(v3);
        *(this + 2) = v16 * 0.5;
        v17 = 0.5 / v16;
        *this = (a2[6] + a2[2]) * v17;
        *(this + 1) = (a2[5] + a2[7]) * v17;
        *(this + 3) = (a2[3] - a2[1]) * v17;
      }
    }
    else
    {
      v5 = *a2 - (a2[4] + a2[8]) + 1.0;
      v12 = rf_sqrt_float(v5);
      *this = v12 * 0.5;
      v13 = 0.5 / v12;
      *(this + 1) = (a2[1] + a2[3]) * v13;
      *(this + 2) = (a2[6] + a2[2]) * v13;
      *(this + 3) = (a2[7] - a2[5]) * v13;
    }
  }
  else
  {
    v6 = v9 + 1.0;
    v10 = rf_sqrt_float(v6);
    *(this + 3) = v10 * 0.5;
    v11 = 0.5 / v10;
    *this = (a2[7] - a2[5]) * v11;
    *(this + 1) = (a2[2] - a2[6]) * v11;
    *(this + 2) = (a2[3] - a2[1]) * v11;
  }
  return this;
}

