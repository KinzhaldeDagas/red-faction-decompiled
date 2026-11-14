// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00559890 rf_vector_distance
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Cdecl two3-float point pointers. Builds local A-B via vector subtract,passes that vector to length helper,returns its floating Euclidean length in ST0 unchanged. Existing VOID prototype incorrect:callers consume ST0,e.g.box-volume580CE5 stores returned distance and multiplies density integral. No source writes or output vector parameter;no own finite/overflow guard. Existing return description preserved;corrected floating ABI prevents bogus uninitialized-ST0 pseudocode.
double __cdecl rf_vector_distance(const float *a1, const float *a2)
{
  float *v2; // eax
  float out_vector[3]; // [esp+0h] [ebp-Ch] BYREF

  v2 = rf_vector_subtract(a1, out_vector, a2);
  return rf_vector3_length(v2);
}

