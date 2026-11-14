// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D0F0 rf_replicator_is_armed
// UNREALRED VERIFIED [ambient-audio]: Returns true exactly when the embedded millisecond deadline is nonnegative; reset state -1 is disarmed.
bool __thiscall rf_replicator_is_armed(_DWORD *this)
{
  return *this >= 0;
}

