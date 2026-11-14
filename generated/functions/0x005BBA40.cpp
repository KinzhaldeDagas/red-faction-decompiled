// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BBA40 rf_text_file_refill_buffer
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, buffered text reader/writer branches, allocation callers and original-PE newline literal): Object layout: FILE*0,buffer4,end8,cursor12,remaining16,capacity20,flags24. If remaining nonzero and cursor>buffer, copies remaining bytes down with memcpy (NOT memmove), shifts end back and resets cursor; empty buffer resets cursor/end to base. EOF flag mask0x1 skips further fread. Otherwise reads capacity-(end-base) bytes into end, advances end and remaining by bytes read; any short read sets EOF flag, without distinguishing file error. Always returns0, including fread failure; no capacity, pointer, underflow or overlap validation. Zero-capacity read does not latch EOF and can leave line reader spinning.
int __thiscall rf_text_file_refill_buffer(int this)
{
  size_t v2; // eax
  unsigned int ElementCount; // [esp+4h] [ebp-8h]

  if ( *(_DWORD *)(this + 16) && *(_DWORD *)(this + 12) > *(_DWORD *)(this + 4) )
  {
    memcpy(*(void **)(this + 4), *(const void **)(this + 12), *(_DWORD *)(this + 16));
    *(_DWORD *)(this + 8) -= *(_DWORD *)(this + 12) - *(_DWORD *)(this + 4);
    *(_DWORD *)(this + 12) = *(_DWORD *)(this + 4);
  }
  else if ( !*(_DWORD *)(this + 16) )
  {
    *(_DWORD *)(this + 12) = *(_DWORD *)(this + 4);
    *(_DWORD *)(this + 8) = *(_DWORD *)(this + 12);
  }
  if ( (*(_DWORD *)(this + 24) & 1) != 0 )
    return 0;
  ElementCount = *(_DWORD *)(this + 20) - (*(_DWORD *)(this + 8) - *(_DWORD *)(this + 4));
  v2 = fread(*(void **)(this + 8), 1u, ElementCount, *(FILE **)this);
  *(_DWORD *)(this + 8) += v2;
  *(_DWORD *)(this + 16) += v2;
  if ( v2 < ElementCount )
    *(_DWORD *)(this + 24) |= 1u;
  return 0;
}

