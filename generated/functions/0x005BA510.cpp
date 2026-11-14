// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BA510 rf_rfa_get_or_load_raw_buffer
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): If clip raw pointer+120 isNULL, calls raw-file loader5BB510 with clip address as filename (record starts with name) andNULL external buffer. Returns pointer+120 after call, possibly stillNULL on failure. No magic/version/size validation, refcount change or reliable successful-load guarantee. All sampling helpers dereference this result without independent NULL checks.
unsigned __int8 *__thiscall rf_rfa_get_or_load_raw_buffer(void *this)
{
  if ( !*((_DWORD *)this + 30) )
    rf_rfa_load_raw_file((const char *)this, nullptr);
  return *((unsigned __int8 **)this + 30);
}

