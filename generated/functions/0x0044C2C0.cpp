// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044C2C0 rf_hud_message_atexit_noop
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. Native body is only PUSH EBP/MOV EBP,ESP/POP EBP/RET. No calls, field/global writes, resource release,
// stack-argument cleanup or explicit EAX assignment. Registered as44C2D0 atexit callback; does not destroy message queue/color storage. Incidental incoming EAX is unchanged; nominal
// void.
void __cdecl rf_hud_message_atexit_noop()
{
  ;
}

