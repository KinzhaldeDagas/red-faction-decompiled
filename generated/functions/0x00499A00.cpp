// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00499A00 rf_client_apply_ctf_flag_dropped_payload
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF variable state serialization, client payload state/timer ordering, native function boundaries and reliable packet queue admission): 
// Recovered original function [499A00,499B92), cdecl(payload). Requires runtime mode1, authority0, game mode1 and nonzero initialized77D6E2, with no payload length/null validation.
// Reads15 payload bytes: selector BYTE0, red/blue capture BYTE1/2, XYZ floats at3/7/11, copying both counts before pose application. Packet35 association follows exact paired sender
// layout; no static incoming xrefs currently.
// Selector EXACTLY1 selects red; every other byte selects blue. Clears selected carrier via setter(NULL), arming its25000ms return timer and clearing definition bit2, then sets
// definition bit2 back and copies XYZ ONLY to common position+60. Does not synchronize current+228,predicted+240,bounds,common/physical matrices or room; does not clear instance home
// bit200 when the previous flag is home. This limited state mutation differs from snapshot receiver498E50. No cooldown reset, sound, notification or score/contribution-byte award.
// Extra caller stack literal1 does not change carrier setter one-pointer ABI.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, compiled registry/dispatcher and native ABI refinement): Original PE descriptor at0x00662AEC registers opcode35 (ctf_flag_dropped), callback0x00499A00. Native dispatcher49FB50 indirectly calls it with(payload,source endpoint),8-byte caller cleanup,after envelope/source admission; handler receives NO payload length. Thus absence of IDA direct call/xrefs does not imply a dormant handler. Compiled registration and dispatch edge verified independently of earlier paired-layout inference; actual invocation still depends on runtime admission.
void __cdecl rf_client_apply_ctf_flag_dropped_payload(const unsigned __int8 *payload)
{
  float v1[3]; // [esp+0h] [ebp-2Ch] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-20h] BYREF
  unsigned __int8 v3; // [esp+1Bh] [ebp-11h]
  float source[3]; // [esp+1Ch] [ebp-10h] BYREF
  int v5; // [esp+28h] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1
    && !rf_multiplayer_server_authority
    && rf_multiplayer_game_mode_get() == 1
    && byte_77D6E2 )
  {
    v3 = 1;
    v5 = 0;
    v3 = *payload;
    v5 = 1;
    byte_77D6E0 = payload[1];
    v5 = 2;
    byte_77D6E1 = payload[2];
    v5 = 3;
    rf_vector3_default_construct_noop(source);
    source[0] = *(float *)&payload[v5];
    v5 += 4;
    source[1] = *(float *)&payload[v5];
    v5 += 4;
    source[2] = *(float *)&payload[v5];
    v5 += 4;
    if ( v3 == 1 )
    {
      rf_ctf_red_carrier_set(0);
      *(_DWORD *)(*(_DWORD *)(dword_77D6E4 + 660) + 68) |= 2u;
      rf_vector_copy((float *)(dword_77D6E4 + 60), copy_result, source);
    }
    else
    {
      rf_ctf_blue_carrier_set(0);
      *(_DWORD *)(*(_DWORD *)(dword_77D6E8 + 660) + 68) |= 2u;
      rf_vector_copy((float *)(dword_77D6E8 + 60), v1, source);
    }
  }
}

