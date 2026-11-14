// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005598F0 rf_vector_fast_distance
// UNREALRED VERIFIED [mission-mover-occupancy-20261020] Subtracts the vectors and calls0x558CC0 FAST length, not Euclidean length. Both mover trigger-sphere occupancy helpers use this approximate distance and store the result to float before strict radius comparison.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): Corrected saved VOID signature to cdecl two3-float point pointers,floating ST0 return. Subtracts A-B to local vector,returns FAST approximate length558CC0 unchanged. For sorted absolute components L>=M>=S,helper uses float W=M/4+S/8 then float(L+W+W/2),not Euclidean sqrt(dot). Existing mover-occupancy finding preserved;this return also fixes false x87-input inference in seam matcher5385B0. No source writes or own finite/overflow guard.
double __cdecl rf_vector_fast_distance(const float *a1, const float *a2)
{
  float *v2; // eax
  float out_vector[3]; // [esp+0h] [ebp-Ch] BYREF

  v2 = rf_vector_subtract(a1, out_vector, a2);
  return rf_vector_fast_length(v2);
}

