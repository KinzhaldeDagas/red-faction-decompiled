// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004624F0 rf_multiplayer_menu_join_selected_server
// UNREALRED VERIFIED [local-multiplayer-20261028] Join Selected validates selected result index, stops pending browser work, copies selected server identity and rejects incompatible active-mod ownership before connect. Server flag0x2 opens password prompt0x4628A0; otherwise0x4A2E10 builds the request using selected endpoint, local player name, empty password and update rate. It does not mark a connection gameplay-ready merely because the Join button was pressed.
void rf_multiplayer_menu_join_selected_server()
{
  int v0; // eax
  _DWORD v1[2]; // [esp-14h] [ebp-3E4h] BYREF
  _DWORD v2[2]; // [esp-Ch] [ebp-3DCh] BYREF
  int v3; // [esp-4h] [ebp-3D4h]
  int v4; // [esp+4h] [ebp-3CCh]
  _DWORD *v5; // [esp+8h] [ebp-3C8h]
  _DWORD *v6; // [esp+Ch] [ebp-3C4h]
  int v7; // [esp+24h] [ebp-3ACh]
  char *v8; // [esp+2Ch] [ebp-3A4h]
  char *v9; // [esp+30h] [ebp-3A0h]
  _DWORD *v10; // [esp+34h] [ebp-39Ch]
  void *v11; // [esp+38h] [ebp-398h]
  char v12[128]; // [esp+3Ch] [ebp-394h] BYREF
  char v13[256]; // [esp+BCh] [ebp-314h] BYREF
  char Buffer[256]; // [esp+1BCh] [ebp-214h] BYREF
  char String1[260]; // [esp+2BCh] [ebp-114h] BYREF
  int v16; // [esp+3CCh] [ebp-4h]

  if ( dword_661F9C >= 0 && dword_661F9C < unk_6F51A8 )
  {
    unk_6F51A1 = 1;
    unk_6F51A2 = 0;
    unk_6F51B0 = -1;
    if ( rf_join_pending_ipv4_is_set() )
      rf_join_pending_ipv4_clear();
    rf_string_assign_from_cstr(unk_704EC0, (char *)dword_6F52CC + 108 * dword_661F9C);
    memset(String1, 0, 256);
    v8 = (char *)dword_6F52CC + 108 * dword_661F9C + 65;
    v9 = (char *)dword_6F52CC + 108 * dword_661F9C + strlen((const char *)dword_6F52CC + 108 * dword_661F9C + 64) + 65;
    v7 = v9 - v8;
    if ( v9 == v8 )
    {
      if ( rf_command_line_copy_enabled_archive_basename(String1) )
      {
        sprintf(v13, unk_88E3C0, String1);
        rf_ui_show_ok_modal(unk_88E138, (int)v13, 0, 0);
        return;
      }
    }
    else if ( !rf_command_line_copy_enabled_archive_basename(String1)
           || _stricmp(String1, (const char *)dword_6F52CC + 108 * dword_661F9C + 64) )
    {
      sprintf(Buffer, unk_88E3BC, (char *)dword_6F52CC + 108 * dword_661F9C + 64);
      rf_ui_show_ok_modal(unk_88E138, (int)Buffer, 0, 0);
      return;
    }
    if ( (*((_DWORD *)dword_6F52CC + 27 * dword_661F9C + 26) & 2) != 0 )
    {
      rf_ui_show_ok_modal(unk_88E14C, (int)&unk_63684A, (int)rf_browser_join_selected_with_prompt_password, 1);
    }
    else
    {
      sprintf(v12, "MAX UPDATE RATE : %d\n", *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 2492));
      rf_join_pending_ipv4_set_from_endpoint((int *)dword_6F52CC + 27 * dword_661F9C + 21);
      v3 = *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 2492);
      v11 = v2;
      v6 = rf_string_construct_from_cstr(v2, (char *)&byte_63684B);
      v5 = v6;
      v16 = 0;
      v10 = v1;
      rf_string_copy_construct_from_object(v1, (char **)(rf_local_fpgun_player + 8));
      v4 = v0;
      v16 = -1;
      rf_multiplayer_send_join_request_packet2(
        (int)dword_6F52CC + 108 * dword_661F9C + 84,
        v1[0],
        v1[1],
        v2[0],
        v2[1],
        v3);
      rf_clock_deadline_set_wrapped_offset(&dword_6F537C, 1000);
    }
  }
}

