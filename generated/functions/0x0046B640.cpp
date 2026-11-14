// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046B640 rf_gameplay_difficulty_choice_load_active
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, video/performance/gameplay call chains, original gamma constants and compiled labels, native
// x87/byte/stack/callback ABI): Noarg. Copy active difficultyDWORD6612A4 into UI selectedDWORD6F7F54,return same fullDWORD. Does NOT copy configured6612A8,change active/configured
// difficulty,validate range,apply or save. Complements pointer group commit policy;no runtime gate here.
int rf_gameplay_difficulty_choice_load_active()
{
  unk_6F7F54 = dword_6612A4;
  return dword_6612A4;
}

