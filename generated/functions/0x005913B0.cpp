// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005913B0 rf_dsound_get_primary_buffer_pointer
// UNREALRED VERIFIED [dsound-buffers-20261028]: Returns global primary-buffer pointer0x195166C unchanged. Borrowed pointer; no AddRef, initialization check or synchronization.
_DWORD *rf_dsound_get_primary_buffer_pointer()
{
  return dword_195166C;
}

