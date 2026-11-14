// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00609480 _strchr
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): CRT cdecl(string,intValue),returns first matching byte pointer orNULL;value converted to low8bits. Alignment prefix and four-byte fast scan preserve crucial comparison order:matched BYTE checked BEFORE zero-termination rejection. Therefore searching value0 returns pointer to terminatingNUL,notNULL. Parser579890 uses this result as hex-loop predicate and has no separateNUL test,so its hex-EOF path advances past source terminator. No allocation,locale folding,application length validation or owned-pointer transfer.
char *__cdecl strchr(const char *Str, int Val)
{
  const char *v2; // edx
  char v3; // cl
  int v4; // ecx
  int v5; // esi
  int v6; // eax
  unsigned int v7; // eax
  unsigned int v9; // eax
  unsigned int v10; // eax

  v2 = Str;
  if ( ((unsigned __int8)Str & 3) != 0 )
  {
    while ( 1 )
    {
      v3 = *v2++;
      if ( v3 == (_BYTE)Val )
        return (char *)(v2 - 1);
      if ( !v3 )
        return nullptr;
      if ( ((unsigned __int8)v2 & 3) == 0 )
        goto main_loop_1;
    }
  }
  else
  {
    while ( 1 )
    {
main_loop_1:
      while ( 1 )
      {
        v4 = (((unsigned __int8)Val << 8)
            | (unsigned __int8)Val
            | ((((unsigned __int8)Val << 8) | (unsigned __int8)Val) << 16))
           ^ *(_DWORD *)v2;
        v5 = *(_DWORD *)v2 + 2130640639;
        v6 = v5 ^ ~*(_DWORD *)v2;
        v2 += 4;
        if ( (((v4 + 2130640639) ^ ~v4) & 0x81010100) != 0 )
          break;
        v7 = v6 & 0x81010100;
        if ( v7 && (((unsigned int)&unk_1010100 & v7) != 0 || (v5 & 0x80000000) == 0) )
          return nullptr;
      }
      v9 = *((_DWORD *)v2 - 1);
      if ( (_BYTE)v9 == (_BYTE)Val )
        break;
      if ( !(_BYTE)v9 )
        return nullptr;
      if ( BYTE1(v9) == (_BYTE)Val )
        return (char *)(v2 - 3);
      if ( !BYTE1(v9) )
        return nullptr;
      v10 = HIWORD(v9);
      if ( (_BYTE)v10 == (_BYTE)Val )
        return (char *)(v2 - 2);
      if ( !(_BYTE)v10 )
        return nullptr;
      if ( BYTE1(v10) == (_BYTE)Val )
        return (char *)(v2 - 1);
      if ( !BYTE1(v10) )
        return nullptr;
    }
    return (char *)(v2 - 4);
  }
}

