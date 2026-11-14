// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006070F8 __store_str
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Register copier: EAX points remainingDWORD, EDX sourceCString, ECX points destination-pointer slot. While remaining!=0 and current sourcebyte!=NUL, copy
// onebyte to *destination, increment destination slot, advance local source, decrement remaining with32-bit wrap. Does NOT append/copy NUL or update a caller source slot. Initial
// remaining0 reads no sourcebyte. Negative raw remaining is not rejected; no NULL/storage-capacity check beyond counter. Returns ORIGINAL counter-address EAX; ESI/EDI preserved, DL
// scratch holds byte.
_DWORD *__usercall _store_str@<eax>(_DWORD *result@<eax>, _BYTE *a2@<edx>, _DWORD *a3@<ecx>)
{
  for ( ; *result; --*result )
  {
    if ( !*a2 )
      break;
    *(_BYTE *)(*a3)++ = *a2++;
  }
  return result;
}

