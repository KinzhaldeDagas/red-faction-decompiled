// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566360 rf_model_instance_render_data_size
// UNREALRED VERIFIED [resource-pools-20261028]: Kind1 model uses descriptor data pointer+4; kind2 uses derived record+8+6592 through no-op constructor; other kinds return0. For each submesh adds16 bytes, then for each mesh record accumulates3*vertex-count(u16 at polygon-batch+40) across u16 batch count+12 and56-byte entries. Returns integer sum; no overflow checks. Level allocator currently accepts kind1 only.
int __cdecl rf_model_instance_render_data_size(_DWORD *a1)
{
  int k; // [esp+4h] [ebp-20h]
  int v3; // [esp+8h] [ebp-1Ch]
  int j; // [esp+Ch] [ebp-18h]
  _DWORD *v5; // [esp+10h] [ebp-14h]
  int i; // [esp+14h] [ebp-10h]
  int v7; // [esp+18h] [ebp-Ch]
  _DWORD *v8; // [esp+20h] [ebp-4h]

  if ( *a1 == 1 )
  {
    v8 = (_DWORD *)a1[1];
  }
  else
  {
    if ( *a1 != 2 )
      return 0;
    v8 = rf_vector3_default_construct_noop((void *)(a1[2] + 6592));
  }
  v7 = 0;
  for ( i = 0; i < rf_v3c_asset_get_mesh_count(v8); ++i )
  {
    v5 = *(_DWORD **)(v8[19] + 144 * i + 140);
    v7 += 16;
    for ( j = 0; j < *v5; ++j )
    {
      v3 = v5[j + 1];
      for ( k = 0; k < *(unsigned __int16 *)(v3 + 12); ++k )
        v7 += 3 * *(unsigned __int16 *)(*(_DWORD *)(v3 + 8) + 56 * k + 40);
    }
  }
  return v7;
}

