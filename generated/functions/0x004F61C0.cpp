// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F61C0 rf_persona_history_set_newest_index
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): Cdecl one DWORD argument: stores exactly that value into rf_persona_history_newest_index, returns same EAX. No validation/clamp, modulo/ring normalization, history-slot allocation/free or updates to other history counters. Negative and out-of-range values are not rejected by this accessor; higher-level append/render logic supplies its own constraints.
int __cdecl rf_persona_history_set_newest_index(int newest_index)
{
  rf_persona_history_newest_index = newest_index;
  return newest_index;
}

