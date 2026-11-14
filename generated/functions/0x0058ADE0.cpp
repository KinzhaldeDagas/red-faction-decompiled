// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058ADE0 rf_mouse_button_record_construct_deadline
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): Constructor used with16-byte mouse button records. Initializes ONLY deadline DWORD at this+12 to-1 through rf_clock_deadline_construct_invalid and returns this. Held/double-click bytes and press/release DWORDs remain untouched here. The inherited Concurrency::SchedulerCore label/type is false; this is a tiny record constructor, with no scheduler/vtable initialization. Corrected to opaque pointer ABI without changing local type definitions.
void *__thiscall rf_mouse_button_record_construct_deadline(void *this)
{
  rf_clock_deadline_construct_invalid((int *)this + 3);
  return this;
}

