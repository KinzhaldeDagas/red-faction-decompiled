// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00413840 rf_matrix_array36_initialize_capacity_unchecked
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter registry grammar/default retention,108-byte skin ownership, allocator cookies, native stack aliases and original flag-table strings): Thiscall header plus capacity,RET4. Zeroes count0/capacity4/base8,then on ANY nonzero request invokes4134E0. Does not release old pointer before losing it or validate sign/size. Does not write identity/default matrix elements;delegate constructors are no-ops.
void __thiscall rf_matrix_array36_initialize_capacity_unchecked(int *this, int a2)
{
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  if ( a2 )
    rf_matrix_array36_reallocate_capacity_unchecked(this, a2);
}

