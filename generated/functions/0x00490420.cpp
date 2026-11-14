// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00490420 rf_string_array8_initialize_capacity
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Thiscall12-byte RFString array header,stack requested capacity,RET4. Writes count0,capacity0,backingNULL. ANY nonzero requested capacity delegates45E020,which allocates
// cookie-prefixed8-byte RFString elements and sets capacity. Does not release existing backing before overwriting header,validate negative capacity or populate count. Zero-capacity
// path EAX receiver; nonzero EAX delegate artifact.
char *__thiscall rf_string_array8_initialize_capacity(char *this, int a2)
{
  char *result; // eax

  result = this;
  *(_DWORD *)this = 0;
  *((_DWORD *)this + 1) = 0;
  *((_DWORD *)this + 2) = 0;
  if ( a2 )
    return rf_rfstring_array8_reallocate_capacity(this, a2);
  return result;
}

