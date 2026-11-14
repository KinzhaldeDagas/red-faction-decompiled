// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A42D0 rf_console_kick_player_name
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// No-argument console callback, runtime1/authority EXACT1 only. If argument-present DWORD1809818 nonzero, reads argument with literal(type mask2,option1), scans1809820 toNUL; empty
// sets usage flag1809814=1. Nonempty traverses player circle comparing FULL name RFString+8 byte-for-byte CASE-SENSITIVELY, skips local and kicks FIRST eligible exact name via5590.
// No own player-net guard or not-found error. Prints localized88E010 with argument text through unbounded sprintf into256-byte buffer before removal. Afterwards preexisting/nonzero
// usage flag prints localized usage plus kick syntax via40-byte buffer, even after successful operation. Absent argument does not itself set usage flag; guard rejection skips
// everything. EAX incidental.
int rf_console_kick_player_name()
{
  int result; // eax
  bool v1; // cf
  int v2; // [esp+10h] [ebp-154h]
  unsigned __int8 v3; // [esp+16h] [ebp-14Eh]
  const char *v4; // [esp+18h] [ebp-14Ch]
  char *v5; // [esp+1Ch] [ebp-148h]
  _DWORD *v6; // [esp+20h] [ebp-144h]
  char *v8; // [esp+30h] [ebp-134h]
  char v9[40]; // [esp+34h] [ebp-130h] BYREF
  char Buffer[256]; // [esp+5Ch] [ebp-108h] BYREF
  _DWORD *i; // [esp+160h] [ebp-4h]

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
        for ( i = (_DWORD *)dword_87C324; i; i = v6 )
        {
          v5 = &MEMORY[0x1809820];
          v4 = rf_string_object_c_str_or_empty(i + 2);
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
          if ( !v2 && i != (_DWORD *)rf_local_fpgun_player )
          {
            sprintf(Buffer, unk_88E010, &MEMORY[0x1809820]);
            rf_console_output_append_text_lines(Buffer, nullptr);
            result = rf_server_kick_and_remove_player((int)i);
            break;
          }
          if ( *i == dword_87C324 )
          {
            v6 = nullptr;
          }
          else
          {
            result = (int)i;
            v6 = (_DWORD *)*i;
          }
        }
      }
    }
    if ( dword_1809814 )
    {
      rf_console_output_append_text_lines(dword_88E210, nullptr);
      sprintf(v9, "     kick <%s>\n", unk_88E144);
      return rf_console_output_append_text_lines(v9, nullptr);
    }
  }
  return result;
}

