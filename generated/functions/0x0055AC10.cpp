// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055AC10 rf_matrix3_extract_euler_angles_retail
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): ECX matrix plus outPitch,outBank,outHeading, RET12. Heading=customatan(m6,m8), except both0 gives0. Letsh=sinHeading,ch=cosHeading: d=m8*ch ifabs(ch)>=abs(sh),else m6*sh. This MULTIPLICATION is original behavior, not division/hypot reconstruction of cosPitch. Pitch=customatan(-m7,d) unless both0. Bank0 ifd==0;else customatan(m1/d,m4/d), with both0→0. Uses custom ratio atan helper, not standard atan2. No orthonormality validation, alias protection or output null checks.
void __thiscall rf_matrix3_extract_euler_angles_retail(float *this, float *a2, float *a3, float *a4)
{
  double v4; // st7
  float v5; // [esp+0h] [ebp-28h]
  float v6; // [esp+8h] [ebp-20h]
  float v7; // [esp+Ch] [ebp-1Ch]
  float v9; // [esp+14h] [ebp-14h]
  float v10; // [esp+18h] [ebp-10h]
  float v11; // [esp+1Ch] [ebp-Ch]
  float v12; // [esp+20h] [ebp-8h]
  float v13; // [esp+24h] [ebp-4h]

  if ( *(this + 6) == 0.0 && *(this + 8) == 0.0 )
    *a4 = 0.0;
  else
    *a4 = rf_atan_ratio_with_negative_x_pi_adjustment(*(this + 6), *(this + 8));
  v11 = rf_sin_float(*a4);
  v12 = rf_cos_float(*a4);
  v7 = fabs(v11);
  v6 = fabs(v12);
  if ( v6 >= (double)v7 )
    v4 = *(this + 8) * v12;
  else
    v4 = *(this + 6) * v11;
  v13 = v4;
  if ( v13 == 0.0 && *(this + 7) == 0.0 )
  {
    *a2 = 0.0;
  }
  else
  {
    v5 = -*(this + 7);
    *a2 = rf_atan_ratio_with_negative_x_pi_adjustment(v5, v13);
  }
  if ( v13 == 0.0 )
  {
    *a3 = 0.0;
  }
  else
  {
    v9 = *(this + 1) / v13;
    v10 = *(this + 4) / v13;
    if ( v9 == 0.0 && v10 == 0.0 )
      *a3 = 0.0;
    else
      *a3 = rf_atan_ratio_with_negative_x_pi_adjustment(v9, v10);
  }
}

