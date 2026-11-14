// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C74D0 rf_glass_remove_geometry_and_record_id
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Collect linked faces from geometry record+0x28 into temporary vector then remove/destroy each face from rf_world_solid. Traverse render objects vector+0x9C backward through0x524100, optional multiplayer server path finds pointer in0x822510 registry and calls0x57E5A0(handle,index,0), then clears render-object vector and appends saved geometry id+0x24 to0x822310 incrementing count0x8222F4. No local ledger capacity/deduplication check or glass-shard creation in this body. Snapshot replay uses this removal path after its first-byte admission.
void __cdecl rf_glass_remove_geometry_and_record_id(_DWORD *a1)
{
  _DWORD **v1; // eax
  _DWORD **v2; // eax
  int i; // [esp+8h] [ebp-20h]
  int j; // [esp+Ch] [ebp-1Ch]
  int k; // [esp+Ch] [ebp-1Ch]
  int m; // [esp+Ch] [ebp-1Ch]
  void *v7[3]; // [esp+10h] [ebp-18h] BYREF
  int v8; // [esp+24h] [ebp-4h]

  rf_dword_array_construct_capacity(v7, 0);
  v8 = 0;
  for ( i = rf_receiver_get_first_dword(a1 + 10); i; i = rf_face_next_room_link(i) )
    rf_pointer_array_append_dword(v7, i);
  for ( j = 0; j < rf_receiver_get_first_dword(v7); ++j )
  {
    v1 = (_DWORD **)sub_552200(v7, j);
    rf_solid_face_remove_destroy((int *)rf_world_solid, *v1, 0);
  }
  for ( k = rf_receiver_get_first_dword(a1 + 39) - 1; k >= 0; --k )
  {
    v2 = (_DWORD **)rf_inline_dword_array4_element_address_unchecked(a1 + 39, k);
    rf_world_decal_remove_spatial_links_and_recycle(*v2);
  }
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    for ( m = 0; m < dword_822714; ++m )
    {
      if ( (_DWORD *)unk_822510[m] == a1 )
      {
        rf_bitset_set_bit_unchecked(dword_823BC0, m, 0);
        break;
      }
    }
  }
  rf_pointer_array_clear_count_keep_storage(a1 + 39);
  unk_822310[unk_8222F4++] = a1[9];
  v8 = -1;
  rf_pointer_array_destroy_backing_storage(v7);
}

