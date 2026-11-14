// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055EF00 rf_game_clock_pause_depth_increment
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): False ___inc_tmpoff CRT label. Increments signed DWORD17F1110 and returns new value; nonzero pauses game clock663E90 updates while663E94 continues. No time-step or other object mutation, maximum-depth guard or synchronization.
int rf_game_clock_pause_depth_increment()
{
  return ++unk_17F1110;
}

