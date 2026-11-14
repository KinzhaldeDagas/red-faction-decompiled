// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00416F70 rf_inline_dword_array4_element_address_unchecked
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter registry grammar/default retention,108-byte skin ownership, allocator cookies, native stack aliases and original flag-table strings): ECX inline array plus stackindex,RET4. Returns receiver+4+4*index with32-bit arithmetic. Does not dereference receiver/result or check logicalcount,capacity4,negativeindex,NULL,overflow;no mutation.
int __thiscall rf_inline_dword_array4_element_address_unchecked(void *this, int a2)
{
  return (int)this + 4 * a2 + 4;
}

