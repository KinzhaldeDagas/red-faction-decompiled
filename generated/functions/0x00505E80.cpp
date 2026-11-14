// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00505E80 rf_trigger_debug_draw_registry
// UNREALRED VERIFIED [event-item-dispatch-20261028]: If debug byte0x90B4F0 is nonzero, traverses runtime trigger list to sentinel0x90B510 and calls0x505830 for every trigger. Called by player-view rendering. Does not independently filter shape, activation state, or multiplayer authority. Return is incidental byte/list pointer, not reliable count.
int rf_trigger_debug_draw_registry()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  result = byte_90B4F0[0];
  if ( byte_90B4F0[0] )
  {
    for ( i = rf_trigger_runtime_list_head; (_UNKNOWN *)i != &unk_90B510; i = result )
    {
      rf_trigger_debug_draw_one(i);
      result = *(_DWORD *)(i + 652);
    }
  }
  return result;
}

