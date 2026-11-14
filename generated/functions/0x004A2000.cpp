// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A2000 rf_pre_session_apply_join_rejection_payload4
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Recovered [4A2000,4A20A8), cdecl(payload), no current incoming xrefs. Native guard RETURNS for runtime1 with authority0 OR authority1; all other combinations parse, including
// runtime1 with unusual nonzero authority values other than1. No pending-target/source-address/null/length check. Reads reason as unsigned BYTE;0..10 remain, >=11 normalizes to9
// (native negative check after MOVZX cannot be true). Clears pending join IPv4 DWORD6F52DC, then shows localized OK modal(title88E1E8, *table78C250[reason],0,0). Clearing occurs even
// if modal helper refuses due to another active modal. Packet4 association is inferred from paired one-byte sender, not a live dispatch edge.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, compiled registry/dispatcher and native ABI refinement): Original PE descriptor at0x00662978 registers opcode4 (join_deny), callback0x004A2000. Native dispatcher49FB50 indirectly calls it with(payload,source endpoint),8-byte caller cleanup,after envelope/source admission; handler receives NO payload length. Thus absence of IDA direct call/xrefs does not imply a dormant handler. Compiled registration and dispatch edge verified independently of earlier paired-layout inference; actual invocation still depends on runtime admission.
void __cdecl rf_pre_session_apply_join_rejection_payload4(const unsigned __int8 *payload)
{
  int v1; // [esp+7h] [ebp-5h]

  if ( (rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority)
    && (rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority != 1) )
  {
    v1 = *payload;
    if ( (unsigned __int8)v1 >= 0xBu )
      LOBYTE(v1) = 9;
    rf_join_pending_ipv4_clear();
    rf_ui_show_ok_modal((const char *)dword_88E1E8, *(char **)dword_78C250[(unsigned __int8)v1], nullptr, 0);
  }
}

