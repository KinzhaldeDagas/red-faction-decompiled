// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00456120 rf_record272_array_initialize_header
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall(receiver,raw initialCapacity), RET4. Stores DWORD0 count=0, DWORD+4 capacity=0, DWORD+8 backing=0 in that order; ANY nonzero raw capacity, including
// negative signed bits, calls456050. Zero skips allocator. No destruction/free of old backing before overwrite, whole-element clear or nonnegative validation. Delegate returns
// void/incidental EAX; this initializer does not promise receiver result.
void __thiscall rf_record272_array_initialize_header(_DWORD *this, int a2)
{
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  if ( a2 )
    rf_record272_array_reallocate_shallow(this, a2);
}

