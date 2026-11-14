// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00472670 rf_item_count_dropped_fade_candidates
// UNREALRED VERIFIED [item-pickups-20261028]: Traverses item list from0x6FB1C4 to sentinel0x6FAF38 using next+652. Counts items with flags+700 bit8 set, fading bit4 clear, retention bit0x10 clear. No age threshold or respawn-inactive check here.
int rf_item_count_dropped_fade_candidates()
{
  int i; // [esp+0h] [ebp-8h]
  int v2; // [esp+4h] [ebp-4h]

  v2 = 0;
  for ( i = unk_6FB1C4; (_UNKNOWN *)i != &unk_6FAF38; i = *(_DWORD *)(i + 652) )
  {
    if ( (*(_DWORD *)(i + 700) & 8) != 0 && !rf_item_is_fading(i) && !rf_item_has_retention_flag10(i) )
      ++v2;
  }
  return v2;
}

