// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005622A0 rf_model_handle_find_named_sphere_prefix
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): Tag1 delegates5B99B0 on instance4;tag2 delegates same helper on definition8+6592; other tags-1. Helper rejects null name and returns first case-insensitive prefix match in44byte named-sphere records; empty name matches first record if count>0. Not node-name or full-equality lookup.
// UNREALRED VERIFIED [combat-named-sphere-binding-20261112]: tag1 instance+4 andtag2 definition+8+19C0 both delegate5B99B0; other tags return-1. First case-insensitive prefix result is model CSPH ordinal, independent of authored override order.
int __thiscall rf_model_handle_find_named_sphere_prefix(_DWORD *this, char *String2)
{
  _DWORD *v2; // eax

  if ( *this == 1 )
    return rf_mesh_find_named_sphere_prefix((_DWORD *)*(this + 1), String2);
  if ( *this != 2 )
    return -1;
  v2 = rf_vector3_default_construct_noop((void *)(*(this + 2) + 6592));
  return rf_mesh_find_named_sphere_prefix(v2, String2);
}

