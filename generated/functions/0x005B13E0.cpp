// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B13E0 rf_aabb_union_componentwise_in_place
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Takes output minXYZ,maxXYZ and input minXYZ,maxXYZ. Independently stores componentwise minimum into each min axis and maximum into each max axis through float helpers; unlike point min-ELSE-max helper, all six stores always occur. EAX has no defined semantic return; corrected saved prototype to void cdecl4. No empty-box/inversion/pointer checks.
void __cdecl rf_aabb_union_componentwise_in_place(float *a1, float *a2, const float *a3, const float *a4)
{
  *a1 = rf_float_minimum_two_values(*a1, *a3);
  a1[1] = rf_float_minimum_two_values(a1[1], a3[1]);
  a1[2] = rf_float_minimum_two_values(a1[2], a3[2]);
  *a2 = rf_float_maximum_two_values(*a2, *a4);
  a2[1] = rf_float_maximum_two_values(a2[1], a4[1]);
  a2[2] = rf_float_maximum_two_values(a2[2], a4[2]);
}

