// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00576010 rf_bitmap_allocate_contiguous_slot_run
// UNREALRED VERIFIED [bitmap-loading-20261028]: Argument requested record count. Scans record array for a contiguous run whose typeDWORD+52==0. No run returns0. Success gets one generation, assigns consecutive handles startslot+slotcount*generation through run, moves each record from its current list into active-list tail, returns first record pointer. Does not mark type occupied or reset payload; caller must initialize immediately. No positive count, list integrity or arithmetic checks; count0 can match a zero-length run and return a record without reserving it.
int __cdecl rf_bitmap_allocate_contiguous_slot_run(int a1)
{
  int v2; // [esp+0h] [ebp-14h]
  int j; // [esp+4h] [ebp-10h]
  int v4; // [esp+8h] [ebp-Ch]
  int v5; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]

  v5 = 0;
  v4 = 0;
  for ( i = 0; ; ++i )
  {
    if ( i >= dword_663F14 )
      return 0;
    if ( *(_DWORD *)(dword_1897344 + 108 * i + 52) )
    {
      v5 = 0;
    }
    else
    {
      if ( !v5 )
        v4 = i;
      ++v5;
    }
    if ( v5 == a1 )
      break;
  }
  v2 = v4 + dword_663F14 * rf_bitmap_next_handle_generation();
  for ( j = v4; j < a1 + v4; ++j )
  {
    *(_DWORD *)(dword_1897344 + 108 * j + 36) = v2++;
    *(_DWORD *)(*(_DWORD *)(dword_1897344 + 108 * j + 88) + 84) = *(_DWORD *)(dword_1897344 + 108 * j + 84);
    *(_DWORD *)(*(_DWORD *)(dword_1897344 + 108 * j + 84) + 88) = *(_DWORD *)(dword_1897344 + 108 * j + 88);
    *(_DWORD *)(dword_1897344 + 108 * j + 84) = 0;
    *(_DWORD *)(dword_1897344 + 108 * j + 88) = 0;
    *(_DWORD *)(dword_1897344 + 108 * j + 88) = unk_1897438;
    *(_DWORD *)(dword_1897344 + 108 * j + 84) = &unk_18973E0;
    *(_DWORD *)(unk_1897438 + 84) = dword_1897344 + 108 * j;
    unk_1897438 = dword_1897344 + 108 * j;
  }
  return dword_1897344 + 108 * v4;
}

