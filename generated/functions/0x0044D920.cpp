// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044D920 rf_hud_status_bitmaps_atexit_noop
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments, nominal void. Exact PUSH EBP/MOV EBP,ESP/POP EBP/RET; no calls, bitmap release, handle invalidation, global
// writes or explicit EAX assignment. Registered by status-bitmap initializer; native callback itself performs no resource cleanup. Incoming EAX unchanged.
void __cdecl rf_hud_status_bitmaps_atexit_noop()
{
  ;
}

