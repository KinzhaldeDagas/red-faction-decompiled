// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AD570 rf_console_set_or_query_network_update_rate
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, packet14/27 registry bindings, rate-width/clamp policy, native string ABI and pregame17/18 wire layout): Noarg
// console callback. If argument-present1809818 parse(mask2,option0), inspect C-string1809820. Empty string prints localized usage88E210 and seven rate examples then exits; '?'
// case-insensitive prints current DWORD662C60 using localized88E214 then exits. Otherwise CRT atoi FIRST: any positive numeric prefix accepted as custom value (including trailing
// nonnumeric bytes), prints localized88E27C with PRECLAMP value. Nonpositive atoi falls through case-insensitive presets modem2600,isdn5000,cable15000,t1/lan200000; unknown
// prints88E278 and exits. Presets print88E274. All format output via unbounded sprintf to260-byte local buffer. Signed clamp minimum1000 ONLY AFTER status output; no upper clamp.
// Store full32 rate662C60 and, if local player exists, unguarded net1200+2492. With local player: runtime1 authority0 sends27 to local-player transport; runtime1 authority EXACT1
// broadcasts27; other states do not send. Both paths later serialize ONLY lowWORD, so200000 is3392 on wire, local/global/registry remain200000 until other updates. Always write
// registry(default root,'UpdateRate',DWORD662C60) after successful setting, ignoring result. Existing helpflag1809814 prints usage AFTER successful setting, or when no argument; no
// automatic current query on noargs. Early empty/?/invalid exits skip helpflag tail. No general multiplayer gate on local/registry setting.
void rf_console_set_or_query_network_update_rate()
{
  int v0; // [esp+38h] [ebp-10Ch]
  char Buffer[260]; // [esp+3Ch] [ebp-108h] BYREF

  if ( dword_1809818 )
  {
    rf_console_read_argument_validate_type_mask(2, 0);
    if ( &MEMORY[0x1809820] + strlen(&MEMORY[0x1809820]) + 1 == (char *)&unk_1809821 )
    {
      rf_console_output_append_text_lines(dword_88E210, nullptr);
      rf_console_output_append_text_lines("     rate modem", nullptr);
      rf_console_output_append_text_lines("     rate isdn", nullptr);
      rf_console_output_append_text_lines("     rate cable", nullptr);
      rf_console_output_append_text_lines("     rate t1", nullptr);
      rf_console_output_append_text_lines("     rate lan", nullptr);
      rf_console_output_append_text_lines("     rate <n>", nullptr);
      rf_console_output_append_text_lines("     rate ?", nullptr);
      return;
    }
    if ( !_stricmp(&MEMORY[0x1809820], "?") )
    {
      sprintf(Buffer, unk_88E214, *(_DWORD *)&dword_662C60);
      rf_console_output_append_text_lines(Buffer, nullptr);
      return;
    }
    v0 = atoi(&MEMORY[0x1809820]);
    if ( v0 > 0 )
    {
      sprintf(Buffer, unk_88E27C, v0);
      rf_console_output_append_text_lines(Buffer, nullptr);
    }
    else if ( !_stricmp(&MEMORY[0x1809820], "modem") )
    {
      v0 = 2600;
      sprintf(Buffer, unk_88E274, 2600);
      rf_console_output_append_text_lines(Buffer, nullptr);
    }
    else if ( !_stricmp(&MEMORY[0x1809820], "isdn") )
    {
      v0 = 5000;
      sprintf(Buffer, unk_88E274, 5000);
      rf_console_output_append_text_lines(Buffer, nullptr);
    }
    else if ( !_stricmp(&MEMORY[0x1809820], "cable") )
    {
      v0 = 15000;
      sprintf(Buffer, unk_88E274, 15000);
      rf_console_output_append_text_lines(Buffer, nullptr);
    }
    else
    {
      if ( _stricmp(&MEMORY[0x1809820], "t1") && _stricmp(&MEMORY[0x1809820], off_63B330) )
      {
        rf_console_output_append_text_lines(unk_88E278, nullptr);
        return;
      }
      v0 = 200000;
      sprintf(Buffer, unk_88E274, 200000);
      rf_console_output_append_text_lines(Buffer, nullptr);
    }
    if ( v0 < 1000 )
      v0 = 1000;
    *(_DWORD *)&dword_662C60 = v0;
    if ( rf_local_fpgun_player )
      *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 2492) = v0;
    if ( rf_local_fpgun_player )
    {
      if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
      {
        if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
          rf_multiplayer_broadcast_rate_change_if_local27(
            *(_BYTE *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 20),
            *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 2492));
      }
      else
      {
        rf_multiplayer_send_rate_change_to_local_transport27(
          *(_BYTE *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 20),
          *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 2492));
      }
    }
    rf_registry_write_dword(nullptr, "UpdateRate", *(_DWORD *)&dword_662C60);
  }
  if ( dword_1809814 )
  {
    rf_console_output_append_text_lines(dword_88E210, nullptr);
    rf_console_output_append_text_lines("     rate modem", nullptr);
    rf_console_output_append_text_lines("     rate isdn", nullptr);
    rf_console_output_append_text_lines("     rate cable", nullptr);
    rf_console_output_append_text_lines("     rate t1", nullptr);
    rf_console_output_append_text_lines("     rate lan", nullptr);
    rf_console_output_append_text_lines("     rate <n>", nullptr);
    rf_console_output_append_text_lines("     rate ?", nullptr);
  }
}

