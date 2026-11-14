// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055ADA0 rf_matrix3_extract_axis_angle
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): ECX matrix plus outAxisXYZ,outAngle, RET8. c=(trace-1)/2. Ifc>float0.9999998807907104 writes angle0,axisunitX. Ifc<=negative threshold writes anglefloatpi, picks greatest diagonal (X wins ties), sets selected axis component sqrt(diagonal+1), other components from selected ROW divided by it, then unchecked-normalizes axis. Otherwise angle=acos(c),axis=(m5-m7,m6-m2,m1-m3),unchecked normalize. No clamp/orthonormality/denominator guard; NaN follows unordered comparisons as instructions dictate.
float *__thiscall rf_matrix3_extract_axis_angle(float *this, float *a2, float *a3)
{
  float v4; // [esp+Ch] [ebp-20h]
  float v5; // [esp+10h] [ebp-1Ch]
  float v6; // [esp+14h] [ebp-18h]
  int v8; // [esp+20h] [ebp-Ch]
  float v9; // [esp+24h] [ebp-8h]
  float v10; // [esp+28h] [ebp-4h]

  v9 = *this + *(this + 4) + *(this + 8);
  v10 = (v9 - 1.0) * 0.5;
  if ( v10 <= 0.9999998807907104 )
  {
    if ( v10 <= -0.9999998807907104 )
    {
      *a3 = 3.1415927;
      v8 = 0;
      if ( *this >= (double)*(this + 4) )
      {
        if ( *this < (double)*(this + 8) )
          v8 = 2;
      }
      else
      {
        v8 = 1;
        if ( *(this + 4) < (double)*(this + 8) )
          v8 = 2;
      }
      if ( v8 )
      {
        if ( v8 == 1 )
        {
          v5 = *(this + 4) + 1.0;
          a2[1] = rf_sqrt_float(v5);
          *a2 = *(this + 3) / a2[1];
          a2[2] = *(this + 5) / a2[1];
        }
        else
        {
          v4 = *(this + 8) + 1.0;
          a2[2] = rf_sqrt_float(v4);
          *a2 = *(this + 6) / a2[2];
          a2[1] = *(this + 7) / a2[2];
        }
      }
      else
      {
        v6 = *this + 1.0;
        *a2 = rf_sqrt_float(v6);
        a2[1] = *(this + 1) / *a2;
        a2[2] = *(this + 2) / *a2;
      }
      return rf_vector_normalize_reciprocal_sqrt(a2);
    }
    else
    {
      *a3 = rf_acos_float(v10);
      *a2 = *(this + 5) - *(this + 7);
      a2[1] = *(this + 6) - *(this + 2);
      a2[2] = *(this + 1) - *(this + 3);
      return rf_vector_normalize_reciprocal_sqrt(a2);
    }
  }
  else
  {
    *a3 = 0.0;
    return rf_vector3_set_components_thiscall(a2, 1.0, 0.0, 0.0);
  }
}

