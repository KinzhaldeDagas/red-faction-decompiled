// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060C2C2 _strncmp
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(first string, second string, unsigned max
// count). Count zero returns0 without dereference. Compare sequential bytes until mismatch, first-string NUL, or count exhausted; return exact (unsigned byte first)-(unsigned byte
// second), range -255..255, not normalized sign. For counts>4 use unrolled groups of four BYTE loads and test each before next, then bounded byte tail; there are no speculative DWORD
// source loads in this body. Equal terminating NUL yields0. No locale folding, NULL validation, allocation or writes.
int __cdecl strncmp(const char *Str1, const char *Str2, size_t MaxCount)
{
  const char *v4; // ecx
  const char *v5; // eax
  char v6; // dl
  char v7; // dl
  char v8; // dl
  char v9; // dl
  int v10; // eax
  int v11; // ecx
  size_t v12; // [esp+4h] [ebp-4h]

  v12 = 0;
  if ( !MaxCount )
    return 0;
  if ( MaxCount <= 4 )
  {
    v4 = Str2;
    v5 = Str1;
    goto LABEL_23;
  }
  v4 = Str2;
  v5 = Str1;
  do
  {
    v6 = *v5;
    v5 += 4;
    v4 += 4;
    if ( !v6 || v6 != *(v4 - 4) )
    {
      v10 = *((unsigned __int8 *)v5 - 4);
      v11 = *((unsigned __int8 *)v4 - 4);
      return v10 - v11;
    }
    v7 = *(v5 - 3);
    if ( !v7 || v7 != *(v4 - 3) )
    {
      v10 = *((unsigned __int8 *)v5 - 3);
      v11 = *((unsigned __int8 *)v4 - 3);
      return v10 - v11;
    }
    v8 = *(v5 - 2);
    if ( !v8 || v8 != *(v4 - 2) )
    {
      v10 = *((unsigned __int8 *)v5 - 2);
      v11 = *((unsigned __int8 *)v4 - 2);
      return v10 - v11;
    }
    v9 = *(v5 - 1);
    if ( !v9 || v9 != *(v4 - 1) )
    {
      v10 = *((unsigned __int8 *)v5 - 1);
      v11 = *((unsigned __int8 *)v4 - 1);
      return v10 - v11;
    }
    v12 += 4;
  }
  while ( v12 < MaxCount - 4 );
  while ( 1 )
  {
LABEL_23:
    if ( v12 >= MaxCount )
      return 0;
    if ( !*v5 || *v5 != *v4 )
      break;
    ++v5;
    ++v4;
    ++v12;
  }
  v10 = *(unsigned __int8 *)v5;
  v11 = *(unsigned __int8 *)v4;
  return v10 - v11;
}

