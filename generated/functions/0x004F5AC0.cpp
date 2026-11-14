// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F5AC0 rf_level_state_cache_clear
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] memset global cache base0x894D38 for484056 bytes(0x762D8), including83544-byte header and4 level slots. No file delete, shared-goal table clear or dynamic-resource cleanup in this body.
void *rf_level_state_cache_clear()
{
  return memset(unk_894D38, 0, 0x762D8u);
}

