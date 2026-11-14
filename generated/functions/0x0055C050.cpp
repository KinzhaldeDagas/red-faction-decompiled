// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055C050 rf_orientation_matrix_from_direction
// UNREALRED VERIFIED [combat-particle-emission-20261104]: Correction to orthonormal wording: general branch DOES NOT normalize supplied forward row2. It preserves raw forward, normalizes right=(forward.z,0,-forward.x), and sets up=cross(forward,right), so nonunit forward produces nonunit up/output. If abs(forward.x)<1e-4 and abs(forward.z)<1e-4, snap forward to(0,signY,0), right=(1,0,0), up=(0,0,-signY); zero chooses sign+. RF-to-UE converted basis right=(-axisUE.y,axisUE.x,0), up=cross(axisUE,right). This basis also affects jitter with raw push-region axes.
float *__thiscall rf_orientation_matrix_from_direction(float *this, float *source)
{
  float *v3; // eax
  float v5[3]; // [esp+4h] [ebp-24h] BYREF
  float v6[3]; // [esp+10h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-Ch] BYREF

  rf_vector_copy(this + 6, copy_result, source);
  if ( *(this + 6) >= 0.00009999999747378752
    || *(this + 6) <= -0.00009999999747378752
    || *(this + 8) >= 0.00009999999747378752
    || *(this + 8) <= -0.00009999999747378752 )
  {
    *this = *(this + 8);
    *(this + 1) = 0.0;
    *(this + 2) = -*(this + 6);
    rf_vector_normalize_reciprocal_sqrt(this);
    v3 = rf_vector_cross(this + 6, v6, this);
    return rf_vector_copy(this + 3, v5, v3);
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

