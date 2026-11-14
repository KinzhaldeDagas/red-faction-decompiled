// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F61B0 rf_persona_history_get_newest_index
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): No-argument cdecl accessor: loads single DWORD rf_persona_history_newest_index into EAX and returns it unchanged. No ring-buffer validation, clamping, text/height recomputation or side effects. Native value is a32-bit integer, not float or an owned pointer.
int __cdecl rf_persona_history_get_newest_index()
{
  return rf_persona_history_newest_index;
}

