// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00606940 _strncpy
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(destination, source, unsigned count), returns
// original destination. Count zero reads neither string. Copies up to count bytes; source NUL is copied and all remaining destination bytes through count are filled with zero. If
// count nonzero source bytes are consumed, no extra terminator is written. Source alignment prefix uses byte copies; aligned source DWORD scan uses
// ((word+0x7EFEFEFF)^~word)&0x81010100 then confirms each byte, masks bytes after first NUL to zero and fills remaining DWORD/tail bytes. DWORD reads occur only with >=4 requested
// bytes remaining, but may read bytes after an earlier NUL in that word. Destination may be unaligned on copy path; padding can first align destination. No NULL/capacity/overlap
// checking, errno or allocation; forward copy is not an overlap-safe move.
char *__cdecl strncpy(char *Destination, const char *Source, size_t Count)
{
  size_t v3; // ecx
  size_t v4; // ebx
  const char *v5; // esi
  char *v6; // edi
  size_t v7; // ecx
  char v8; // al
  size_t v10; // ecx
  int v11; // eax
  int v12; // edx

  v3 = Count;
  if ( !Count )
    return Destination;
  v4 = Count;
  v5 = Source;
  v6 = Destination;
  if ( ((unsigned __int8)Source & 3) == 0 )
  {
    v7 = Count >> 2;
    if ( Count >> 2 )
      goto main_loop_entrance;
copy_tail_loop:
    while ( 1 )
    {
      v8 = *v5++;
      *v6++ = v8;
      if ( !v8 )
        break;
      if ( !--v4 )
        return Destination;
    }
    while ( --v4 )
finish_loop:
      *v6++ = v8;
    return Destination;
  }
  do
  {
    v8 = *v5++;
    *v6++ = v8;
    if ( !--v3 )
      return Destination;
    if ( !v8 )
    {
      while ( ((unsigned __int8)v6 & 3) != 0 )
      {
        *v6++ = 0;
        if ( !--v3 )
          return Destination;
      }
      v4 = v3;
      v10 = v3 >> 2;
      if ( !v10 )
        goto finish_loop;
      goto fill_dwords_with_EOS;
    }
  }
  while ( ((unsigned __int8)v5 & 3) != 0 );
  LOBYTE(v4) = v3;
  v7 = v3 >> 2;
  if ( !v7 )
  {
tail_loop_start:
    v4 &= 3u;
    if ( v4 )
      goto copy_tail_loop;
    return Destination;
  }
  while ( 1 )
  {
main_loop_entrance:
    v11 = (*(_DWORD *)v5 + 2130640639) ^ ~*(_DWORD *)v5;
    v12 = *(_DWORD *)v5;
    v5 += 4;
    if ( (v11 & 0x81010100) == 0 )
      goto main_loop;
    if ( !(_BYTE)v12 )
      break;
    if ( !BYTE1(v12) )
    {
      *(_DWORD *)v6 = (unsigned __int8)v12;
      goto fill_with_EOS_dwords;
    }
    if ( ((unsigned int)&unk_FF0000 & v12) == 0 )
    {
      *(_DWORD *)v6 = (unsigned __int16)v12;
      goto fill_with_EOS_dwords;
    }
    if ( (v12 & 0xFF000000) == 0 )
    {
      *(_DWORD *)v6 = v12;
      goto fill_with_EOS_dwords;
    }
main_loop:
    *(_DWORD *)v6 = v12;
    v6 += 4;
    if ( !--v7 )
      goto tail_loop_start;
  }
  *(_DWORD *)v6 = 0;
fill_with_EOS_dwords:
  v6 += 4;
  v8 = 0;
  v10 = v7 - 1;
  if ( v10 )
  {
fill_dwords_with_EOS:
    v8 = 0;
    do
    {
      *(_DWORD *)v6 = 0;
      v6 += 4;
      --v10;
    }
    while ( v10 );
  }
  v4 &= 3u;
  if ( v4 )
    goto finish_loop;
  return Destination;
}

