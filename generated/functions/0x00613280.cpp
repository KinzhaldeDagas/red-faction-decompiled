// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00613280 _strcpy_s
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Here invalid(E) means storing errno E, calling
// invalid_parameter(NULL,NULL,NULL,0,0), and returning the stated status only if that handler returns. Cdecl(destination, unsigned capacity, source), returns errno-style0/22/34. NULL
// destination or capacity0 invalid(22), without destination write. Valid destination plus NULL source FIRST clears destination[0], then invalid(22). Otherwise forward byte copy
// including NUL; decrement remaining capacity only for nonzero copied bytes. If NUL fits, return0 and leave later destination bytes untouched. If all capacity consumed by nonzero
// bytes, clear ONLY destination[0], invalid(34); previously copied bytes beyond index0 remain. No whole-buffer wipe, overlap test, allocation or actual capacity discovery.
errno_t __cdecl strcpy_s(char *Destination, rsize_t SizeInBytes, const char *Source)
{
  rsize_t v3; // edi
  errno_t v4; // esi
  const char *v6; // esi
  char *v7; // edx
  char v8; // al

  if ( !Destination )
    goto LABEL_3;
  v3 = SizeInBytes;
  if ( !SizeInBytes )
    goto LABEL_3;
  v6 = Source;
  if ( !Source )
  {
    *Destination = 0;
LABEL_3:
    v4 = 22;
    *_errno() = 22;
LABEL_4:
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return v4;
  }
  v7 = Destination;
  do
  {
    v8 = *v6;
    *v7++ = *v6++;
    if ( !v8 )
      break;
    --v3;
  }
  while ( v3 );
  if ( !v3 )
  {
    *Destination = 0;
    *_errno() = 34;
    v4 = 34;
    goto LABEL_4;
  }
  return 0;
}

