// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045E300 rf_two_rfstring_array16_destruct_storage
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, allocation/header ownership, exception and callback stack ABI, original rule tables and UI/flag apply
// ordering): ECX array. If dataDWORD8 nonNULL,invoke pair-delete45DF80(data,3);otherwise no destructor call. Does NOT zero count/capacity/data or free the array object. Thus distinct
// from clear-and-release45DE40;stored data remains stale after deletion and repeated use is not made safe by this body. ReturnEAX incidental this/backing/header pointer,possibly
// freed. No count guard;header controls full allocated destruction extent.
char *__thiscall rf_two_rfstring_array16_destruct_storage(char **this)
{
  char *result; // eax

  result = (char *)this;
  if ( *(this + 2) )
  {
    result = *(this + 2);
    if ( result )
      return rf_two_rfstring_delete_with_scalar_or_vector_flags(*(this + 2), 3);
  }
  return result;
}

