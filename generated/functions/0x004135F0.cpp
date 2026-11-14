// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004135F0 rf_array24_initialize_capacity_unchecked
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native aggregate constructors, vector/matrix/24-byte array ownership, by-value stack arguments, contact copies and packed network messages): ECX array24 header plus requested capacity,RET4. Always sets count0=0,capacity4=0,base8=NULL FIRST;nonzero requested capacity (including negative) delegates413630. Zero requested capacity leaves empty header. Does not release prior base before overwriting,initialize records itself or preserve live contents;not a clear/reserve operation. No NULL/sign/size guard;no defined application return value.
void __thiscall rf_array24_initialize_capacity_unchecked(int *this, int a2)
{
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  if ( a2 )
    rf_array24_reallocate_capacity_unchecked(this, a2);
}

