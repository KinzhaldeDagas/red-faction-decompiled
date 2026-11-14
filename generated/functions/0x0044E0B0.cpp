// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044E0B0 rf_hud_ammo_bitmaps_atexit_noop
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments, nominal void. Exact four-instruction frame prologue/epilogue and plainRET. No bitmap release/retain, handle
// reset, memory writes, calls or explicit EAX assignment.44E0C0 registers this callback after loading ammo bitmaps; registration does not make this no-op release those resources.
// Incoming EAX unchanged.
void __cdecl rf_hud_ammo_bitmaps_atexit_noop()
{
  ;
}

