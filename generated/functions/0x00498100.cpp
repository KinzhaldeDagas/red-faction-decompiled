// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00498100 rf_client_apply_ctf_flag_captured_payload
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF variable state serialization, client payload state/timer ordering, native function boundaries and reliable packet queue admission): 
// Recovered original native function [498100,49822B), caller-cleaned one payload pointer. Requires runtime mode1, authority exactly0, game mode1 and nonzero initialized77D6E2; no
// pointer/length validation. Reads selector BYTE0, player id BYTE1, red/blue counts BYTE2/3; stores both counts before looking up player. Player id is zero-extended; FF is passed
// through lookup with no explicit sentinel rejection. Packet32 association is inferred from exact paired sender layout; no static incoming xrefs in current database.
// Always plays event63, then return_flag_home(selector==1, sound1): only selector EXACTLY1 means red, every other byte blue. If player lookup succeeds, capture notification receives
// RAW selector. Finally clears selected carrier through setter(NULL), AFTER the home reset. Home reset first cancels both return timers and arms500ms cooldown, then selected setter
// rearms its return timer for25000ms even though home bit is set. Unknown player still triggers sound/home/carrier/timer changes; no frag/assist/contribution-byte awards in this
// client routine. Native extra stack literal1 passed around setters is not a second setter parameter.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, compiled registry/dispatcher and native ABI refinement): Original PE descriptor at0x00662AC8 registers opcode32 (ctf_flag_captured), callback0x00498100. Native dispatcher49FB50 indirectly calls it with(payload,source endpoint),8-byte caller cleanup,after envelope/source admission; handler receives NO payload length. Thus absence of IDA direct call/xrefs does not imply a dormant handler. Compiled registration and dispatch edge verified independently of earlier paired-layout inference; actual invocation still depends on runtime admission.
void __cdecl rf_client_apply_ctf_flag_captured_payload(const unsigned __int8 *payload)
{
  unsigned __int8 v1; // [esp+Bh] [ebp-Dh]
  _DWORD *v2; // [esp+Ch] [ebp-Ch]
  char v3; // [esp+13h] [ebp-5h]

  if ( rf_multiplayer_runtime_mode == 1
    && !rf_multiplayer_server_authority
    && rf_multiplayer_game_mode_get() == 1
    && byte_77D6E2 )
  {
    v1 = *payload;
    v3 = payload[1];
    byte_77D6E0 = payload[2];
    byte_77D6E1 = payload[3];
    v2 = rf_player_find_by_network_id(v3);
    rf_gamesound_play_event(63, 0, 0.0, 1.0);
    rf_ctf_return_flag_home(v1 == 1, 1);
    if ( v2 )
      rf_ctf_flag_capture_notification((int)v2, v1);
    if ( v1 == 1 )
      rf_ctf_red_carrier_set(0);
    else
      rf_ctf_blue_carrier_set(0);
  }
}

