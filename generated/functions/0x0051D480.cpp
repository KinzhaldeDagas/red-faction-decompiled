// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051D480 rf_geomod_face_closest_point_to_point
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mass sampling and inverse inertia,recentering,UV cuts and density,finite epsilon tests,original ECX/stack flow and PE bytes): Thiscall face,point,outXYZ RET8. Signed plane distance roundedF32; project point-normal*distance via vector helpers, assuming unit normal (no normal length division). If projected point passes face projected containment, copy projected XYZ to output. Otherwise seed best point with projection and bestDistanceFLTMAX, traverse circular edges, call56CBA0(point,edgeStart,edgeEnd,outCandidate) and DISCARD its x87 distance return, compute Euclidean point-to-candidate distance F32. Replace best only ORDERED strict smaller, retaining first tie; unordered ignored. Empty ring or no finite improvement leaves plane projection. No plane distance return or face/vertex mutation. Existing float* EAX is
// vector-copy result object in LOCAL stack, not stable out pointer; rely on output side effect.
float *__thiscall rf_geomod_face_closest_point_to_point(float *this, float *lhs, float *destination)
{
  float *v3; // eax
  int v5; // [esp+4h] [ebp-5Ch]
  float v7[3]; // [esp+Ch] [ebp-54h] BYREF
  float v8[3]; // [esp+18h] [ebp-48h] BYREF
  float copy_result[3]; // [esp+24h] [ebp-3Ch] BYREF
  float scaled_result[3]; // [esp+30h] [ebp-30h] BYREF
  float scalar; // [esp+3Ch] [ebp-24h]
  int i; // [esp+40h] [ebp-20h]
  float v13; // [esp+44h] [ebp-1Ch]
  float source[3]; // [esp+48h] [ebp-18h] BYREF
  float out_vector[3]; // [esp+54h] [ebp-Ch] BYREF

  scalar = rf_plane_point_signed_distance(this, lhs);
  v3 = rf_vector_multiply_scalar(this, scaled_result, scalar);
  rf_vector_subtract(lhs, out_vector, v3);
  if ( rf_geomod_face_contains_projected_point(this, (int)out_vector) )
    return rf_vector_copy(destination, copy_result, out_vector);
  v13 = 3.4028235e38;
  rf_vector3_copy_return_destination(source, out_vector);
  for ( i = *((_DWORD *)this + 16); i; i = v5 )
  {
    rf_vector3_closest_point_on_segment(lhs, *(const float **)i, **(const float ***)(i + 20), out_vector);
    scalar = rf_vector_distance(lhs, out_vector);
    if ( v13 > (double)scalar )
    {
      v13 = scalar;
      rf_vector_copy(source, v8, out_vector);
    }
    if ( *(_DWORD *)(i + 20) == *((_DWORD *)this + 16) )
      v5 = 0;
    else
      v5 = *(_DWORD *)(i + 20);
  }
  return rf_vector_copy(destination, v7, source);
}

