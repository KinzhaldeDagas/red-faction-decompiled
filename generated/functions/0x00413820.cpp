// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00413820 rf_matrix_array36_construct_capacity
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter registry grammar/default retention,108-byte skin ownership, allocator cookies, native stack aliases and original flag-table strings): ECX header plus requested capacity DWORD,RET4. Delegates413840 and returns receiverEAX. Header0/4/8=count/capacity/base;zero request empty,nonzero uses36-byte matrix array allocator. No old-storage release or NULL/sign guard;matrix constructors do not zero matrix values.
int *__thiscall rf_matrix_array36_construct_capacity(int *this, int a2)
{
  rf_matrix_array36_initialize_capacity_unchecked(this, a2);
  return this;
}

