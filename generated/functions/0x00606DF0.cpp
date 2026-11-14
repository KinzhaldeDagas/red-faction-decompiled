// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00606DF0 _strncat
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(destination, source, unsigned max appended
// bytes), returns original destination. Count zero returns before scanning or modifying either string. Otherwise find destination NUL using byte alignment then aligned DWORD zero
// detection; copy at most count source bytes there. Source NUL stops immediately and is retained; if exactly count nonzero bytes are copied, explicitly append one NUL after them. No
// zero-padding of unused count. Source DWORD loads require >=4 count remaining; the terminating DWORD may read bytes after NUL. Destination scan has no capacity bound. Forward
// writes, no NULL/overlap/capacity validation, errno or allocation; caller must provide room for existing prefix plus copied bytes plus terminator.
char *__cdecl strncat(char *Destination, const char *Source, size_t Count)
{
  size_t v3; // ecx
  char *v4; // edi
  int v6; // eax
  int v7; // eax
  char *v8; // edi
  const char *v9; // esi
  char v10; // bl
  size_t v11; // ecx
  int v12; // edx
  char v13; // dl
  int v15; // eax

  v3 = Count;
  if ( !Count )
    return Destination;
  v4 = Destination;
  if ( ((unsigned __int8)Destination & 3) == 0 )
    goto find_end_of_front_string_loop;
  do
  {
    if ( !*v4++ )
    {
start_byte_3:
      v8 = v4 - 1;
      goto copy_start;
    }
  }
  while ( ((unsigned __int8)v4 & 3) != 0 );
  while ( 1 )
  {
    do
    {
find_end_of_front_string_loop:
      v6 = (*(_DWORD *)v4 + 2130640639) ^ ~*(_DWORD *)v4;
      v4 += 4;
    }
    while ( (v6 & 0x81010100) == 0 );
    v7 = *((_DWORD *)v4 - 1);
    if ( !(_BYTE)v7 )
      break;
    if ( !BYTE1(v7) )
    {
      v8 = v4 - 3;
      goto copy_start;
    }
    if ( ((unsigned int)&unk_FF0000 & v7) == 0 )
    {
      v8 = v4 - 2;
      goto copy_start;
    }
    if ( (v7 & 0xFF000000) == 0 )
      goto start_byte_3;
  }
  v8 = v4 - 4;
copy_start:
  v9 = Source;
  if ( ((unsigned __int8)Source & 3) == 0 )
  {
    v10 = Count;
    v11 = Count >> 2;
    if ( Count >> 2 )
      goto main_loop_entrance_0;
tail_loop_start_0:
    v3 = v10 & 3;
    if ( (v10 & 3) != 0 )
    {
      while ( 1 )
      {
        v13 = *v9++;
        *v8++ = v13;
        if ( !v13 )
          break;
        if ( !--v3 )
          goto empty_counter;
      }
    }
    else
    {
empty_counter:
      *v8 = v3;
    }
    return Destination;
  }
  do
  {
    LOBYTE(v12) = *v9++;
    if ( !(_BYTE)v12 )
    {
LABEL_26:
      *v8 = v12;
      return Destination;
    }
    *v8++ = v12;
    if ( !--v3 )
      goto empty_counter;
  }
  while ( ((unsigned __int8)v9 & 3) != 0 );
  v10 = v3;
  v11 = v3 >> 2;
  if ( !v11 )
    goto tail_loop_start_0;
  while ( 1 )
  {
main_loop_entrance_0:
    v15 = (*(_DWORD *)v9 + 2130640639) ^ ~*(_DWORD *)v9;
    v12 = *(_DWORD *)v9;
    v9 += 4;
    if ( (v15 & 0x81010100) == 0 )
      goto main_loop_0;
    if ( !(_BYTE)v12 )
      goto LABEL_26;
    if ( !BYTE1(v12) )
      break;
    if ( ((unsigned int)&unk_FF0000 & v12) == 0 )
    {
      *(_WORD *)v8 = v12;
      v8[2] = 0;
      return Destination;
    }
    if ( (v12 & 0xFF000000) == 0 )
    {
      *(_DWORD *)v8 = v12;
      return Destination;
    }
main_loop_0:
    *(_DWORD *)v8 = v12;
    v8 += 4;
    if ( !--v11 )
      goto tail_loop_start_0;
  }
  *(_WORD *)v8 = (unsigned __int8)v12;
  return Destination;
}

