// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061D8EE __lseeki64_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Descriptor record
// R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31); handle DWORD+0, flags BYTE+4, lookahead BYTE+5, lock-init DWORD+8, critical section+12, encoding BYTE+36; fd limit DWORD2021E20.
// Cdecl(fd,offsetLow,offsetHigh,raw origin), return64-bit EDX:EAX. get_osfhandle==-1 ->errno9 and bothreturnhalves-1. Otherwise SetFilePointer(handle,offsetLow,&localHigh,origin),
// initializedhigh=callerhigh. Only lowUINT_MAX triggers GetLastError; nonzero error dosmaperr and64-bit-1. Otherwise cleardescriptor EOFflag0x2 andreturn raw updatedhigh/low,
// including lowUINT_MAX whenLastError0. No pre-clearingLastError, method/negativeoffset validation, own fd-range guard orlock; old split-four-slot type retained, native ABI
// includes64-bit low/high pair.
__int64 __cdecl _lseeki64_nolock(int FileHandle, LONG a2, int a3, DWORD dwMoveMethod)
{
  void *osfhandle; // eax
  DWORD LastError; // eax
  _BYTE *v7; // eax
  __int64 lDistanceToMove; // [esp+8h] [ebp-8h] BYREF

  HIDWORD(lDistanceToMove) = a3;
  osfhandle = (void *)_get_osfhandle(FileHandle);
  if ( osfhandle == (void *)-1 )
  {
    *_errno() = 9;
    return -1;
  }
  LODWORD(lDistanceToMove) = SetFilePointer(osfhandle, a2, (PLONG)&lDistanceToMove + 1, dwMoveMethod);
  if ( (_DWORD)lDistanceToMove == -1 )
  {
    LastError = GetLastError();
    if ( LastError )
    {
      _dosmaperr(LastError);
      return -1;
    }
  }
  v7 = (_BYTE *)(unk_2021E40[FileHandle >> 5] + ((FileHandle & 0x1F) << 6) + 4);
  *v7 &= ~2u;
  return lDistanceToMove;
}

