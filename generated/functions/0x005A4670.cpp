// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A4670 rf_cubic_bezier_evaluate_position
// UNREALRED VERIFIED [cutscene-playback-20261028]: When output vec3 nonnull, zeroes output then sums four control-point vec3 pointers at this+48/+52/+56/+60 weighted by0x5A44A0(i,t). No t clamp or control-pointer validity checks. Output/control storage aliasing is not protected: output is zeroed before reading control points. Return is incidental loop index/address and not a pointer/status contract; null output makes no stores.
float *__thiscall rf_cubic_bezier_evaluate_position(float **this, float *a2, float a3)
{
  float *result; // eax
  float v5; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  if ( a2 )
  {
    result = rf_vector3_zero_return_destination(a2);
    for ( i = 0; i < 4; ++i )
    {
      v5 = rf_cubic_bezier_bernstein_basis(i, a3);
      *a2 = **(this + i + 12) * v5 + *a2;
      a2[1] = (*(this + i + 12))[1] * v5 + a2[1];
      a2[2] = (*(this + i + 12))[2] * v5 + a2[2];
      result = (float *)(i + 1);
    }
  }
  return result;
}

