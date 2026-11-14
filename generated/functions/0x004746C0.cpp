// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004746C0 rf_item_definitions_select_multiplayer_counts
// UNREALRED VERIFIED [event-item-dispatch-20261028]: For each definition copies configured MP count dword+52 to active count+44. Does not clamp or recompute values. Does not itself check multiplayer flag. Empty loop leaves return register incidental; no boolean contract.
// UNREALRED VERIFIED [combat-native-pickups-20261111]: Copies every item signed MPcount+34 directly into active count+2C. Missing CountMulti was resolved by parser to exact signed SP value; zero/negative values are retained.
int rf_item_definitions_select_multiplayer_counts()
{
  int result; // eax
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < unk_6F9124; ++i )
  {
    *((_DWORD *)&unk_6F9130 + 20 * i + 11) = *((_DWORD *)&unk_6F9130 + 20 * i + 13);
    result = i + 1;
  }
  return result;
}

