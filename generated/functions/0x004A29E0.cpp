// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A29E0 rf_client_apply_join_accept_payload3
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Cdecl(payload,sender endpoint). Admission is pending IPv4 DWORD6F52DC!=0 AND sender DWORD0 equals it; sender PORT is not compared. No own runtime/authority/null/length guard or
// current incoming xrefs. Packet3 pairing from exact sender. Full source level name scanned, strncpy255 then destination[254]=0, cursor starts uint16(strlen+1). Assigns level6FC3AC
// and level-transition strings via two8-byte by-value RFStrings (empty save string;16-byte cleanup). Then receives CRC, raw game mode, game flags, floats6FC428/704EE4 (native
// fld/fstp after copies), assigned id BYTE and net flags DWORD. Does not verify received CRC against a local file here.
// Sets local team from received flags80 BEFORE runtime_initialize(1,sender). Saves/restores received game flags around initialization, then forces authority0. If local reliable
// handle remains-1, calls4A5FA0(id,3) and localized reliable-connection-failure modal. Otherwise copies full8-byte sender to704EF4/704EF8, sets local network id, and only when
// received flags mask2 set latches704E84=1 and ORs local net flags2 (no complementary clear here); logs joined name if runtime remains1. Both post-init branches clear notification
// prefix/suffix strings via49FAA0. Early target rejection skips all parsing/state changes.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, compiled registry/dispatcher and native ABI refinement): Original PE descriptor at0x0066296C registers opcode3 (join_accept), callback0x004A29E0. Native dispatcher49FB50 indirectly calls it with(payload,source endpoint),8-byte caller cleanup,after envelope/source admission; handler receives NO payload length. Thus absence of IDA direct call/xrefs does not imply a dormant handler. Compiled registration and dispatch edge verified independently of earlier paired-layout inference; actual invocation still depends on runtime admission.
int __cdecl rf_client_apply_join_accept_payload3(const char *a1, int *a2)
{
  int result; // eax
  int v3; // eax
  int v4; // eax
  const char *v5; // eax
  int v6[2]; // [esp-10h] [ebp-168h] BYREF
  int v7[7]; // [esp-8h] [ebp-160h] BYREF
  _DWORD *v8; // [esp+14h] [ebp-144h]
  int v9; // [esp+18h] [ebp-140h]
  const char *v10; // [esp+20h] [ebp-138h]
  const char *v11; // [esp+24h] [ebp-134h]
  int *v12; // [esp+28h] [ebp-130h]
  void *v13; // [esp+2Ch] [ebp-12Ch]
  __int16 v14; // [esp+30h] [ebp-128h]
  int v15; // [esp+34h] [ebp-124h]
  char v16; // [esp+3Bh] [ebp-11Dh]
  int v17; // [esp+3Ch] [ebp-11Ch]
  unsigned int v18; // [esp+40h] [ebp-118h]
  char Destination[260]; // [esp+44h] [ebp-114h] BYREF
  int v20; // [esp+154h] [ebp-4h]

  result = rf_join_pending_ipv4_is_set();
  if ( (_BYTE)result )
  {
    result = rf_join_sender_ipv4_matches_pending(a2);
    if ( (_BYTE)result )
    {
      v17 = 0;
      v11 = a1;
      v10 = a1 + 1;
      v11 += strlen(v11) + 1;
      v9 = v11 - (a1 + 1);
      v14 = (_WORD)v11 - ((_WORD)a1 + 1);
      strncpy(Destination, a1, 0xFFu);
      Destination[254] = 0;
      v17 = (unsigned __int16)((_WORD)v11 - (_WORD)a1);
      rf_string_assign_from_cstr(unk_6FC3AC, Destination);
      v13 = v7;
      v8 = rf_string_construct_from_cstr(v7, (char *)&byte_63A976);
      v7[6] = (int)v8;
      v20 = 0;
      v12 = v6;
      rf_string_copy_construct_from_object(v6, (char **)unk_6FC3AC);
      v7[5] = v3;
      v20 = -1;
      rf_level_transition_assign_level_and_save_strings(v6[0], (char *)v6[1], v7[0], (char *)v7[1]);
      dword_6FC3A8 = *(_DWORD *)&a1[v17];
      v17 += 4;
      unk_704ED4 = *(_DWORD *)&a1[v17];
      v17 += 4;
      rf_multiplayer_game_flags = *(_DWORD *)&a1[v17];
      v17 += 4;
      dword_6FC428 = *(_DWORD *)&a1[v17];
      v17 += 4;
      dword_704EE4 = *(_DWORD *)&a1[v17];
      v17 += 4;
      v16 = a1[v17];
      v15 = *(_DWORD *)&a1[++v17];
      v17 += 4;
      *(_BYTE *)(rf_local_fpgun_player + 48) = (v15 & 0x80) != 0;
      v18 = rf_multiplayer_game_flags;
      rf_multiplayer_runtime_initialize(1, a2);
      rf_multiplayer_server_authority = 0;
      rf_multiplayer_game_flags = v18;
      if ( *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 16) == -1 )
      {
        rf_client_leave_game_notify_and_exit(v16, 3);
        v7[4] = (int)dword_88E1EC;
        v7[3] = dword_88E1E8;
        rf_ui_show_ok_modal((const char *)dword_88E1E8, dword_88E1EC, nullptr, 0);
      }
      else
      {
        v4 = a2[1];
        dword_704EF4 = *a2;
        unk_704EF8 = v4;
        *(_BYTE *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 20) = v16;
        if ( (v15 & 2) != 0 )
        {
          unk_704E84 = 1;
          *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 8) |= 2u;
        }
        if ( rf_multiplayer_runtime_mode == 1 )
        {
          v5 = rf_string_object_c_str_or_empty((const void *)(rf_local_fpgun_player + 8));
          rf_multiplayer_log_printf("Joined game as %s", v5);
        }
      }
      return rf_multiplayer_notification_text_rows_clear();
    }
  }
  return result;
}

