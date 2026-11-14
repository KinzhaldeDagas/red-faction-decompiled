// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A47D0 rf_console_ban_ip_pattern
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Runtime1/authority1 no-argument console callback. Present argument parsed(mask2,option0); empty sets usage flag. Nonempty invalid ban-pattern text prints88E338 and immediately
// returns before usage display. Valid pattern appended uniquely, localized88E33C confirmation formatted with original argument. Then scans remote,nonnull-net players and kicks FIRST
// address found in ENTIRE current banlist, not necessarily matching only the just-added pattern. Breaks after one removal. Kicking message88E330 also substitutes original IP-pattern
// argument, not matched player name. Local excluded. Existing usage flag prints ban_ip syntax after normal paths; no own buffer bounds or every-match enforcement.
int rf_console_ban_ip_pattern()
{
  int result; // eax
  int v1; // [esp+Ch] [ebp-14Ch]
  char *v3; // [esp+24h] [ebp-134h]
  char v4[40]; // [esp+28h] [ebp-130h] BYREF
  char Buffer[256]; // [esp+50h] [ebp-108h] BYREF
  int i; // [esp+154h] [ebp-4h]

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    if ( dword_1809818 )
    {
      rf_console_read_argument_validate_type_mask(2, 0);
      v3 = &MEMORY[0x1809820];
      do
        result = (int)v3;
      while ( *v3++ );
      if ( v3 == (char *)&unk_1809821 )
      {
        dword_1809814 = 1;
      }
      else
      {
        if ( !rf_ban_pattern_text_is_valid(&MEMORY[0x1809820]) )
          return rf_console_output_append_text_lines(unk_88E338, nullptr);
        rf_banlist_append_unique_text(&MEMORY[0x1809820]);
        sprintf(Buffer, unk_88E33C, &MEMORY[0x1809820]);
        result = rf_console_output_append_text_lines(Buffer, nullptr);
        for ( i = dword_87C324; i; i = v1 )
        {
          if ( i != rf_local_fpgun_player
            && *(_DWORD *)(i + 4608)
            && rf_banlist_contains_address(*(u_long **)(i + 4608)) )
          {
            sprintf(Buffer, unk_88E330, &MEMORY[0x1809820]);
            rf_console_output_append_text_lines(Buffer, nullptr);
            result = rf_server_kick_and_remove_player(i);
            break;
          }
          result = i;
          if ( *(_DWORD *)i == dword_87C324 )
          {
            v1 = 0;
          }
          else
          {
            result = *(_DWORD *)i;
            v1 = *(_DWORD *)i;
          }
        }
      }
    }
    if ( dword_1809814 )
    {
      rf_console_output_append_text_lines(dword_88E210, nullptr);
      sprintf(v4, "     ban_ip <%s>\n", unk_88DFB8);
      return rf_console_output_append_text_lines(v4, nullptr);
    }
  }
  return result;
}

