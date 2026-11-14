// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055EF20 rf_game_clock_pause_depth_decrement
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): Decrements DWORD17F1110 and returns new value. No lower-bound check: decrementing0 yields-1, which still pauses game clock advancement because gate tests nonzero. Does not directly update either clock or resume callbacks.
int rf_game_clock_pause_depth_decrement()
{
  return --unk_17F1110;
}

