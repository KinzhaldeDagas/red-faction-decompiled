// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00562240 rf_model_handle_get_named_sphere_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): Tag1 returns record at handle.instance4 DWORD96;tag2 returns embedded mesh definition at definition8+6592 DWORD96 (absolute definition6688). Other tags0. No-op vector constructor used by compiler does not initialize that embedded record. Does not inspect animated pose or validate pointers.
int __thiscall rf_model_handle_get_named_sphere_count(_DWORD *this)
{
  if ( *this == 1 )
    return *(_DWORD *)(*(this + 1) + 96);
  if ( *this == 2 )
    return *((_DWORD *)rf_vector3_default_construct_noop((void *)(*(this + 2) + 6592)) + 24);
  return 0;
}

