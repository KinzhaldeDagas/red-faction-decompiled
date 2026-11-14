// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AFC00 rf_client_send_state_info_request_packet9
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Noarg. Build opcode9 with current-level RFString6FC31C as NUL-terminated payload. Full scan to NUL first, truncate strlen to unsigned16, memcpy that
// many bytes, then appendNUL using unsigned16 cursor. WORD payload=length+1,total=length+4 modulo16-bit arithmetic. Stack packet512 bytes; no capacity/length clamp or split.
// Reliable_queue(localPlayer,packet,total,requireActive0) with no own local/net/runtime/authority guard. Returns queue EAX. Does not send next-level string6FC300 even when ruleflags4
// set; receiving server independently selects comparison string.
int rf_client_send_state_info_request_packet9()
{
  const char *v0; // eax
  unsigned __int16 v2; // [esp+0h] [ebp-224h]
  unsigned __int8 Src; // [esp+1Ch] [ebp-208h] BYREF
  __int16 v4; // [esp+1Dh] [ebp-207h]
  char v5; // [esp+1Fh] [ebp-205h] BYREF

  Src = 9;
  v2 = strlen(rf_string_object_c_str_or_empty(unk_6FC31C));
  v0 = rf_string_object_c_str_or_empty(unk_6FC31C);
  memcpy(&v5, v0, v2);
  *(&Src + (unsigned __int16)(v2 + 3)) = 0;
  v4 = v2 + 1;
  return rf_multiplayer_queue_reliable_packet(rf_local_fpgun_player, &Src, (unsigned __int16)(v2 + 4), 0);
}

