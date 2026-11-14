// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00606580 _memset
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(destination, int value, unsigned byte count),
// returns original destination. Count zero returns before dereferencing destination. Only low eight value bits are used. Zero byte plus count >=256 and global2021F64 nonzero
// tail-jumps VEC_memzero61028B with original three stack slots; its second slot is ignored. Scalar path emits up to three prefix bytes to align destination to four, replicates value
// into all DWORD bytes, REP STOSD for count/4, then 0..3 trailing bytes. No buffer validation, allocation, errno or terminator policy; REP path assumes incoming direction flag clear.
// Vector helper behavior is delegated; it is not selected for nonzero fill bytes.
void *__cdecl memset(void *a1, int Val, size_t Size)
{
  size_t v3; // edx
  int v4; // eax
  _BYTE *v6; // edi
  int v7; // ecx
  size_t v8; // ecx
  unsigned int v9; // ecx

  v3 = Size;
  if ( !Size )
    return a1;
  LOBYTE(v4) = Val;
  if ( !(_BYTE)Val && Size >= 0x100 && unk_2021F64 )
    return (void *)_VEC_memzero((int)a1, Val, Size);
  v6 = a1;
  if ( Size < 4 )
    goto LABEL_17;
  v7 = -(int)a1 & 3;
  if ( v7 )
  {
    v3 = Size - v7;
    do
    {
      *v6++ = Val;
      --v7;
    }
    while ( v7 );
  }
  v4 = 16843009 * (unsigned __int8)Val;
  v8 = v3;
  v3 &= 3u;
  v9 = v8 >> 2;
  if ( !v9 || (memset32(v6, v4, v9), v6 += 4 * v9, v3) )
  {
LABEL_17:
    do
    {
      *v6++ = v4;
      --v3;
    }
    while ( v3 );
  }
  return a1;
}

