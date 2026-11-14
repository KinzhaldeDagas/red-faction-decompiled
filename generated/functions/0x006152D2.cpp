// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006152D2 __getstream
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): FILE32 offsets
// ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28; dynamic critical section+32. Noargs, returns LOCKED reusable/new FILE pointer orNULL. Lockglobal1,armSEH; signed
// index0..<LIVE2022F80 with LIVEpointertable2021F68. Existing nonNULL slot: require flags&0x83==0 ANDflags&0x8000==0. For indices3..19 only, mtinitlocknum(index+16); failure stops
// entire scan/NULL. lock_file2(index,slot),re-fetch slot and recheck0x83. Stillinactive transfers stream lock to caller; otherwise unlock_file2 andcontinue. NULLslot:
// malloc_crt56,store in currenttable; failure stops scan. Initialize CS atFILE+32 spin4000; failure freeFILE,clear slot,stop. Success EnterCriticalSection,flags0,selectFILE. Selected
// FILE flags&=0x8000; ptr,cnt,base,tmpname0,fd-1; charbuf andbufsiz not initialized here. Finally release ONLY global1 and return selected pointer with perstream lock HELD. No
// wraparound search, table growth, standard0..2 exclusion, rollback of partially initialized fields or perstream-unlock-on-throw finally.
_DWORD *_getstream()
{
  _DWORD *v0; // edi
  int i; // esi
  int v2; // eax
  int v3; // eax
  int v4; // esi

  v0 = nullptr;
  _lock(1);
  for ( i = 0; i < dword_2022F80; ++i )
  {
    v2 = unk_2021F68 + 4 * i;
    if ( !*(_DWORD *)v2 )
    {
      v4 = 4 * i;
      *(_DWORD *)(v4 + unk_2021F68) = _malloc_crt(0x38u);
      if ( *(_DWORD *)(v4 + unk_2021F68) )
      {
        if ( __crtInitCritSecAndSpinCount((LPCRITICAL_SECTION)(*(_DWORD *)(v4 + unk_2021F68) + 32), 0xFA0u) )
        {
          EnterCriticalSection((LPCRITICAL_SECTION)(*(_DWORD *)(v4 + unk_2021F68) + 32));
          v0 = *(_DWORD **)(v4 + unk_2021F68);
          v0[3] = 0;
        }
        else
        {
          free(*(void **)(v4 + unk_2021F68));
          *(_DWORD *)(v4 + unk_2021F68) = 0;
        }
      }
      break;
    }
    v3 = *(_DWORD *)(*(_DWORD *)v2 + 12);
    if ( (v3 & 0x83) == 0 && (v3 & 0x8000) == 0 )
    {
      if ( (unsigned int)(i - 3) <= 0x10 && !_mtinitlocknum(i + 16) )
        break;
      _lock_file2(i, *(_DWORD *)(unk_2021F68 + 4 * i));
      if ( (*(_BYTE *)(*(_DWORD *)(unk_2021F68 + 4 * i) + 12) & 0x83) == 0 )
      {
        v0 = *(_DWORD **)(unk_2021F68 + 4 * i);
        break;
      }
      _unlock_file2(i, *(_DWORD *)(unk_2021F68 + 4 * i));
    }
  }
  if ( v0 )
  {
    v0[3] &= 0x8000u;
    v0[1] = 0;
    v0[2] = 0;
    *v0 = 0;
    v0[7] = 0;
    v0[4] = -1;
  }
  _unlock(1);
  return v0;
}

