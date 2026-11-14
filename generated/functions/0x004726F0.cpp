// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004726F0 rf_item_find_oldest_dropped_fade_candidate
// UNREALRED VERIFIED [item-pickups-20261028]: Same eligibility as0x472670: bit8 set, bit4 and0x10 clear. Returns eligible item with minimum float creation time+696, or0. Strict comparison retains first list entry on equal times. Does not mark or delete candidate.
int rf_item_find_oldest_dropped_fade_candidate()
{
  int i; // [esp+0h] [ebp-8h]
  int v2; // [esp+4h] [ebp-4h]

  v2 = 0;
  for ( i = unk_6FB1C4; (_UNKNOWN *)i != &unk_6FAF38; i = *(_DWORD *)(i + 652) )
  {
    if ( (*(_DWORD *)(i + 700) & 8) != 0 && !rf_item_is_fading(i) && !rf_item_has_retention_flag10(i) )
    {
      if ( v2 )
      {
        if ( *(float *)(v2 + 696) > (double)*(float *)(i + 696) )
          v2 = i;
      }
      else
      {
        v2 = i;
      }
    }
  }
  return v2;
}

