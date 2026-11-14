// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061AB95 __alloc_osfhnd
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Descriptor record
// R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31); handle DWORD+0, flags BYTE+4, lookahead BYTE+5, lock-init DWORD+8, critical section+12, encoding BYTE+36; fd limit DWORD2021E20.
// Noargs, allocates/reserves descriptor and returns fd with record CS HELD, or-1. mtinitlocknum11 failure ->-1; thenlock11/armouterSEH,scan blockindices0..63,32records
// per2048-byteblock. Existing block: unsignedaddress scan for flagsopen1 clear; if initfield0 lock10/arminnerSEH/recheck/initCS(spin4000). Here initfield increments ONLY onSUCCESS;
// failure sets sticky localfailure1. Innerfinallyunlock10; stickyfailure persists across remaining scan, suppressing all further EXISTING-slot acquisition.
// OtherwiseEnterrecordCS,recheckopen,release if raced; stillfree ->flagsBYTE1,handle-1,return block*32+recordindex whileCSheld. NULLblock: calloc_crt(32,64); failure stops.
// Storeblock andINCREMENT globalfdlimit32; initialize everyrecord handle-1,flags0,lookahead10,init0. Mark firstrecordflags1 BEFORE lock_fhandle(firstfd); FALSE sets return-1 WITHOUT
// clearing reservation/freeing block/decrementinglimit. This newblockpath stillruns evenifstickyfailure set earlier. Outerfinally releasesglobal11 only; no own errno, invalid
// callback or automatic release of returned record CS. Scope65EF60 has outerhandler61AD26 andnestedhandler61AC62.
int _alloc_osfhnd()
{
  int v0; // edi
  unsigned int v2; // esi
  char *v3; // eax
  int v4; // [esp+14h] [ebp-24h]
  int v5; // [esp+1Ch] [ebp-1Ch]

  v5 = -1;
  v0 = 0;
  v4 = 0;
  if ( !_mtinitlocknum(11) )
    return -1;
  _lock(11);
  while ( v0 < 64 )
  {
    v2 = unk_2021E40[v0];
    if ( !v2 )
    {
      v3 = (char *)_calloc_crt(0x20u, 0x40u);
      if ( v3 )
      {
        unk_2021E40[v0] = (int)v3;
        MEMORY[0x2021E20] += 32;
        while ( (unsigned int)v3 < unk_2021E40[v0] + 2048 )
        {
          v3[4] = 0;
          *(_DWORD *)v3 = -1;
          v3[5] = 10;
          *((_DWORD *)v3 + 2) = 0;
          v3 += 64;
        }
        v5 = 32 * v0;
        *(_BYTE *)(unk_2021E40[(32 * v0) >> 5] + 4) = 1;
        if ( !__lock_fhandle(32 * v0) )
          v5 = -1;
      }
      break;
    }
    while ( v2 < unk_2021E40[v0] + 2048 )
    {
      if ( (*(_BYTE *)(v2 + 4) & 1) == 0 )
      {
        if ( !*(_DWORD *)(v2 + 8) )
        {
          _lock(10);
          if ( !*(_DWORD *)(v2 + 8) )
          {
            if ( __crtInitCritSecAndSpinCount((LPCRITICAL_SECTION)(v2 + 12), 0xFA0u) )
              ++*(_DWORD *)(v2 + 8);
            else
              v4 = 1;
          }
          _unlock(10);
        }
        if ( !v4 )
        {
          EnterCriticalSection((LPCRITICAL_SECTION)(v2 + 12));
          if ( (*(_BYTE *)(v2 + 4) & 1) == 0 )
          {
            *(_BYTE *)(v2 + 4) = 1;
            *(_DWORD *)v2 = -1;
            v5 = 32 * v0 + ((int)(v2 - unk_2021E40[v0]) >> 6);
            break;
          }
          LeaveCriticalSection((LPCRITICAL_SECTION)(v2 + 12));
        }
      }
      v2 += 64;
    }
    if ( v5 != -1 )
      break;
    ++v0;
  }
  _unlock(11);
  return v5;
}

