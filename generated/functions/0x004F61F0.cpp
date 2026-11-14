// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F61F0 rf_persona_history_entry_at
// UNREALRED VERIFIED [persona-lifecycle-20260923]: Returns base 0x8A40FE + index*264 with no bounds check or modulo. Entry layout is corroborated by append stores and history-render signed loads: 260 text bytes, signed short persona index at +0x104, signed short layout height at +0x106. Caller-owned ring arithmetic limits normal indices to 0..79.
rf_persona_history_entry *__cdecl rf_persona_history_entry_at(int index)
{
  return (rf_persona_history_entry *)((char *)&rf_persona_history_entries + 264 * index);
}

