// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060C5B1 _rename
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(oldName,newName), MoveFileA with original
// pointers, no own validation/overwrite option/string conversion. API nonzero ->error0; API0 ->GetLastError. Error0 returns0 even when API false; nonzero dosmaperr(error),return-1.
// No new filename allocation, retry or explicit errno clear on success.
int __cdecl rename(const char *OldFilename, const char *NewFilename)
{
  DWORD LastError; // eax

  if ( MoveFileA(OldFilename, NewFilename) )
    LastError = 0;
  else
    LastError = GetLastError();
  if ( !LastError )
    return 0;
  _dosmaperr(LastError);
  return -1;
}

