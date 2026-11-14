// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004137C0 rf_vector_array12_construct_capacity
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter registry grammar/default retention,108-byte skin ownership, allocator cookies, native stack aliases and original flag-table strings): ECX header(count0,capacity4,base8),requested capacity stackDWORD,RET4. Delegates4137E0 then returns receiverEAX. Zero capacity makes empty zero header;nonzero requests12-byte vector allocation. Does not free old storage before overwriting header or validate pointer/negative capacity;new-object construction,not live clear/reserve.
_DWORD *__thiscall rf_vector_array12_construct_capacity(_DWORD *this, int a2)
{
  rf_vector_array12_initialize_capacity_unchecked(this, a2);
  return this;
}

