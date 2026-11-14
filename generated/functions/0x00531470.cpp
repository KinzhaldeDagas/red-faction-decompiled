// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00531470 rf_geomod_face_centroid
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): Thiscall face,outXYZ RET4. Zero output, sum ordered corner vertex positions with F32 vector accumulation, count corner ENTRIES as signedDWORD, compute reciprocal(1.0/double(count)) then storeF32 scalar, multiply output components by it. Returns outXYZ through in-place scale helper. Arithmetic mean of corner positions, not area-weighted centroid/AABB center or unique-vertex mean. No empty-ring guard (normally0*infinity ->NaN with masked FP exceptions), no finite/cycle/alias checks; output aliasing source data can change later reads.
float *__thiscall rf_geomod_face_centroid(_DWORD *this, float *a2)
{
  float v3; // [esp+4h] [ebp-14h]
  int v4; // [esp+8h] [ebp-10h]
  int i; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  rf_vector3_zero_return_destination(a2);
  v7 = 0;
  for ( i = *(this + 16); i; i = v4 )
  {
    rf_vector_accumulate(a2, *(float **)i);
    ++v7;
    if ( *(_DWORD *)(i + 20) == *(this + 16) )
      v4 = 0;
    else
      v4 = *(_DWORD *)(i + 20);
  }
  v3 = 1.0 / (double)v7;
  return rf_vector3_scale_in_place_return_self(a2, v3);
}

