// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045DF80 rf_two_rfstring_delete_with_scalar_or_vector_flags
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, allocation/header ownership, exception and callback stack ABI, original rule tables and UI/flag apply
// ordering): ECX two-RFString16-byte record/first array record,stack flags,RET4. Bit2 ->EH vector destructor iterator(base,16,headerDWORD[base-4],two_rfstring_prefix_destroy);bit1
// additionally operator delete(base-4),return header address. Without bit2,destroy single pair atbase;bit1 operator delete(base),returnbase. Other bits ignored;no
// NULL/header/count/pointer validation or container metadata mutation. Extent is allocation header count,not current container used count. Return may be freed pointer. Pair-array
// clear/reallocation/destructor call with3.
char *__thiscall rf_two_rfstring_delete_with_scalar_or_vector_flags(char *this, char a2)
{
  if ( (a2 & 2) != 0 )
  {
    `eh vector destructor iterator'(
      this,
      0x10u,
      *((_DWORD *)this - 1),
      (void (__thiscall *)(void *))rf_two_rfstring_prefix_destroy);
    if ( (a2 & 1) != 0 )
      operator delete(this - 4);
    return this - 4;
  }
  else
  {
    rf_two_rfstring_prefix_destroy(this);
    if ( (a2 & 1) != 0 )
      operator delete(this);
    return this;
  }
}

