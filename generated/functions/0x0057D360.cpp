// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057D360 rf_stream_adapter_bind_memory
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Sets mode=1, borrowed memory base+8, length+16, cursor+12=0, version+80=0 and error+84=0. Optional label copied with strncpy60 to+20 and byte+79 forcedNUL; absent label clears only first byte. Does not allocate/free memory or validate length. Return register is either receiver or label-copy destination, not a success flag.
char *__thiscall rf_stream_adapter_bind_memory(void *this, int a2, int a3, char *Source)
{
  char *result; // eax

  *(_DWORD *)this = 1;
  *((_DWORD *)this + 2) = a2;
  *((_DWORD *)this + 4) = a3;
  *((_DWORD *)this + 3) = 0;
  result = (char *)this;
  *((_DWORD *)this + 20) = 0;
  *((_DWORD *)this + 21) = 0;
  if ( Source )
  {
    result = strncpy((char *)this + 20, Source, 0x3Cu);
    *((_BYTE *)this + 79) = 0;
  }
  else
  {
    *((_BYTE *)this + 20) = 0;
  }
  return result;
}

