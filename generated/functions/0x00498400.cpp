// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00498400 rf_client_apply_ctf_flag_returned_payload
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF variable state serialization, client payload state/timer ordering, native function boundaries and reliable packet queue admission): 
// Recovered original function [498400,498568), cdecl(payload). Requires runtime mode1, authority0, game mode1 and nonzero initialized77D6E2. Reads four payload bytes selector,id,red
// captures,blue captures and stores counts before lookup; no payload bounds/null validation. Packet34 association follows exact sender payload layout; no static incoming xrefs
// currently.
// Always plays event66 then invokes return notification(optional resolved player, RAW selector); failed lookup uses generic returned wording. Player id is zero-extended and FF is
// still passed to lookup without special rejection, so it can resolve an actual id255 player. Afterwards selector EXACTLY1 chooses red, all other bytes blue: clears carrier through
// setter(NULL) FIRST, then return_flag_home(selected, sound1). The setter arms25000ms but home reset immediately cancels BOTH return timers and arms shared500ms cooldown; this order
// differs from captured-payload receiver498100. Duplicate player-found/not-found branches have identical carrier/home effects. No client score/contribution-byte award or clear;
// setter ABI remains one pointer despite extra caller literal1.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, compiled registry/dispatcher and native ABI refinement): Original PE descriptor at0x00662AE0 registers opcode34 (ctf_flag_returned), callback0x00498400. Native dispatcher49FB50 indirectly calls it with(payload,source endpoint),8-byte caller cleanup,after envelope/source admission; handler receives NO payload length. Thus absence of IDA direct call/xrefs does not imply a dormant handler. Compiled registration and dispatch edge verified independently of earlier paired-layout inference; actual invocation still depends on runtime admission.
void __cdecl rf_client_apply_ctf_flag_returned_payload(const unsigned __int8 *payload)
{
  unsigned __int8 v1; // [esp+Ah] [ebp-Ah]
  char v2; // [esp+Bh] [ebp-9h]
  _DWORD *v3; // [esp+10h] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1
    && !rf_multiplayer_server_authority
    && rf_multiplayer_game_mode_get() == 1
    && byte_77D6E2 )
  {
    v1 = *payload;
    v2 = payload[1];
    byte_77D6E0 = payload[2];
    byte_77D6E1 = payload[3];
    v3 = rf_player_find_by_network_id(v2);
    rf_gamesound_play_event(66, 0, 0.0, 1.0);
    rf_ctf_flag_return_notification((int)v3, v1);
    if ( v3 )
    {
      if ( v1 == 1 )
      {
LABEL_8:
        rf_ctf_red_carrier_set(0);
        rf_ctf_return_flag_home(1, 1);
        return;
      }
    }
    else if ( v1 == 1 )
    {
      goto LABEL_8;
    }
    rf_ctf_blue_carrier_set(0);
    rf_ctf_return_flag_home(0, 1);
  }
}

