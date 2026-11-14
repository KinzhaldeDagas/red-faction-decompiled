// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F1B0 rf_clock_deadline_construct_invalid
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): thiscall one-DWORD constructor: writes -1 at [ECX] and returns ECX in EAX. Used at positional instance+76, the deadline field later passed to clock_deadline_set_wrapped_offset. The inherited Replicator class label does not describe the observed clock field usage. Does not initialize adjacent memory.
int *__thiscall rf_clock_deadline_construct_invalid(int *this)
{
  *this = -1;
  return this;
}

