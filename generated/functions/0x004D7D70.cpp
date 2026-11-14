// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D7D70 rf_euler_angles_add_clamp_pitch_wrap_once
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion integration, selected-row transforms, angular/tensor updates, contact velocity response and x87 gates): Cdecl(outVector,lhsVector,rhsVector,byteWrapPitch);adds all3components into locals before final copy,returnsoutVector. If low-byte mode nonzero,first component wraps by ONE subtract/add6.2831854820251465 when strictly ORDERED outside inclusive+-constant. Mode0 clamps first component to+-1.5707963705062866,ORDERED comparisons only. ComponentsY/Z always same ONE-step revolution wrap. No loop/fmod;large values can remain far outside range. Equality/NaN remain unchanged;infinities remain infinite on wrap path but clamp to limits on pitch-clamp path. Output can alias either input because addition staged. No pointer/finite checks;native integer MOVZX of low-byte mode.
float *__cdecl rf_euler_angles_add_clamp_pitch_wrap_once(float *a1, float *lhs, float *rhs, char a4)
{
  float sum_result; // [esp+0h] [ebp-Ch] BYREF
  float v6; // [esp+4h] [ebp-8h]
  float v7; // [esp+8h] [ebp-4h]

  rf_vector_add(lhs, &sum_result, rhs);
  if ( a4 )
  {
    if ( sum_result <= 6.283185482025146 )
    {
      if ( sum_result < -6.283185482025146 )
        sum_result = sum_result + 6.283185482025146;
    }
    else
    {
      sum_result = sum_result - 6.283185482025146;
    }
  }
  else if ( sum_result <= 1.570796370506287 )
  {
    if ( sum_result < -1.570796370506287 )
      sum_result = -1.5707964;
  }
  else
  {
    sum_result = 1.5707964;
  }
  if ( v6 <= 6.283185482025146 )
  {
    if ( v6 < -6.283185482025146 )
      v6 = v6 + 6.283185482025146;
  }
  else
  {
    v6 = v6 - 6.283185482025146;
  }
  if ( v7 <= 6.283185482025146 )
  {
    if ( v7 < -6.283185482025146 )
      v7 = v7 + 6.283185482025146;
  }
  else
  {
    v7 = v7 - 6.283185482025146;
  }
  rf_vector3_copy_return_destination(a1, &sum_result);
  return a1;
}

