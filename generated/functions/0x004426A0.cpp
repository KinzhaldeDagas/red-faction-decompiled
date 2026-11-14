// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004426A0 rf_request_panel2_unforced
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): No arguments. Calls446100 with cdecl DWORD words(panel/action2,forceBYTE0), caller pops8, forwards EAX
// unchanged. No own pending-panel, runtime, authority, pause or player gate; immediate-request helper owns acceptance/rejection and deferred-flag mutations. No additional side
// effects, status normalization or retry.
int rf_request_panel2_unforced()
{
  return rf_ui_request_panel_immediate(2, 0);
}

