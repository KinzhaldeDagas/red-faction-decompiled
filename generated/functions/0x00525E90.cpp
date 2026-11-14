// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00525E90 rf_vector_array_find_exact_vec3
// UNREALRED VERIFIED [decal-face-links-20261028]: Dynamic vec3 array count+0,backing+8,stride12. Takes vec3 as three by-value stack components (misleading float,int,int decompiler signature) and compares to each element via0x41C9E0, returns first index or-1. No epsilon tolerance, capacity check or mutation.
int __thiscall rf_vector_array_find_exact_vec3(_DWORD *this, float a2, int a3, int a4)
{
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < *this; ++i )
  {
    if ( rf_vector3_components_equal((float *)(*(this + 2) + 12 * i), &a2) )
      return i;
  }
  return -1;
}

