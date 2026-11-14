// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055EF60 rf_timestamp4_invalidate
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): Writes DWORD0=-1 and returns receiver. Does not stop an asynchronous job, release resources, read clocks or change pause depth; paired timer helpers interpret negative value as unarmed.
_DWORD *__thiscall rf_timestamp4_invalidate(_DWORD *this)
{
  *this = -1;
  return this;
}

