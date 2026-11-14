// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044C2D0 rf_hud_message_register_atexit_noop
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. Push exact callback44C2C0 and call CRT atexit6060D2 with one cdecl slot, clean4 and forward returned full EAX.
// Callback is independently verified no-op; wrapper does not initialize/clear message records, register per-record destructors or check atexit result. Repeated calls attempt repeated
// registrations; no own once guard, allocation or cleanup loop.
int rf_hud_message_register_atexit_noop()
{
  return atexit(rf_hud_message_atexit_noop);
}

