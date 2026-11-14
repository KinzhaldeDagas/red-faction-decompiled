// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00539F70 rf_procedural_bitmap_record_release
// UNREALRED VERIFIED [resource-pools-20261028]: Unlinks record from active circular list0x142665C, inserts at free head0x1426658, releases generated bitmap handle+24 through0x5781E0, decrements0x1426660 and returns new count. Does not clear bitmap-handle word or full record; no double-release/membership check.
int __cdecl rf_procedural_bitmap_record_release(_DWORD *a1)
{
  if ( (_DWORD *)unk_142665C == a1 )
  {
    if ( (_DWORD *)a1[2] == a1 )
    {
      a1[2] = 0;
      a1[3] = 0;
      unk_142665C = 0;
      goto LABEL_6;
    }
    unk_142665C = a1[2];
  }
  *(_DWORD *)(a1[3] + 8) = a1[2];
  *(_DWORD *)(a1[2] + 12) = a1[3];
  a1[2] = 0;
  a1[3] = 0;
LABEL_6:
  if ( unk_1426658 )
  {
    *(_DWORD *)(*(_DWORD *)(unk_1426658 + 12) + 8) = a1;
    a1[3] = *(_DWORD *)(unk_1426658 + 12);
    *(_DWORD *)(unk_1426658 + 12) = a1;
    a1[2] = unk_1426658;
  }
  else
  {
    a1[2] = a1;
    a1[3] = a1;
  }
  unk_1426658 = a1;
  rf_bitmap_handle_recycle_slot_or_animation_entry(a1[6]);
  return --unk_1426660;
}

