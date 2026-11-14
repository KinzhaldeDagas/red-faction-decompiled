// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A5600 sub_4A5600
// UNREALRED VERIFIED [lan-match-flow-20261028] Idempotent authority match-end transition: an already-set gameflags bit 4 returns immediately. It clears each player network record +0xC (record at Player+0x1200; semantic meaning unresolved), sends zero-payload packet 21 via 0x4A5730, clears gameflags bit 2, sets bit 4, selects an explicit level or calls rotation selector 0x48FEF0 for NULL, then requests panel 34. Panel 34 initialization/tick are 0x4A5BB0/0x4A5F00. This does not establish a whole-world pause or comprehensive combat freeze.
unsigned int __cdecl sub_4A5600(char *Source)
{
  unsigned int result; // eax
  int v2[2]; // [esp-10h] [ebp-40h] BYREF
  int v3[5]; // [esp-8h] [ebp-38h] BYREF
  _DWORD *v4; // [esp+Ch] [ebp-24h]
  _DWORD *v5; // [esp+10h] [ebp-20h]
  int *v6; // [esp+14h] [ebp-1Ch]
  void *v7; // [esp+18h] [ebp-18h]
  _DWORD *i; // [esp+1Ch] [ebp-14h]
  int v9; // [esp+20h] [ebp-10h]
  int v10; // [esp+2Ch] [ebp-4h]

  result = rf_multiplayer_game_flags & 4;
  if ( (rf_multiplayer_game_flags & 4) == 0 )
  {
    for ( i = (_DWORD *)dword_87C324; i; i = v5 )
    {
      *(_DWORD *)(i[1152] + 12) = 0;
      if ( *i == dword_87C324 )
        v5 = nullptr;
      else
        v5 = (_DWORD *)*i;
    }
    v9 = rf_multiplayer_game_mode_get();
    if ( v9 == 1 || v9 == 2 )
      rf_server_send_team_score_packet53(0);
    rf_multiplayer_broadcast_enter_limbo_packet21();
    rf_multiplayer_game_flags &= ~2u;
    rf_multiplayer_game_flags |= 4u;
    if ( Source )
    {
      v7 = v3;
      v4 = rf_string_construct_from_cstr(v3, (char *)&byte_63AC8B);
      v3[4] = (int)v4;
      v10 = 0;
      v6 = v2;
      v3[3] = (int)rf_string_construct_from_cstr(v2, Source);
      v10 = -1;
      rf_level_transition_assign_level_and_save_strings(v2[0], (char *)v2[1], v3[0], (char *)v3[1]);
    }
    else
    {
      sub_48FEF0();
    }
    return rf_ui_request_panel_immediate(34, 0);
  }
  return result;
}

