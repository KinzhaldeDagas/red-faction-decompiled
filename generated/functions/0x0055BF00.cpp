// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055BF00 rf_orientation_matrix_from_normalized_direction
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): ECX output3x3 plus direction pointer, RET4. First uses UNCHECKED normalized-copy558EF0 to fill forward row24. If abs(forward.x)>=~1e-4 OR abs(forward.z)>=~1e-4, right=(forward.z,0,-forward.x) normalized by reciprocal-sqrt helper and up=cross(forward,right). Otherwise snaps forward=(0,signY,0),right=(1,0,0),up=(0,0,-signY). No explicit zero/NaN validation before unchecked normalization. Differs from55C050, which preserves raw forward in general branch.
float *__thiscall rf_orientation_matrix_from_normalized_direction(float *this, float *a2)
{
  float *v2; // eax
  float *v4; // eax
  float v6[3]; // [esp+4h] [ebp-30h] BYREF
  float v7[3]; // [esp+10h] [ebp-24h] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-18h] BYREF
  float v9[3]; // [esp+28h] [ebp-Ch] BYREF

  v2 = rf_vector3_normalized_copy_unchecked(a2, v9);
  rf_vector_copy(this + 6, copy_result, v2);
  if ( *(this + 6) >= 0.00009999999747378752
    || *(this + 6) <= -0.00009999999747378752
    || *(this + 8) >= 0.00009999999747378752
    || *(this + 8) <= -0.00009999999747378752 )
  {
    *this = *(this + 8);
    *(this + 1) = 0.0;
    *(this + 2) = -*(this + 6);
    rf_vector_normalize_reciprocal_sqrt(this);
    v4 = rf_vector_cross(this + 6, v7, this);
    return rf_vector_copy(this + 3, v6, v4);
  }
  else
  {
    *(this + 8) = 0.0;
    *(this + 6) = 0.0;
    *this = 1.0;
    if ( *(this + 7) >= 0.0 )
    {
      *(this + 7) = 1.0;
      *(this + 5) = -1.0;
    }
    else
    {
      *(this + 7) = -1.0;
      *(this + 5) = 1.0;
    }
    *(this + 4) = 0.0;
    *(this + 3) = 0.0;
    *(this + 2) = 0.0;
    *(this + 1) = 0.0;
    return this;
  }
}

