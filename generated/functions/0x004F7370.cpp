// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F7370 rf_snapshot_owned_buffer_delete
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Wrapper destructor passes stored pointer *this directly to operator delete. Does not null stored pointer, free separately allocated level block, close FILE*, or restore snapshot state.
void __thiscall rf_snapshot_owned_buffer_delete(void **this)
{
  operator delete(*this);
}

