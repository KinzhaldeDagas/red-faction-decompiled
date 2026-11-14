// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566AA0 rf_mesh144_get_lod_table_radius
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): ECX mesh144 record. Follows DWORD140 pointer and returns its float40 throughST0 as saved double. No sqrt, absolute value, bounds construction, animation or null check.
double __thiscall rf_mesh144_get_lod_table_radius(_DWORD *this)
{
  return *(float *)(*(this + 35) + 40);
}

