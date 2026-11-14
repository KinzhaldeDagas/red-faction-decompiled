// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581380 rf_clip_special_plane_reject_point
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Returns false if global flag18CD384 clear. Otherwise computes dot(worldPoint-point18CD5DC,normal18CD5F4) and returns true when ordered <=0. Boundary rejected;NaN comparison false. Does not consult ordinary frustum planes or mutate point.
bool __cdecl rf_clip_special_plane_reject_point(float *lhs)
{
  float *v1; // eax
  bool result; // al
  float out_vector[3]; // [esp+0h] [ebp-Ch] BYREF

  result = false;
  if ( dword_18CD384 )
  {
    v1 = rf_vector_subtract(lhs, out_vector, unk_18CD5DC);
    if ( rf_vector_dot(v1, flt_18CD5F4) <= 0.0 )
      return true;
  }
  return result;
}

