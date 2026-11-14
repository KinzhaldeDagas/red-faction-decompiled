// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061E4D0 _strcspn
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(string, reject-byte string), returns unsigned
// length of initial prefix containing no reject byte. Build a 256-bit local set with eight zero DWORD pushes and BTS on zero-extended byte values; reject-string terminating NUL is
// excluded. Scan input bytes until NUL or first member, incrementing count before each input test from initial UINT_MAX. Empty reject set therefore returns string length; NUL is
// never counted. No string writes, allocation, locale processing, input validation or external memset despite lifted pseudo expression.
size_t __cdecl strcspn(const char *Str, const char *Control)
{
  unsigned int v2; // eax
  size_t v5; // ecx
  signed __int32 v7[9]; // [esp+0h] [ebp-24h] BYREF

  v2 = 0;
  memset(v7, 0, 32);
  while ( 1 )
  {
    LOBYTE(v2) = *Control;
    if ( !*Control )
      break;
    ++Control;
    _bittestandset(v7, v2);
  }
  v5 = -1;
  do
  {
    ++v5;
    LOBYTE(v2) = *Str;
    if ( !*Str )
      break;
    ++Str;
  }
  while ( !_bittest(v7, v2) );
  return v5;
}

