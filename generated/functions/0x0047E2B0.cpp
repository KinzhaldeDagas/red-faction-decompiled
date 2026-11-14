// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047E2B0 rf_rfl_world_geometry_read_and_seed_mp_rooms
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL header and prelude control flow, legacy light layouts, native ECX/stack arguments, environment initialization and multiplayer room tracking): 
// Cdecl stream, normalized full EAX Boolean. Native calls geometry_deserialize with THREE stack arguments(stream,old world solid,1), cleans12; pseudocode may hide third argument.
// Assigns result global world solid and always clears BYTE6FC354. Only when multiplayer mode EXACT1 AND world nonnull: authority EXACT1 fills all backing bytes of bitset823BC0 with1,
// resets count822714=0, then scans world room vector+144 in order, storing first128 eligible pointers at822510. Predicate requires room BYTE0 EXACT1 and BYTE152==0. Stops immediately
// at count128, with no sorting or remaining traversal.
// Outside multiplayer1 or on NULL geometry, leaves old tracking count/array/bitset untouched. Client/non-exact1 authority rebuilds array but preserves bitset. Does not clear stale
// array tail, check room pointers or use liquid-room vector+156. Return world!=NULL irrespective later tracking content.
BOOL __cdecl rf_rfl_world_geometry_read_and_seed_mp_rooms(int a1)
{
  _BYTE **v1; // eax
  int i; // [esp+0h] [ebp-4h]

  rf_world_solid = (int)rf_level_geometry_deserialize(a1, (char *)rf_world_solid);
  unk_6FC354 = 0;
  if ( rf_multiplayer_runtime_mode == 1 && rf_world_solid )
  {
    if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
      rf_bitset_fill_all_storage_bytes((int)&unk_823BC0, 1);
    dword_822714 = 0;
    for ( i = 0; i < rf_receiver_get_first_dword((void *)(rf_world_solid + 144)) && dword_822714 < 128; ++i )
    {
      v1 = (_BYTE **)sub_552200((_DWORD *)(rf_world_solid + 144), i);
      if ( rf_room_mp_tracking_eligible(*v1) )
        unk_822510[dword_822714++] = *(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 144), i);
    }
  }
  return rf_world_solid != 0;
}

