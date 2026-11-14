// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060B76A __mkdir
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(path),0/-1. CreateDirectoryA(path,NULL), no
// own path/NULL validation. BOOL true sets local error0; false reads GetLastError. Error0 returns0 EVEN if API was false with LastError0; nonzero calls dosmaperr and returns-1. No
// allocation, retry or explicit success errno clear.
int __cdecl _mkdir(const char *Path)
{
  DWORD LastError; // eax

  if ( CreateDirectoryA(Path, nullptr) )
    LastError = 0;
  else
    LastError = GetLastError();
  if ( !LastError )
    return 0;
  _dosmaperr(LastError);
  return -1;
}

