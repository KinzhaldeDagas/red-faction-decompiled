// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00569370 rf_point_plane_positive_halfspace_strict
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, sound wrapper ABI, triangle/plane interval tests, strict sphere overlap and retail SAT coefficients): cdecl(point,normal,planePoint),returns byte. Builds local vector point-planePoint then tests dot(vector,normal)>0 with x87 ordered comparison. On-plane equality and unordered/NaN false. No normal normalization,tolerance or output writes.
unsigned __int8 __cdecl rf_point_plane_positive_halfspace_strict(
        const float *point,
        const float *normal,
        const float *plane_point)
{
  float out_vector[3]; // [esp+0h] [ebp-Ch] BYREF

  rf_vector_subtract(point, out_vector, plane_point);
  return rf_vector_dot(out_vector, (float *)normal) > 0.0;
}

