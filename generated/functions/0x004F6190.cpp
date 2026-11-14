// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F6190 rf_persona_history_get_count
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): No-argument cdecl accessor: loads single DWORD rf_persona_history_count into EAX and returns it unchanged. No ring-buffer validation, clamping, text/height recomputation or side effects. Native value is a32-bit integer, not float or an owned pointer.
int __cdecl rf_persona_history_get_count()
{
  return rf_persona_history_count;
}

