// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F1D0 rf_unpaused_timestamp_construct_invalid
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): Only writes signed DWORD0=-1 and returns receiver. Adjacent timer family arms against unpaused clock663E94; constructor itself reads no clock and schedules nothing.
int *__thiscall rf_unpaused_timestamp_construct_invalid(int *this)
{
  *this = -1;
  return this;
}

