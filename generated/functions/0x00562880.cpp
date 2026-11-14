// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00562880 rf_model_handle_get_bounds_aabb
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): ECX handle plus outMin/outMax, RET8. Forwards indexed bounds5628A0 with index-1; no output reset, return-status interpretation or transform.
int __thiscall rf_model_handle_get_bounds_aabb(_DWORD *this, float *a2, float *a3)
{
  return rf_model_handle_get_indexed_bounds_aabb(this, -1, a2, a3);
}

