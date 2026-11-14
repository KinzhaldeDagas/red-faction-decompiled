// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00549FB0 rf_dword_array_construct_capacity
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Calls54A070(receiver,initialCapacity),returns receiver. Header count0,capacity4,backing8;raw4-byte entries,also used for pointer arrays. Capacity0 yields empty zero header;no pointed-object ownership or per-entry construction.
_DWORD *__thiscall rf_dword_array_construct_capacity(_DWORD *this, int a2)
{
  rf_dword_array_initialize_capacity(this, a2);
  return this;
}

