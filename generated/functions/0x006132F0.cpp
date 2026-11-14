// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006132F0 _strlen
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(string), returns unsigned byte distance to
// first NUL, excluding it. Byte prefix aligns source to four; then DWORD-at-a-time ((word+0x7EFEFEFF)^~word)&0x81010100 detection and explicit byte tests in increasing order select
// exact terminator position. DWORD containing NUL is read whole and can include up to three bytes beyond terminator. No NULL guard, bound, writes, allocation or external strlen call;
// preserves stack and uses only volatile EAX/ECX/EDX.
size_t __cdecl strlen(const char *Str)
{
  const char *v1; // ecx
  int v3; // eax
  int v4; // eax

  v1 = Str;
  if ( ((unsigned __int8)Str & 3) == 0 )
    goto main_loop_3;
  do
  {
    if ( !*v1++ )
      return v1 - 1 - Str;
  }
  while ( ((unsigned __int8)v1 & 3) != 0 );
  while ( 1 )
  {
    do
    {
main_loop_3:
      v3 = (*(_DWORD *)v1 + 2130640639) ^ ~*(_DWORD *)v1;
      v1 += 4;
    }
    while ( (v3 & 0x81010100) == 0 );
    v4 = *((_DWORD *)v1 - 1);
    if ( !(_BYTE)v4 )
      break;
    if ( !BYTE1(v4) )
      return v1 - 3 - Str;
    if ( ((unsigned int)&unk_FF0000 & v4) == 0 )
      return v1 - 2 - Str;
    if ( (v4 & 0xFF000000) == 0 )
      return v1 - 1 - Str;
  }
  return v1 - 4 - Str;
}

