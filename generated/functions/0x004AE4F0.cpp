// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AE4F0 rf_splitscreen_set_pending_and_request_panel5
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, packet14/27 registry bindings, rate-width/clamp policy, native string ABI and pregame17/18 wire layout):
// Noarg. Set globalBYTE7B25D1=1 BEFORE requesting immediate UI panel5 with force0. Return panel request delegate EAX. No existing pending/runtime/authority guard; byte remains1 even
// if unforced request is refused. Does not itself create players, set split runtime-active byte or load level.
int rf_splitscreen_set_pending_and_request_panel5()
{
  unk_7B25D1 = 1;
  return rf_ui_request_panel_immediate(5, 0);
}

