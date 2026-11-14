// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005826E0 rf_quaternion_set_from_matrix3_normalized_legacy
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Thiscall output quaternion(x,y,z,w),source row-major matrix m[0..8]. trace=m0+m4+m8;ordered trace>=0 uses s=sqrt(trace+1),w=s/2,xyz=(m7-m5,m2-m6,m3-m1)*(.5/s). Negative trace selects fallback:if m0<m4 picksY unless m8>m4 picksZ;otherwise startsX but STILL picksZ when m8>m4,without comparing m8 with m0. X:radicand=m0-m4-m8+1,x=s/2,others=(m1+m3,m6+m2,m7-m5)*.5/s into y,z,w. Y:radicand=m4-m8-m0+1,y=s/2,others=(m5+m7,m1+m3,m2-m6)*.5/s into z,x,w. Z:actual radicand=m8-(m1+m4)+1 (OFF-DIAGONAL m1,not m0);z=s/2,others=(m6+m2,m5+m7,m3-m1)*.5/s into x,y,w. Both selector/radicand quirks verified in original instructions. Finally normalizes output through unchecked5832E0 and returns receiver. No
// orthogonality,determinant,negative-root,zero divisor or source/output overlap guard;not safe to replace by a corrected standard conversion.
float *__thiscall rf_quaternion_set_from_matrix3_normalized_legacy(float *this, float *a2)
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
    v8 = 0;
    if ( *a2 >= (double)a2[4] )
    {
      if ( a2[4] < (double)a2[8] )
        v8 = 2;
    }
    else
    {
      v8 = 1;
      if ( a2[4] < (double)a2[8] )
        v8 = 2;
    }
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
        v3 = a2[8] - (a2[1] + a2[4]) + 1.0;
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
  rf_quaternion_normalize_in_place_unchecked(this);
  return this;
}

