// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045E2C0 rf_two_rfstring_array16_initialize_storage
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, allocation/header ownership, exception and callback stack ABI, original rule tables and UI/flag apply
// ordering): ECX array,capacityDWORD stack,RET4. Unconditionally set count0,capacity0,dataNULL before testing input. EXACT0 skips allocation;ANY nonzero (including negative signed
// values) invokes16-byte reallocation45E160(this,input). No preexisting-data cleanup,capacity positivity/upper bound or rollback. Return this when input0,otherwise allocator
// residue;wrapper45E2A0 separately guarantees this return. Does not construct/destroy array object beyond these three DWORD fields.
char *__thiscall rf_two_rfstring_array16_initialize_storage(char *this, int a2)
{
  char *result; // eax

  result = this;
  *(_DWORD *)this = 0;
  *((_DWORD *)this + 1) = 0;
  *((_DWORD *)this + 2) = 0;
  if ( a2 )
    return rf_two_rfstring_array16_reallocate_capacity(this, a2);
  return result;
}

