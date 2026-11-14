// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00621C5B __chsize_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Descriptor record
// R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31); handle DWORD+0, flags BYTE+4, lookahead BYTE+5, lock-init DWORD+8, critical section+12, encoding BYTE+36; fd limit DWORD2021E20.
// Cdecl(fd,raw64-bit requestedsize),returns CURRENT errno VALUE on detectedfailure, not-1; success0. No ownfd/negative-length/overflowvalidation orlock. lseeki64_nolock(fd,0,CUR)
// saves64-bitposition; exact64-bit-1 returns*errno. SeekEND,failreturns*errno WITHOUTrestore. Compute wrapped64 delta=requested-end usingSUB/SBB andnativeJS/JG/unsignedlowtests.
// Growth: HeapAlloc(GetProcessHeap(),8,4096); NULLerrno12/returncurrenterrno,positionleftatEND. Save setmode_nolock(fd,0x8000) result,IGNOREmodefailure semantics.
// Loopwrite_nolock(fd,zeroBuffer,min(remaining,4096)); ONLY-1isfailure,0doesnotprogress. Signextendother32-bitreturns andsubtractfromremaining64 withnativeSUB/SBBsign/zero tests.
// Onwrite-1,doserrno5 forceserrno13; markfailure. Alwaysnormalgrowthcleanup callssetmode(fd,SAVEDmodeRETURN),HeapFree(GetProcessHeap(),0,buffer),IGNOREresults. Savedmode is lossy for
// encoding kinds; restorationneednotrecreateoriginalencoding. Growthfailure returnscurrenterrno WITHOUT restoringposition; earlierwritespersist.
// Shrink:seekrequestedSET;failreturns*errno. SetEndOfFile(get_osfhandle(fd)) BOOLnormalized0success/-1failure; failureerrno13 thenstoreGetLastError RAWdoserrno,returncurrenterrno
// WITHOUTpositionrestore. Equalorcompletedgrowth/shrink attemptsseekSAVEDpositionSET (evenbeyondnewEOF),failure*errno,success0. No exception-finally cleanup, truncate rollback or
// guaranteednonzeroerrno on everydelegatefailure.
int __cdecl _chsize_nolock(int FileHandle, __int64 a2)
{
  __int64 v2; // rax
  int v3; // edi
  unsigned int v4; // esi
  HANDLE ProcessHeap; // eax
  DWORD v7; // eax
  int v8; // eax
  bool v9; // of
  unsigned int v10; // kr08_4
  int v11; // esi
  HANDLE v12; // eax
  __int64 v13; // rax
  void *osfhandle; // eax
  unsigned int *v15; // esi
  __int64 v16; // rax
  __int64 v17; // [esp+Ch] [ebp-18h]
  __int64 v18; // [esp+14h] [ebp-10h]
  int v19; // [esp+1Ch] [ebp-8h]
  void *lpMem; // [esp+20h] [ebp-4h]

  HIDWORD(v18) = 0;
  v17 = _lseeki64_nolock(FileHandle, 0, 0, 1u);
  if ( (HIDWORD(v17) & (unsigned int)v17) == 0xFFFFFFFF )
    return *_errno();
  v2 = _lseeki64_nolock(FileHandle, 0, 0, 2u);
  if ( (HIDWORD(v2) & (unsigned int)v2) == 0xFFFFFFFF )
    return *_errno();
  v3 = (unsigned __int64)(a2 - v2) >> 32;
  v4 = a2 - v2;
  if ( v3 >= 0 && (a2 >= v2 && (unsigned __int64)(a2 - v2) >> 32 != 0 || v4) )
  {
    ProcessHeap = GetProcessHeap();
    lpMem = HeapAlloc(ProcessHeap, 8u, 0x1000u);
    if ( !lpMem )
    {
      *_errno() = 12;
      return *_errno();
    }
    v19 = _setmode_nolock(FileHandle, 0x8000);
    while ( 1 )
    {
      v7 = v3 < 0 || v3 <= 0 && v4 < 0x1000 ? v4 : 4096;
      v8 = _write_nolock(FileHandle, lpMem, v7);
      if ( v8 == -1 )
        break;
      v9 = __OFSUB__(__PAIR64__(v3, v4), v8);
      v10 = v4 - v8;
      v3 = (__PAIR64__(v3, v4) - v8) >> 32;
      v4 -= v8;
      if ( v3 < 0 || (v3 < 0) ^ v9 | (v3 == 0) && !v10 )
      {
        v11 = 0;
        goto LABEL_20;
      }
    }
    if ( *__doserrno() == 5 )
      *_errno() = 13;
    v11 = -1;
    HIDWORD(v18) = -1;
LABEL_20:
    _setmode_nolock(FileHandle, v19);
    v12 = GetProcessHeap();
    HeapFree(v12, 0, lpMem);
    goto LABEL_28;
  }
  if ( v3 < 0 )
  {
    v13 = _lseeki64_nolock(FileHandle, a2, SHIDWORD(a2), 0);
    if ( (HIDWORD(v13) & (unsigned int)v13) == 0xFFFFFFFF )
      return *_errno();
    osfhandle = (void *)_get_osfhandle(FileHandle);
    v18 = SetEndOfFile(osfhandle) - 1;
    if ( (HIDWORD(v18) & (unsigned int)v18) == 0xFFFFFFFF )
    {
      *_errno() = 13;
      v15 = __doserrno();
      *v15 = GetLastError();
      v11 = v18;
LABEL_28:
      if ( (HIDWORD(v18) & v11) == 0xFFFFFFFF )
        return *_errno();
    }
  }
  v16 = _lseeki64_nolock(FileHandle, v17, SHIDWORD(v17), 0);
  if ( (HIDWORD(v16) & (unsigned int)v16) == 0xFFFFFFFF )
    return *_errno();
  return 0;
}

