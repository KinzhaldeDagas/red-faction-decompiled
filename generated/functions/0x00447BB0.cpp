// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00447BB0 rf_ui_noop_447bb0
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Reachable body consists only of pushEBP/movEBP,ESP/popEBP/RET. Ignores all registers/stack arguments, leaves EAX unchanged, has
// no object/global mutation and no callee stack cleanup. Current447BE0 callers explicitly push a0/1 DWORD and reclaim it, but this stub reads none.
void rf_ui_noop_447bb0()
{
  ;
}

