// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00474670 rf_item_definitions_select_singleplayer_counts
// UNREALRED VERIFIED [event-item-dispatch-20261028]: For each definition copies configured SP count dword+48 to active count+44. Does not clamp or recompute values. Does not itself check multiplayer flag. Empty loop leaves return register incidental; no boolean contract.
// UNREALRED VERIFIED [combat-native-pickups-20261111]: Copies every item signed SPcount+30 directly into active count+2C. No lower clamp or SP<=0 fallback to MP.
int rf_item_definitions_select_singleplayer_counts()
{
  int result; // eax
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < unk_6F9124; ++i )
  {
    *((_DWORD *)&unk_6F9130 + 20 * i + 11) = *((_DWORD *)&unk_6F9130 + 20 * i + 12);
    result = i + 1;
  }
  return result;
}

