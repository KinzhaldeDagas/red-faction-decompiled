// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054A070 rf_dword_array_initialize_capacity
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Writes header count0=0,capacity4=0,backing8=NULL;nonzero initialCapacity invokes549FD0. Does not free old backing before overwriting or construct elements. Intended new-object initialization,not clear/reserve of an existing live array.
void __thiscall rf_dword_array_initialize_capacity(_DWORD *this, int a2)
{
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  if ( a2 )
    rf_dword_array_reallocate_capacity_unchecked(this, a2);
}

