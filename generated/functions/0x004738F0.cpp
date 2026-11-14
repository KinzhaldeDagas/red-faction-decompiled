// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004738F0 rf_item_play_pickup_sound
// UNREALRED VERIFIED [event-item-dispatch-20261028]: Null item does nothing. Resolves pickup sound through0x473890; if result>=0 calls rf_gamesound_play_positional_event at item position+60, volume1.0, global0x17F10B0 argument and trailing0. Does not itself destroy item or grant pickup contents.
void __cdecl rf_item_play_pickup_sound(int a1)
{
  int v1; // [esp+Ch] [ebp-4h]

  if ( a1 )
  {
    v1 = rf_item_resolve_pickup_sound_index(a1);
    if ( v1 >= 0 )
      rf_gamesound_play_positional_event(v1, (float *)(a1 + 60), 1.0, (int)&unk_17F10B0, 0);
  }
}

