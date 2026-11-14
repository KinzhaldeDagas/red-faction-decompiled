// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B8BA0 rf_v3c_asset_release_owned_arrays
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Releases/nulls descriptor pointers+76(mesh144 array via deleting destructor flags3),+84(mesh metadata100 array),+92(aux100),+100(spheres44),+108(vector pool),+116(record52 pool),+124(material200 array),+132(vector pool),+136(index pool). Plain pools use operator delete, owning arrays use their deletion adapters. Does not reset scalar counts, name, field+140 or selected-mesh+144. Returns owner pointer bits; repeated use of stale scalar counts is not prevented here.
int __thiscall rf_v3c_asset_release_owned_arrays(int this)
{
  int result; // eax
  char *v3; // [esp+1Ch] [ebp-24h]
  char *v4; // [esp+34h] [ebp-Ch]
  char *v5; // [esp+3Ch] [ebp-4h]

  if ( *(_DWORD *)(this + 76) )
  {
    v5 = *(char **)(this + 76);
    if ( v5 )
      rf_model_mesh144_deleting_destructor(v5, 3);
  }
  *(_DWORD *)(this + 76) = 0;
  if ( *(_DWORD *)(this + 84) )
  {
    v4 = *(char **)(this + 84);
    if ( v4 )
      rf_v3c_mesh_metadata100_deleting_destructor(v4, 3);
  }
  *(_DWORD *)(this + 84) = 0;
  if ( *(_DWORD *)(this + 92) )
    operator delete(*(void **)(this + 92));
  *(_DWORD *)(this + 92) = 0;
  if ( *(_DWORD *)(this + 100) )
    operator delete(*(void **)(this + 100));
  *(_DWORD *)(this + 100) = 0;
  if ( *(_DWORD *)(this + 108) )
    operator delete(*(void **)(this + 108));
  *(_DWORD *)(this + 108) = 0;
  if ( *(_DWORD *)(this + 116) )
    operator delete(*(void **)(this + 116));
  *(_DWORD *)(this + 116) = 0;
  if ( *(_DWORD *)(this + 124) )
  {
    v3 = *(char **)(this + 124);
    if ( v3 )
      rf_material200_vector_deleting_destructor(v3, 3);
  }
  *(_DWORD *)(this + 124) = 0;
  if ( *(_DWORD *)(this + 132) )
    operator delete(*(void **)(this + 132));
  result = this;
  *(_DWORD *)(this + 132) = 0;
  if ( *(_DWORD *)(this + 136) )
    operator delete(*(void **)(this + 136));
  *(_DWORD *)(this + 136) = 0;
  return result;
}

