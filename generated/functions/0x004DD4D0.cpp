// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DD4D0 rf_player_unlink_close_and_destroy_record
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player lifecycle, weapon-class selection, team-skin material/profile loops, native string-buffer aliases and caller ABI): Cdecl player-record pointer, requires valid linked nonNULL record; final NULL test does NOT protect earlier dereferences. Unlinks circular list (next0,prev4,head87C324); singleton head zeros head, otherwise updates neighbors and head if needed; clears record links. Only multiplayer byte EXACT1 performs network cleanup: server-authority EXACT1 calls497980(player), closes peer at network-record4608+16 with flag0 if !=-1 then writes-1, closes matching endpoint using network record and flag0. Unconditionally operator-deletes network record4608, assigns empty C string63C221 to name RFString8, operator-deletes member44, releases/zeros25 decal slots4328..4424. Only player==global local player invokes empty
// local fpgun hook and recycles screen bitmap4232; no own model-cache teardown. Scans signed local-entry count, re-reading count: matching entry optionally invokes camera-wrapper cleanup412450(camera196), zeros slot and decrements count WITHOUT shifting/compacting entries. Count shrink can hide later slots from this traversal. Finally calls scalar-deleting destructor(player,1), which destroys embedded options228/name8 and frees record; EAX contains original freed receiver bits on normal path. Does NOT clear global local player/entity/AI pointers or destroy associated entity here. No network/member/list integrity guards.
char *__cdecl rf_player_unlink_close_and_destroy_record(char *a1)
{
  char *result; // eax
  int i; // [esp+14h] [ebp-4h]

  if ( (char *)dword_87C324 == a1 )
  {
    if ( *(char **)a1 == a1 )
    {
      *(_DWORD *)a1 = 0;
      *((_DWORD *)a1 + 1) = 0;
      dword_87C324 = 0;
      goto LABEL_6;
    }
    dword_87C324 = *(_DWORD *)a1;
  }
  **((_DWORD **)a1 + 1) = *(_DWORD *)a1;
  *(_DWORD *)(*(_DWORD *)a1 + 4) = *((_DWORD *)a1 + 1);
  *(_DWORD *)a1 = 0;
  *((_DWORD *)a1 + 1) = 0;
LABEL_6:
  if ( rf_multiplayer_runtime_mode == 1 )
  {
    if ( rf_multiplayer_server_authority == 1 )
      rf_ctf_drop_player_carried_flag((int)a1);
    if ( *(_DWORD *)(*((_DWORD *)a1 + 1152) + 16) != -1 )
    {
      rf_reliable_udp_close_peer((_DWORD *)(*((_DWORD *)a1 + 1152) + 16), 0);
      *(_DWORD *)(*((_DWORD *)a1 + 1152) + 16) = -1;
    }
    rf_reliable_udp_close_matching_endpoint(*((_DWORD *)a1 + 1152), 0);
  }
  operator delete(*((void **)a1 + 1152));
  rf_string_assign_from_cstr((_DWORD *)a1 + 2, (char *)byte_63C221);
  operator delete(*((void **)a1 + 11));
  result = (char *)rf_model_mesh_decal_slots_clear25((int)a1);
  if ( a1 == (char *)rf_local_fpgun_player )
  {
    rf_player_call_local_fpgun_release_hook((int)a1);
    result = (char *)rf_player_release_weapon_screen_bitmap((int)a1);
  }
  for ( i = 0; i < rf_local_player_entry_count; ++i )
  {
    result = (char *)i;
    if ( (char *)rf_local_player_entries[i] == a1 )
    {
      if ( *((_DWORD *)a1 + 49) )
        rf_camera_slot_destroy_entity(*((void ***)a1 + 49));
      rf_local_player_entries[i] = 0;
      result = (char *)--rf_local_player_entry_count;
    }
  }
  if ( a1 )
    return rf_player_record_scalar_deleting_destructor(a1, 1);
  return result;
}

