// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061E520 _strpbrk
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(string, accepted-byte string), returns first
// input byte in set or NULL. Eight zero DWORD pushes create 256-bit local bitmap; BTS indexes zero-extended byte, excluding accepted-string NUL. Scan input bytewise; stop on NUL
// returning EAX0, otherwise BT tests membership and returns current pointer on first member. Empty accepted string always yieldsNULL after scanning input to NUL. High-bit bytes are
// ordinary unsigned set members. No writes, allocation, locale, NULL checks or native external memset call.
char *__cdecl strpbrk(const char *Str, const char *Control)
{
  char *result; // eax
  signed __int32 v5[9]; // [esp+0h] [ebp-24h] BYREF

  result = nullptr;
  memset(v5, 0, 32);
  while ( 1 )
  {
    LOBYTE(result) = *Control;
    if ( !*Control )
      break;
    ++Control;
    _bittestandset(v5, (unsigned int)result);
  }
  while ( 1 )
  {
    LOBYTE(result) = *Str;
    if ( !*Str )
      break;
    ++Str;
    if ( _bittest(v5, (unsigned int)result) )
      return (char *)(Str - 1);
  }
  return result;
}

