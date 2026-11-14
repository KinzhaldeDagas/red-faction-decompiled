// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044B230 rf_hud_message_register_noop_atexit_callback
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. Push44B250 and call CRTatexit once, then return full EAX registration status. No message state initialization,
// cleanup invocation, retry or rollback on registration failure; repeated calls add registrations. Callback44B250 is itself a native no-op.
int rf_hud_message_register_noop_atexit_callback()
{
  return atexit(rf_hud_message_noop_atexit_callback);
}

