// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00525DF0 rf_vector_array_find_or_append_vec3
// UNREALRED VERIFIED [decal-projection-20261028]: Copies three by-value stack components into local vec3, calls lookup0x525E90(this,vec3); existing index>=0 returned unchanged. If lookupnegative calls append0x413270 and returns its result. Equality tolerance/capacity policy belong to helpers; no duplicate insertion on successful lookup.
int __thiscall rf_vector_array_find_or_append_vec3(_DWORD *this, float a2, int a3, int a4)
{
  float v5; // [esp-Ch] [ebp-1Ch] BYREF
  int v6; // [esp-8h] [ebp-18h]
  int v7; // [esp-4h] [ebp-14h]
  _DWORD *v8; // [esp+0h] [ebp-10h]
  int exact_vec3; // [esp+Ch] [ebp-4h]

  v8 = this;
  rf_vector3_copy_return_destination(&v5, &a2);
  exact_vec3 = rf_vector_array_find_exact_vec3(v8, v5, v6, v7);
  if ( exact_vec3 >= 0 )
    return exact_vec3;
  rf_vector3_copy_return_destination(&v5, &a2);
  return rf_vector_array12_append_by_value(v8, v5, v6, v7);
}

