// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DD030 rf_player_create_runtime
// UNREALRED VERIFIED [local-multiplayer-20261028] This is player allocation/initialization, NOT std::_Throw_future_error. Allocates0x1204 bytes, initializes player/entity/score/network/input state and returns the Player pointer inEAX at0x4DD4BA. Nonzero byte argument appends to local entry array0x87C5B0/count0x87C638 with maximum2; all players always link into circular list0x87C324. Remote join callers4A2580/4A36E9 pass0 and consumeEAX; local startup4DBCC5 and splitscreen4AE328 pass1. Corrected name/prototype follow these PE-matched call sites, not the previous library-signature guess.
void *__cdecl rf_player_create_runtime(unsigned __int8 bLocal)
{
  int v1; // eax
  int v3; // [esp+4h] [ebp-3Ch]
  int v4; // [esp+Ch] [ebp-34h]
  void *v5; // [esp+10h] [ebp-30h]
  char *v6; // [esp+24h] [ebp-1Ch]
  int i; // [esp+2Ch] [ebp-14h]

  v6 = (char *)operator new(0x1204u);
  if ( v6 )
  {
    rf_player_construct_owned_members(v6);
    v4 = v1;
  }
  else
  {
    v4 = 0;
  }
  if ( bLocal )
  {
    if ( rf_local_player_entry_count == 2 )
    {
      if ( v4 )
        rf_player_record_scalar_deleting_destructor((char *)v4, 1);
      return nullptr;
    }
    rf_local_player_entries[rf_local_player_entry_count++] = v4;
  }
  if ( !v4 )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\player\\player.cpp",
      2480,
      "Failure to allocate player\n");
  *(_DWORD *)(v4 + 44) = operator new(8u);
  rf_string_assign_from_cstr((_DWORD *)(v4 + 8), "Default");
  *(_DWORD *)(v4 + 24) = sub_431680("miner1");
  *(_BYTE *)(v4 + 48) = 0;
  *(_DWORD *)(v4 + 20) = -1;
  *(_DWORD *)(v4 + 16) = bLocal != 0 ? 0x10 : 0;
  **(_WORD **)(v4 + 44) = 0;
  *(_WORD *)(*(_DWORD *)(v4 + 44) + 2) = 0;
  *(_WORD *)(*(_DWORD *)(v4 + 44) + 4) = 0;
  v5 = operator new(0x9C8u);
  if ( v5 )
    v3 = rf_player_aux4608_record_construct((int)v5);
  else
    v3 = 0;
  *(_DWORD *)(v4 + 4608) = v3;
  *(_DWORD *)(*(_DWORD *)(v4 + 4608) + 16) = -1;
  *(_DWORD *)(*(_DWORD *)(v4 + 4608) + 2488) = 0;
  *(_DWORD *)(*(_DWORD *)(v4 + 4608) + 1972) = 0;
  *(_DWORD *)(*(_DWORD *)(v4 + 4608) + 24) = 0;
  *(_DWORD *)(*(_DWORD *)(v4 + 4608) + 8) = 0;
  rf_net_statistics_initialize((int *)(*(_DWORD *)(v4 + 4608) + 28));
  *(_DWORD *)(*(_DWORD *)(v4 + 4608) + 1452) = 0;
  *(_DWORD *)(*(_DWORD *)(v4 + 4608) + 2492) = *(_DWORD *)&dword_662C60;
  *(float *)(*(_DWORD *)(v4 + 4608) + 1456) = 0.0;
  *(_BYTE *)(v4 + 4604) = 0;
  *(_BYTE *)(v4 + 49) = 1;
  *(_DWORD *)(v4 + 52) = 0;
  *(_DWORD *)(v4 + 56) = 0;
  *(_DWORD *)(v4 + 180) = -1;
  *(_BYTE *)(v4 + 176) = 0;
  *(_BYTE *)(v4 + 177) = 0;
  *(_DWORD *)(v4 + 196) = 0;
  rf_player_options_initialize_defaults(v4 + 228);
  *(_DWORD *)(v4 + 204) = 0;
  *(_DWORD *)(v4 + 200) = 0;
  *(_DWORD *)(v4 + 208) = rf_renderer_get_physical_screen_width();
  *(_DWORD *)(v4 + 212) = rf_renderer_get_physical_screen_height();
  *(float *)(v4 + 216) = 90.0;
  *(_DWORD *)(v4 + 224) = -1;
  *(_BYTE *)(v4 + 4228) = 0;
  *(_DWORD *)(v4 + 4232) = rf_bitmap_create_user_bitmap(7, 64, 64);
  *(float *)(v4 + 4296) = 0.0;
  *(float *)(v4 + 4300) = 0.0;
  rf_color4_set_bytes_return_destination((_BYTE *)(v4 + 4304), 0, 0, 0, 255);
  *(_DWORD *)(v4 + 4308) = 0;
  *(float *)(v4 + 4564) = 0.0;
  *(float *)(v4 + 4568) = 1.0;
  *(_DWORD *)(v4 + 4572) = 0;
  *(float *)(v4 + 4576) = 0.0;
  *(float *)(v4 + 4580) = 0.0;
  *(float *)(v4 + 4584) = 0.0;
  *(float *)(v4 + 4588) = 0.0;
  *(_BYTE *)(v4 + 4593) = 0;
  *(_BYTE *)(v4 + 4592) = 0;
  *(float *)(v4 + 4596) = 0.0;
  *(_DWORD *)(v4 + 72) = -1;
  *(_DWORD *)(v4 + 76) = -1;
  for ( i = 0; i < 25; ++i )
    *(_DWORD *)(v4 + 4 * i + 4328) = 0;
  rf_player_initialize_fpgun_runtime_members(v4);
  rf_player_initialize_weapon_preference_order(v4);
  if ( dword_87C324 )
  {
    *(_DWORD *)(v4 + 4) = *(_DWORD *)(dword_87C324 + 4);
    *(_DWORD *)v4 = dword_87C324;
    **(_DWORD **)(dword_87C324 + 4) = v4;
    *(_DWORD *)(dword_87C324 + 4) = v4;
  }
  else
  {
    *(_DWORD *)v4 = v4;
    *(_DWORD *)(v4 + 4) = v4;
    dword_87C324 = v4;
  }
  return (void *)v4;
}

