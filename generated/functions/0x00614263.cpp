// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00614263 __close_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Descriptor record
// R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31); handle DWORD+0, flags BYTE+4, lookahead BYTE+5, lock-init DWORD+8, critical section+12, encoding BYTE+36; fd limit DWORD2021E20.
// Cdecl(fd), no own range/open validation before get_osfhandle delegate. Getter -1 skips OS close and sets savederror0. Otherwise if fd1 with sibling2 open OR fd2 with sibling1 open,
// compare handles2 and1; equal skips CloseHandle to preserve shared standard handle. Other paths call CloseHandle(get_osfhandle(fd)), save GetLastError only onFALSE. ALWAYS call
// free_osfhnd(fd),IGNORE result, then unconditionally write record flags byte0, even after OS close failure. Nonzero savederror ->dosmaperr/-1, else0. Therefore failed CloseHandle
// still invalidates CRT slot, and getter/free-helper errors can coexist with return0 if savederror0 (e.g. open slot storing-1). No own lock, retry or descriptor/header rollback.
int __cdecl _close_nolock(int FileHandle)
{
  intptr_t osfhandle; // edi
  void *v2; // eax
  DWORD LastError; // edi

  if ( _get_osfhandle(FileHandle) == -1
    || (FileHandle == 1 && (*(_BYTE *)(unk_2021E40[0] + 132) & 1) != 0
     || FileHandle == 2 && (*(_BYTE *)(unk_2021E40[0] + 68) & 1) != 0)
    && (osfhandle = _get_osfhandle(2), _get_osfhandle(1) == osfhandle)
    || (v2 = (void *)_get_osfhandle(FileHandle), CloseHandle(v2)) )
  {
    LastError = 0;
  }
  else
  {
    LastError = GetLastError();
  }
  _free_osfhnd(FileHandle);
  *(_BYTE *)(unk_2021E40[FileHandle >> 5] + ((FileHandle & 0x1F) << 6) + 4) = 0;
  if ( !LastError )
    return 0;
  _dosmaperr(LastError);
  return -1;
}

