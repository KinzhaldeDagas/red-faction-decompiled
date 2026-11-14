// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FE9F0 rf_jpeg_access_virt_sarray
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jmemmgr.c:access_virt_sarray matched): Cdecl(cinfo,descriptor,startRow,numRows,writable),returnsborrowedpointer torowpointerentryatbuffer+4*(start-currentStart). Rejectsend=start+num>totalRows,num>maxAccess,orunrealizedNULLbuffer witherror22. No separateadditionoverflowguard. Ifrequestedrowsoutsidecurrentmemorywindow,requiresbackingopenelseerror69;flushesdirtywindow viaIOhelper,clearsdirty,repositionsforwardtostartorbackwardmax(end-rowsInMemory,0),loadswindow. IfrequestedendbeyondfirstUndefined:writeaccess mustnotleavegap(error22),thenextendsfirstUndefined=end;preZero clearsnewlyundefinedrows beforeaccess;readuninitializedwithoutpreZeroerror22. Writablemarksdirty36=1. No rowcontentcopy orallocationonordinary in-windowaccess. Samplebytewidth=itemsPerRow8;IOhelper0x5FEBF0;zerohelper0x6003F0.
unsigned int __cdecl rf_jpeg_access_virt_sarray(int a1, _DWORD *a2, unsigned int a3, unsigned int a4, int a5)
{
  size_t Size; // [esp+0h] [ebp-10h]
  int v7; // [esp+4h] [ebp-Ch]
  unsigned int v8; // [esp+8h] [ebp-8h]
  unsigned int v9; // [esp+8h] [ebp-8h]
  unsigned int v10; // [esp+Ch] [ebp-4h]
  unsigned int v11; // [esp+Ch] [ebp-4h]

  v8 = a4 + a3;
  if ( a4 + a3 > a2[1] || a4 > a2[3] || !*a2 )
  {
    *(_DWORD *)(*(_DWORD *)a1 + 20) = 22;
    (**(void (__cdecl ***)(int))a1)(a1);
  }
  if ( a3 < a2[6] || v8 > a2[4] + a2[6] )
  {
    if ( !a2[10] )
    {
      *(_DWORD *)(*(_DWORD *)a1 + 20) = 69;
      (**(void (__cdecl ***)(int))a1)(a1);
    }
    if ( a2[9] )
    {
      rf_jpeg_do_sarray_io(a1, (int)a2, 1);
      a2[9] = 0;
    }
    if ( a3 <= a2[6] )
    {
      v7 = v8 - a2[4];
      if ( v7 < 0 )
        v7 = 0;
      a2[6] = v7;
    }
    else
    {
      a2[6] = a3;
    }
    rf_jpeg_do_sarray_io(a1, (int)a2, 0);
  }
  if ( a2[7] < v8 )
  {
    if ( a2[7] >= a3 )
    {
      v10 = a2[7];
    }
    else
    {
      if ( a5 )
      {
        *(_DWORD *)(*(_DWORD *)a1 + 20) = 22;
        (**(void (__cdecl ***)(int))a1)(a1);
      }
      v10 = a3;
    }
    if ( a5 )
      a2[7] = v8;
    if ( a2[8] )
    {
      Size = a2[2];
      v11 = v10 - a2[6];
      v9 = v8 - a2[6];
      while ( v11 < v9 )
        rf_jpeg_jzero_far(*(void **)(*a2 + 4 * v11++), Size);
    }
    else if ( !a5 )
    {
      *(_DWORD *)(*(_DWORD *)a1 + 20) = 22;
      (**(void (__cdecl ***)(int))a1)(a1);
    }
  }
  if ( a5 )
    a2[9] = 1;
  return *a2 + 4 * (a3 - a2[6]);
}

