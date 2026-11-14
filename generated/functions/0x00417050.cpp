// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417050 rf_clutter_skin_array_release_storage
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter registry grammar/default retention,108-byte skin ownership, allocator cookies, native stack aliases and original flag-table strings): Thiscall header,no stackargs. Writescount0=0/capacity4=0 FIRST;if base8 nonNULL,invokes4170D0(base,3) to destroy every cookie-capacity record and free raw allocation,then setsbase8=NULL. Does NOT use just oldlogicalcount for destruction or free pointed glare entries;returnsreceiverEAX. Does not allocate,validatecookie or transactionally restoreheader if destructor fails.
_DWORD *__thiscall rf_clutter_skin_array_release_storage(_DWORD *this)
{
  _DWORD *result; // eax

  result = this;
  *this = 0;
  *(this + 1) = 0;
  if ( *(this + 2) )
  {
    rf_clutter_skin108_deleting_destructor((char *)*(this + 2), 3);
    *(this + 2) = 0;
    return this;
  }
  return result;
}

