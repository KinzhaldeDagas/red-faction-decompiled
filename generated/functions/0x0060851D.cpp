// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060851D _remove
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(filename), DeleteFileA(filename) with no own
// pointer/path validation. Nonzero API result selects error0; zero API result calls GetLastError. Error0 returns0, INCLUDING API false with LastError0. Nonzero error passes raw value
// to dosmaperr then returns-1. No own invalid handler, retry, string conversion, free or manual errno-clear on success.
int __cdecl remove(const char *FileName)
{
  DWORD LastError; // eax

  if ( DeleteFileA(FileName) )
    LastError = 0;
  else
    LastError = GetLastError();
  if ( !LastError )
    return 0;
  _dosmaperr(LastError);
  return -1;
}

