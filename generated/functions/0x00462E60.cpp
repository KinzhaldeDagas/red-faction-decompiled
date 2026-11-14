// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00462E60 rf_browser_import_cache100
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Cdecl(source100,favorite lowBYTE),returns raw endpoint index or-1. Reject primaryNULL,signed liveCount>=capacity,or liveCount<0 BEFORE endpoint lookup,so full capacity
// rejects even an existing endpoint. Hit:optionally OR favorite80000000;other live fields unchanged. Miss:construct108-byte stack record WITHOUT memset:IP0->84,ONLY
// portWORD4->88,names8/40/72->0/32/64 via strncpy31/31/15 with finalNUL,mode88->80,players92/93,ping94,entire UNMASKED flags96->104,optional favorite. Bytes90..91 and query
// bytes96..103 remain uninitialized stack data. Increment liveCount BEFORE carry/swap108-byte copies through newCount-1,including reading unused tail slot;return insertion index. No
// allocation,query-byte initialization,dirty flag,display rebuild or input record sanitization.
int __cdecl rf_browser_import_cache100(int a1, char a2)
{
  char Destination[112]; // [esp+8h] [ebp-F0h] BYREF
  _BYTE v4[108]; // [esp+78h] [ebp-80h] BYREF
  int v5; // [esp+F0h] [ebp-8h] BYREF
  int i; // [esp+F4h] [ebp-4h]

  if ( !dword_6F52CC )
    return -1;
  if ( dword_6F51A8 >= dword_6F5198 )
    return -1;
  if ( dword_6F51A8 < 0 )
    return -1;
  if ( rf_browser_find_endpoint_or_insertion_index(*(_DWORD *)a1, *(_DWORD *)(a1 + 4), &v5) )
  {
    if ( a2 )
      *((_DWORD *)dword_6F52CC + 27 * v5 + 26) |= 0x80000000;
    return v5;
  }
  else
  {
    *(_DWORD *)&Destination[84] = *(_DWORD *)a1;
    *(_WORD *)&Destination[88] = *(_WORD *)(a1 + 4);
    strncpy(Destination, (const char *)(a1 + 8), 0x1Fu);
    Destination[31] = 0;
    strncpy(&Destination[32], (const char *)(a1 + 40), 0x1Fu);
    Destination[63] = 0;
    strncpy(&Destination[64], (const char *)(a1 + 72), 0xFu);
    Destination[79] = 0;
    *(_DWORD *)&Destination[80] = *(_DWORD *)(a1 + 88);
    Destination[92] = *(_BYTE *)(a1 + 92);
    Destination[93] = *(_BYTE *)(a1 + 93);
    *(_WORD *)&Destination[94] = *(_WORD *)(a1 + 94);
    *(_DWORD *)&Destination[104] = *(_DWORD *)(a1 + 96);
    if ( a2 )
      *(_DWORD *)&Destination[104] |= 0x80000000;
    ++dword_6F51A8;
    for ( i = v5; i < dword_6F51A8; ++i )
    {
      qmemcpy(v4, (char *)dword_6F52CC + 108 * i, sizeof(v4));
      qmemcpy((char *)dword_6F52CC + 108 * i, Destination, 0x6Cu);
      qmemcpy(Destination, v4, 0x6Cu);
    }
    return v5;
  }
}

