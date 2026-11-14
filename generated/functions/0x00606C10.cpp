// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00606C10 _strrchr
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(string, int character), returns last matching
// low-eight-bit byte pointer or NULL. With incoming DF clear, REPNE SCASB first finds NUL using ECX=UINT_MAX; constructs length+1, points at terminator, sets DF and scans backward
// over terminator and all preceding bytes. Therefore character zero returns the terminator. Final compare distinguishes no match; all normal return paths CLD before restoring
// EDI/EBP. No allocation, locale, NULL validation, bound or string mutation. Existing decompiler strlen expression is lifted REP scanning, not a native strlen call.
char *__cdecl strrchr(const char *Str, int Ch)
{
  unsigned int v2; // ecx
  const char *v3; // edi
  bool v4; // zf
  char *v5; // edi

  v2 = strlen(Str) + 1;
  v3 = &Str[v2 - 1];
  do
  {
    if ( !v2 )
      break;
    v4 = *v3-- == (unsigned __int8)Ch;
    --v2;
  }
  while ( !v4 );
  v5 = (char *)(v3 + 1);
  if ( *v5 == (_BYTE)Ch )
    return v5;
  else
    return nullptr;
}

