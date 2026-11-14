// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00453B20 rf_frontend_request_credits_or_endgame_blackout
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): One cdecl required NUL Cstring pointer; no NULL/length guard. First CRT case-insensitive FULL
// compare with original 'call_credits'. Equality directly446100(panel23,force0), forwarding full request EAX and leaving global endgame name6F1508 unchanged; no blackout. Other
// strings forward-copy every byte INCLUDING NUL to global6F1508 with no capacity/overlap/alias guard. Then4E25F0(GLOBAL local-player POINTER87C318,FLOAT1.5,callbackADDRESS453B00),
// forwarding delegate EAX. No local-player NULL guard, duration validation or callback execution here. Blackout delegate stores its progress/duration/callback and returns; panel19
// request occurs only when later native transition invokes callback, not synchronously. Copy is committed before delegate even on later failure; no pause/authority/name lookup or
// rollback.
int __cdecl rf_frontend_request_credits_or_endgame_blackout(char *String1)
{
  char v2; // [esp+Bh] [ebp-Dh]
  char *v3; // [esp+10h] [ebp-8h]
  char *v4; // [esp+14h] [ebp-4h]

  if ( !_stricmp(String1, "call_credits") )
    return rf_ui_request_panel_immediate(23, 0);
  v4 = String1;
  v3 = unk_6F1508;
  do
  {
    v2 = *v4;
    *v3++ = *v4++;
  }
  while ( v2 );
  return rf_player_begin_blackout_transition(
           rf_local_fpgun_player,
           1.5,
           (int)rf_endgame_blackout_complete_request_panel19);
}

