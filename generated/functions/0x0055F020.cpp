// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F020 rf_replicator_reset
// UNREALRED VERIFIED [ambient-audio]: Disarms the embedded millisecond deadline by writing -1.
_DWORD *__thiscall rf_replicator_reset(_DWORD *this)
{
  *this = -1;
  return this;
}

