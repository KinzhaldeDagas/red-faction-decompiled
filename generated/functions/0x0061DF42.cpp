// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061DF42 _strncpy_s
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Here invalid(E) means storing errno E, calling
// invalid_parameter(NULL,NULL,NULL,0,0), and returning the stated status only if that handler returns. Cdecl(destination, unsigned capacity, source, unsigned max count),
// returns0/22/34 or truncation80. Exact (count0,destinationNULL,capacity0) returns0; other NULL destination or capacity0 invalid(22). Valid destination with count0 clears
// destination[0] and returns0 without checking source. Nonzero count plus NULL source clears destination[0], invalid(22). Normal count: copy bytes including NUL, stop on NUL,
// capacity exhaustion, or requested nonzero-byte count exhausted. On count exhaustion with capacity left, write extra NUL and return0. If capacity exhausted first, clear ONLY
// destination[0], invalid(34); no rollback of other copied bytes. Sentinel count UINT_MAX instead copies until NUL or capacity exhausted; exhausted case overwrites
// destination[capacity-1] with NUL and returns80, preserving truncated prefix, WITHOUT own errno write or invalid-handler call. A fitting NUL always returns0. No zero-padding or
// overlap detection.
errno_t __cdecl strncpy_s(char *Destination, rsize_t SizeInBytes, const char *Source, rsize_t MaxCount)
{
  rsize_t v5; // edi
  errno_t v6; // esi
  const char *v7; // edx
  char *v8; // eax
  char v9; // cl
  char v10; // cl

  if ( MaxCount )
  {
    if ( !Destination )
    {
LABEL_7:
      v6 = 22;
      *_errno() = 22;
LABEL_8:
      _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
      return v6;
    }
  }
  else if ( !Destination )
  {
    if ( !SizeInBytes )
      return 0;
    goto LABEL_7;
  }
  v5 = SizeInBytes;
  if ( !SizeInBytes )
    goto LABEL_7;
  if ( !MaxCount )
  {
    *Destination = 0;
    return 0;
  }
  v7 = Source;
  if ( !Source )
  {
    *Destination = 0;
    goto LABEL_7;
  }
  v8 = Destination;
  if ( MaxCount == -1 )
  {
    do
    {
      v9 = *v7;
      *v8++ = *v7++;
      if ( !v9 )
        break;
      --v5;
    }
    while ( v5 );
  }
  else
  {
    do
    {
      v10 = *v7;
      *v8++ = *v7++;
      if ( !v10 )
        break;
      if ( !--v5 )
        break;
      --MaxCount;
    }
    while ( MaxCount );
    if ( !MaxCount )
      *v8 = 0;
  }
  if ( v5 )
    return 0;
  if ( MaxCount != -1 )
  {
    *Destination = 0;
    *_errno() = 34;
    v6 = 34;
    goto LABEL_8;
  }
  Destination[SizeInBytes - 1] = 0;
  return 80;
}

