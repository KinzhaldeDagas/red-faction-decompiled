// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AFBC0 rf_client_apply_state_info_done_callback10
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Recovered4AFBC0..4AFBF4, lastRET4AFBF3; original descriptor10. No consumed arguments; dispatcher payload/source ignored. Unconditionally dereference
// local player+4608 net and write stateDWORD12=2, THEN set reliable handle net16 minimum resend delay333ms. No runtime/authority/local/net/handle validation, pending-geometry
// completion check, packet length or acknowledgment. State write not rolled back on transport delegate failure. No meaningful return.
void __cdecl rf_client_apply_state_info_done_callback10()
{
  *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 12) = 2;
  rf_reliable_udp_set_minimum_resend_delay(*(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 16), 333);
}

