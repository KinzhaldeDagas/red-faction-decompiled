// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BCF50 rf_particle_compare_age_descending
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): qsort comparator for36-byte particle records: returns-1 if B.age<A.age,0 if equal,otherwise1. Thus descending age,with free age-1 slots normally last. Float NaNs can violate comparator ordering; no stable-sort guarantee or secondary key.
int __cdecl rf_particle_compare_age_descending(float *a1, float *a2)
{
  float v3; // [esp+0h] [ebp-8h]
  float v4; // [esp+4h] [ebp-4h]

  v4 = *a1;
  v3 = *a2;
  if ( v3 >= (double)v4 )
    return v3 != v4;
  else
    return -1;
}

