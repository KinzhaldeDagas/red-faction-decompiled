// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00539800 rf_record16_array_construct_capacity
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Thiscall12-byte array header,count0/capacity4/backing8;calls539820(initialCapacity),returns receiver. No per-element construction or payload initialization;nonzero capacity allocates raw16-byte records.
_DWORD *__thiscall rf_record16_array_construct_capacity(_DWORD *this, int a2)
{
  rf_record16_array_initialize_capacity(this, a2);
  return this;
}

