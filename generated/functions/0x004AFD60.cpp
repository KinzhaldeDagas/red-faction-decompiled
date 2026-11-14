// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AFD60 rf_server_apply_state_info_request_payload9
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Recovered4AFD60..4AFEC7, lastRET4AFEC6; descriptor9. Cdecl(payload,sourceEndpoint), both consumed. Find player by SOURCE endpoint first; missing
// returns without scanning payload. Found: full unbounded scan of payload C-string BEFORE strncpy1023 to1024-byte local; force Destination[1022]=NUL, advance unused cursor by
// original full length+1 truncated16. Ruleflags4 selects RFString6FC300 comparison, otherwise6FC31C; case-insensitive not-equal predicate. Mismatch broadcasts packet7(claimed
// endpoint-owned peer netID,reason5) THEN remove_player_and_mark_object(peer). Match invokes activate_peer_and_send_world_state(peer). No own runtime/authority/state gate, source
// pointer/length checks or file/CRC validation. Unlike ID-addressed callbacks, this one chooses peer by source endpoint; long-string copy truncation does not bound the earlier scan.
void __cdecl rf_server_apply_state_info_request_payload9(const unsigned __int8 *payload, const void *source)
{
  char Destination[1024]; // [esp+14h] [ebp-410h] BYREF
  bool v3; // [esp+41Bh] [ebp-9h]
  _DWORD *v4; // [esp+41Ch] [ebp-8h]
  int v5; // [esp+420h] [ebp-4h]

  v4 = rf_player_find_by_network_endpoint((int)source);
  if ( v4 )
  {
    v5 = 0;
    strncpy(Destination, (const char *)payload, 0x3FFu);
    Destination[1022] = 0;
    v5 = (unsigned __int16)(v5 + strlen((const char *)payload) + 1);
    v3 = 0;
    if ( (rf_multiplayer_game_flags & 4) != 0 )
      v3 = rf_rf_string_not_equals_cstring_case_insensitive((int)unk_6FC300, Destination);
    else
      v3 = rf_rf_string_not_equals_cstring_case_insensitive((int)unk_6FC31C, Destination);
    if ( v3 )
    {
      rf_multiplayer_broadcast_left_game_packet7(*(_BYTE *)(v4[1152] + 20), 5);
      rf_multiplayer_remove_player_and_mark_object((int)v4);
    }
    else
    {
      rf_server_activate_peer_and_send_world_state((int)v4);
    }
  }
}

