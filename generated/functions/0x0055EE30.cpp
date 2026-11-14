// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055EE30 rf_matrix48_copy_raw_return_self
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): ECX destination plus source, RET4. Copies exactly48bytes with rep movsd and returns destination. Does not call row constructors, check matrix layout or compute values. Exact same-base safe; overlapping ranges are not memmove-protected.
void *__thiscall rf_matrix48_copy_raw_return_self(void *this, const void *a2)
{
  qmemcpy(this, a2, 0x30u);
  return this;
}

