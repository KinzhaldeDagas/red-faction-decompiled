// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060980C _flsall
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Cdecl mode. Lock globalindex1,armouterSEH; signed i0..<LIVE2022F80
// reads LIVEtable2021F68. SkipNULLslots orflags&0x83==0. Lock_file2(i,slot),arminnerSEH,RE-FETCH slot/flags. mode==1 flushes each active FILE andcounts result!= -1;mode==0 flushes
// ONLY writebit2 andrecords-1 ifanyfail;every othermode stillscans/locks butdoesno flush,returns0. Innerfinally re-fetches currenttableentry andunlock_file2;outerfinally
// unlockglobal1,includingunwind. Returncount onlymode1,else status0/-1. No stabletable/entry/count snapshot, deletion, capacity validation or rollback of previouslyflushed streams.
int __cdecl flsall(int a1)
{
  int i; // esi
  int *v2; // eax
  int v3; // eax
  int v4; // ecx
  int result; // eax
  int v6; // [esp+10h] [ebp-24h]
  int v7; // [esp+18h] [ebp-1Ch]

  v7 = 0;
  v6 = 0;
  _lock(1);
  for ( i = 0; i < unk_2022F80; ++i )
  {
    v2 = (int *)(unk_2021F68 + 4 * i);
    if ( *v2 )
    {
      v3 = *v2;
      if ( (*(_BYTE *)(v3 + 12) & 0x83) != 0 )
      {
        _lock_file2(i, v3);
        v4 = *(_DWORD *)(*(_DWORD *)(unk_2021F68 + 4 * i) + 12);
        if ( (v4 & 0x83) != 0 )
        {
          if ( a1 == 1 )
          {
            if ( _fflush_nolock(*(FILE **)(unk_2021F68 + 4 * i)) != -1 )
              ++v7;
          }
          else if ( !a1 && (v4 & 2) != 0 && _fflush_nolock(*(FILE **)(unk_2021F68 + 4 * i)) == -1 )
          {
            v6 = -1;
          }
        }
        _unlock_file2(i, *(_DWORD *)(unk_2021F68 + 4 * i));
      }
    }
  }
  _unlock(1);
  result = v7;
  if ( a1 != 1 )
    return v6;
  return result;
}

