// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00453CE0 rf_extras_menu_request_credits_panel23
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): No arguments. Call446460 with raw cdecl slots(panel23,BYTE0,BYTE0), caller cleans12 and forwards
// helperEAX23. Deferred helper unconditionally arms push1/pop0, pending23 and both per-panel flags0; does not test an existing request. No immediate credits initialization,
// current-stack pop, sound, playback or own acceptance gate.
int rf_extras_menu_request_credits_panel23()
{
  return rf_ui_request_panel_deferred(23, 0, 0);
}

