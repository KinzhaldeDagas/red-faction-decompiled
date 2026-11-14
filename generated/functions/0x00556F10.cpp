// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556F10 rf_vector3_all_components_strictly_greater
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Returns byte boolean exactly(second.x<first.x && second.y<first.y && second.z<first.z). Strict all-axis comparison, not a lexicographic comparator or box containment test. Equality rejects; used by spatial merge to choose child from incoming center versus child0 minimum.
bool __cdecl rf_vector3_all_components_strictly_greater(float *a1, float *a2)
{
  return *a2 < (double)*a1 && a2[1] < (double)a1[1] && a2[2] < (double)a1[2];
}

