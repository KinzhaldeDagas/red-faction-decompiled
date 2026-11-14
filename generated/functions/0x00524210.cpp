// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00524210 rf_world_decal_recycle_record
// UNREALRED VERIFIED [decal-updates-20261028]: Nonnull input unlinks active decal from circular list0xA7051C via next+224/prev+228 (handles singleton/head), inserts into free list0xA70620. Decrements category counters0xA70630/34 for flags+80 masks0x100/0x200, releases polygon list through0x5215D0, decrements active count0xA70624. Does NOT clear flags, bitmap handle or owner fields. Does not remove spatial owner-array references; full remove helper0x524100 does that first. Null returns uninitialized/incidental EAX, no stable status contract.
int __cdecl rf_world_decal_recycle_record(_DWORD *a1)
{
  int result; // eax

  if ( !a1 )
    return result;
  if ( (_DWORD *)unk_A7051C != a1 )
    goto LABEL_6;
  if ( (_DWORD *)a1[56] != a1 )
  {
    unk_A7051C = a1[56];
LABEL_6:
    *(_DWORD *)(a1[57] + 224) = a1[56];
    *(_DWORD *)(a1[56] + 228) = a1[57];
    a1[56] = 0;
    a1[57] = 0;
    goto LABEL_7;
  }
  a1[56] = 0;
  a1[57] = 0;
  unk_A7051C = 0;
LABEL_7:
  if ( unk_A70620 )
  {
    a1[57] = *(_DWORD *)(unk_A70620 + 228);
    a1[56] = unk_A70620;
    *(_DWORD *)(*(_DWORD *)(unk_A70620 + 228) + 224) = a1;
    *(_DWORD *)(unk_A70620 + 228) = a1;
  }
  else
  {
    a1[56] = a1;
    a1[57] = a1;
    unk_A70620 = a1;
  }
  if ( (a1[20] & 0x100) != 0 )
    --dword_A70630;
  if ( (a1[20] & 0x200) != 0 )
    --dword_A70634;
  result = rf_world_decal_release_attached_polygons((int)a1);
  --unk_A70624;
  return result;
}

