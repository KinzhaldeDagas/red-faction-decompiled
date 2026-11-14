// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054ADF0 rf_scratch_arena_mark_live_owner_blocks
// UNREALRED VERIFIED [resource-pools-20261028]: For each tracked owner at0x1494718, reads block pointer owner+4; ifnonnull and block dword+32==1 sets it2. Does not change other block states, cursor or owner count. Empty-loop return incidental, not count/status.
int rf_scratch_arena_mark_live_owner_blocks()
{
  int result; // eax
  int v1; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < dword_1426C74; ++i )
  {
    v1 = *(_DWORD *)(unk_1494718[i] + 4);
    if ( v1 )
    {
      if ( *(_DWORD *)(v1 + 32) == 1 )
        *(_DWORD *)(v1 + 32) = 2;
    }
    result = i + 1;
  }
  return result;
}

