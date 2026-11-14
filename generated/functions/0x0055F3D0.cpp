// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F3D0 rf_timestamp_is_armed_nonnegative
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): Returns byte boolean whether stored signed deadline DWORD>=0. No clock read, elapsed test, bounds or wrapping adjustment. Every negative value is unarmed, not just-1.
unsigned __int8 __thiscall rf_timestamp_is_armed_nonnegative(const int *this)
{
  return *this >= 0;
}

