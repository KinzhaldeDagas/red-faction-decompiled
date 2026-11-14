// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00456100 rf_record272_array_construct
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall(self,raw initialCapacity), RET4. Forwards raw slot unchanged to456120 using same receiver, then explicitly returns original self in EAX. No
// allocation/validation beyond delegate, no cleanup of preexisting ownership, constructor-success test or object-wide clear. Exact272-byte-record ownership follows fresh456120/456050
// chain, not old generic or locale labels.
_DWORD *__thiscall rf_record272_array_construct(_DWORD *this, int a2)
{
  rf_record272_array_initialize_header(this, a2);
  return this;
}

