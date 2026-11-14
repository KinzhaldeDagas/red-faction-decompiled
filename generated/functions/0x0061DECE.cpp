// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061DECE _strcat_s
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Here invalid(E) means storing errno E, calling
// invalid_parameter(NULL,NULL,NULL,0,0), and returning the stated status only if that handler returns. Cdecl(destination, unsigned total capacity, source), returns0/22/34. NULL
// destination or zero capacity invalid(22) with no write. NULL source clears destination[0] before invalid(22), even if destination initially unterminated. Otherwise scan at most
// capacity bytes for destination NUL; not found clears ONLY destination[0], invalid(22). Append source including NUL using remaining capacity, decrementing remaining only on nonzero
// byte. Full nonzero exhaustion clears ONLY destination[0], invalid(34); existing prefix and partial append beyond first byte remain. Success0 leaves later capacity untouched. No
// overlap validation, allocation, rollback or whole-buffer fill.
errno_t __cdecl strcat_s(char *Destination, rsize_t SizeInBytes, const char *Source)
{
  rsize_t v3; // edi
  errno_t v4; // esi
  const char *v6; // esi
  char *v7; // edx
  char v8; // cl

  if ( !Destination )
    goto LABEL_3;
  v3 = SizeInBytes;
  if ( !SizeInBytes )
    goto LABEL_3;
  v6 = Source;
  if ( !Source )
    goto LABEL_6;
  v7 = Destination;
  do
  {
    if ( !*v7 )
      break;
    ++v7;
    --v3;
  }
  while ( v3 );
  if ( !v3 )
  {
LABEL_6:
    *Destination = 0;
LABEL_3:
    v4 = 22;
    *_errno() = 22;
LABEL_4:
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return v4;
  }
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

