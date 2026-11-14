// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B3510 rf_motion_sample_buffer_clear_snap_flag
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native buffered-motion insertion/sampling, asymmetric WORD time differences, temporary physics snapshot/restore and native list guards): ECX buffer,no stackargs. Clears ONLY flags1320 bit2 using AND0xFFFFFFFD,returns bufferEAX. No count/cursor/clock/sample/curve writes or validation.
_DWORD *__thiscall rf_motion_sample_buffer_clear_snap_flag(_DWORD *this)
{
  *(this + 330) &= ~2u;
  return this;
}

