// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A4540 rf_console_ban_player_name
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// No-argument callback, runtime1/authority1. Argument parsing(mask2,option1), case-sensitive full-name circular search and usage policy mirror kick. Excludes local AND requires
// net+4608 nonnull. First eligible match prints localized88E334 with argument into256-byte buffer, appends its address through banlist_append_address(net), then kick/removal5590;
// breaks regardless delegate success. Does not kick every duplicate name or require peer state2/valid handle. Empty argument sets usage flag; absent argument relies on existing flag.
// Unbounded formatted usage/name buffers; no own runtime persistence beyond delegates.
int rf_console_ban_player_name()
{
  int result; // eax
  bool v1; // cf
  int v2; // [esp+10h] [ebp-154h]
  unsigned __int8 v3; // [esp+16h] [ebp-14Eh]
  const char *v4; // [esp+18h] [ebp-14Ch]
  char *v5; // [esp+1Ch] [ebp-148h]
  int v6; // [esp+20h] [ebp-144h]
  char *v8; // [esp+30h] [ebp-134h]
  char v9[40]; // [esp+34h] [ebp-130h] BYREF
  char Buffer[256]; // [esp+5Ch] [ebp-108h] BYREF
  int i; // [esp+160h] [ebp-4h]

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    if ( dword_1809818 )
    {
      rf_console_read_argument_validate_type_mask(2, 1);
      v8 = &MEMORY[0x1809820];
      do
        result = (int)v8;
      while ( *v8++ );
      if ( v8 == (char *)&unk_1809821 )
      {
        dword_1809814 = 1;
      }
      else
      {
        result = dword_87C324;
        for ( i = dword_87C324; i; i = v6 )
        {
          v5 = &MEMORY[0x1809820];
          v4 = rf_string_object_c_str_or_empty((const void *)(i + 8));
          while ( 1 )
          {
            result = (int)v4;
            v1 = (unsigned int)*v4 < (unsigned __int8)*v5;
            if ( *v4 != *v5 )
              break;
            if ( !*v4 )
              goto LABEL_19;
            result = (int)v4;
            v3 = v4[1];
            v1 = v3 < (unsigned __int8)v5[1];
            if ( v3 != v5[1] )
              break;
            v4 += 2;
            v5 += 2;
            if ( !v3 )
            {
LABEL_19:
              v2 = 0;
              goto LABEL_21;
            }
          }
          result = -v1 - (v1 - 1);
          v2 = result;
LABEL_21:
          if ( !v2 && i != rf_local_fpgun_player )
          {
            result = i;
            if ( *(_DWORD *)(i + 4608) )
            {
              sprintf(Buffer, unk_88E334, &MEMORY[0x1809820]);
              rf_console_output_append_text_lines(Buffer, nullptr);
              rf_banlist_append_address(*(u_long **)(i + 4608));
              result = rf_server_kick_and_remove_player(i);
              break;
            }
          }
          if ( *(_DWORD *)i == dword_87C324 )
          {
            v6 = 0;
          }
          else
          {
            result = i;
            v6 = *(_DWORD *)i;
          }
        }
      }
    }
    if ( dword_1809814 )
    {
      rf_console_output_append_text_lines(dword_88E210, nullptr);
      sprintf(v9, "     ban <%s>\n", unk_88E144);
      return rf_console_output_append_text_lines(v9, nullptr);
    }
  }
  return result;
}

