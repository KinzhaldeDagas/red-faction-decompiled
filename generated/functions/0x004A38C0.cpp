// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A38C0 rf_server_send_browser_info_packet1
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Cdecl(endpoint), runtime1/authority exactly1. Opcode1 payload: protocol BYTE89h, server name RFString704EC0+NUL, game mode LOW BYTE704ED4, player-count LOW BYTE, configured max LOW
// BYTE704EDC, level-display string6FC314+NUL, enabled archive basename+NUL, flags BYTE. Archive temp initializes first byte from PE63A977(0) plus16 zero bytes before command-line
// basename helper. No packet-bound check; full string scans narrowed to uint16 lengths/cursor. Ordinary total=three string lengths+11,payload=lengths+8.
// Advertised flags:1 only when BYTE704E83 EXACTLY1;2 when game flags400 set;4 when configured password704EC8 nonempty versus verified NUL63A9E5. Counts/mode truncate naturally to
// byte, without normalization/clamp. Direct unreliable send, no own endpoint-null guard or server-state mutation. Uses display level string6FC314, distinct from join-accept level
// filename6FC31C.
int __cdecl rf_server_send_browser_info_packet1(int a1)
{
  int result; // eax
  const char *v2; // eax
  const char *v3; // eax
  char *v4; // [esp+Ch] [ebp-264h]
  unsigned __int16 v5; // [esp+10h] [ebp-260h]
  unsigned __int16 v6; // [esp+20h] [ebp-250h]
  unsigned __int16 v7; // [esp+4Ch] [ebp-224h]
  unsigned __int16 v8; // [esp+4Ch] [ebp-224h]
  unsigned __int16 v9; // [esp+4Ch] [ebp-224h]
  unsigned __int16 v10; // [esp+4Ch] [ebp-224h]
  char Src; // [esp+50h] [ebp-220h] BYREF
  _DWORD v12[4]; // [esp+51h] [ebp-21Fh] BYREF
  char v13; // [esp+66h] [ebp-20Ah]
  char v14; // [esp+67h] [ebp-209h]
  char v15; // [esp+68h] [ebp-208h] BYREF
  __int16 v16; // [esp+69h] [ebp-207h]
  char v17; // [esp+6Bh] [ebp-205h]
  _BYTE v18[515]; // [esp+6Ch] [ebp-204h] BYREF
  char v19; // [esp+26Fh] [ebp-1h]

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    v15 = 1;
    v17 = -119;
    v6 = strlen(rf_string_object_c_str_or_empty(unk_704EC0));
    v2 = rf_string_object_c_str_or_empty(unk_704EC0);
    memcpy(v18, v2, v6);
    *(&v15 + (unsigned __int16)(v6 + 4)) = 0;
    v13 = unk_704ED4;
    *(&v15 + (unsigned __int16)(v6 + 5)) = unk_704ED4;
    v14 = rf_player_runtime_list_count();
    *(&v15 + (unsigned __int16)(v6 + 6)) = v14;
    v18[514] = unk_704EDC[0];
    *(&v15 + (unsigned __int16)(v6 + 7)) = unk_704EDC[0];
    v5 = strlen(rf_string_object_c_str_or_empty(unk_6FC314));
    v3 = rf_string_object_c_str_or_empty(unk_6FC314);
    memcpy(&v15 + (unsigned __int16)(v6 + 8), v3, v5);
    v7 = v5 + v6 + 8;
    *(&v15 + v7++) = 0;
    Src = 0;
    memset(v12, 0, sizeof(v12));
    rf_command_line_copy_enabled_archive_basename(&Src);
    v4 = (char *)v12 + strlen(&Src);
    memcpy(&v15 + v7, &Src, (unsigned __int16)((_WORD)v4 - (unsigned __int16)v12));
    v8 = (_WORD)v4 - (unsigned __int16)v12 + v7;
    *(&v15 + v8) = 0;
    v9 = v8 + 1;
    v19 = 0;
    if ( byte_704E83 == 1 )
      v19 |= 1u;
    if ( (rf_multiplayer_game_flags & 0x400) != 0 )
      v19 |= 2u;
    if ( rf_rf_string_not_equals_cstring_case_insensitive((int)dword_704EC8, (char *)&byte_63A9E5) )
      v19 |= 4u;
    *(&v15 + v9) = v19;
    v10 = v9 + 1;
    v16 = v10 - 3;
    return rf_network_send_unreliable(a1, &v15, v10);
  }
  return result;
}

