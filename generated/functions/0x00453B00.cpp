// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00453B00 rf_endgame_blackout_complete_request_panel19
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): No arguments. Calls446100(panelID19,forceLOWBYTE0), caller pops8 and forwards full request-helper
// EAX. No immediate stack commit, game/endgame-text load, validity check, retry or normalized success. Accepted request returns19; native rejected-request residues remain
// path-dependent.
int rf_endgame_blackout_complete_request_panel19()
{
  return rf_ui_request_panel_immediate(19, 0);
}

