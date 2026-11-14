// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004133B0 rf_array24_construct_capacity
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native aggregate constructors, vector/matrix/24-byte array ownership, by-value stack arguments, contact copies and packed network messages): ECX array24 header plus requested capacity stack DWORD,RET4. Delegates4135F0(receiver,capacity),returns receiverEAX. Initializes header count0/capacity0/baseNULL,then optionally allocates24-byte records when capacity nonzero. Used for physics-state P252 sphere collection;does not free previous storage before header reset or own pointed objects. No NULL or negative-capacity guard.
_DWORD *__thiscall rf_array24_construct_capacity(_DWORD *this, int a2)
{
  rf_array24_initialize_capacity_unchecked(this, a2);
  return this;
}

