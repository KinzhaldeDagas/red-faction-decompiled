// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004137E0 rf_vector_array12_initialize_capacity_unchecked
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter registry grammar/default retention,108-byte skin ownership, allocator cookies, native stack aliases and original flag-table strings): Thiscall header plus requested capacity,RET4. Always writes count/capacity/base=0 first;nonzero request delegates4133D0. Does not free previousbase,initialize vector contents itself,clamp negative capacity or preserve live contents. Underlying allocator saturates unsigned byte-size overflow,but this function has no own range validation.
void __thiscall rf_vector_array12_initialize_capacity_unchecked(int *this, int a2)
{
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  if ( a2 )
    rf_vector_array12_reallocate_capacity_unchecked(this, a2);
}

