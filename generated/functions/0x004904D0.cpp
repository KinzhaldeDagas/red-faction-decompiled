// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004904D0 rf_string_array8_destroy_storage
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Thiscall12-byte RFString array header. If backingDWORD8 nonnull invokes45DF10(backing,flags3): destroys cookie-count8-byte RFStrings and raw-deletes allocation atbacking-4. Does
// NOT clear header pointer/count/capacity afterward; this is destructor storage release,not reusable reset. Empty path EAX incidental; no element-pointer ownership beyond string
// buffers.
char *__thiscall rf_string_array8_destroy_storage(_DWORD *this)
{
  char *result; // eax

  result = (char *)this;
  if ( *(this + 2) )
  {
    result = (char *)*(this + 2);
    if ( result )
      return rf_rfstring_delete_with_scalar_or_vector_flags((char *)*(this + 2), 3);
  }
  return result;
}

