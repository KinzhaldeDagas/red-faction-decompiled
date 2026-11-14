// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00590C60 rf_dsound_cancel_fade_by_play_handle
// UNREALRED VERIFIED [dsound-buffers-20261028]: Resolves handle; failure-1. Clears flags+40 mask8,returns remaining flags. Does not restore volume,reset timer or stop/release buffer.
signed int __cdecl rf_dsound_cancel_fade_by_play_handle(int a1)
{
  signed int result; // eax
  signed int v2; // [esp+4h] [ebp-4h]

  result = rf_dsound_find_buffer_slot_by_play_handle(a1);
  v2 = result;
  if ( result >= 0 )
  {
    result = unk_1BA1820[11 * result + 10] & 0xFFFFFFF7;
    unk_1BA1820[11 * v2 + 10] = result;
  }
  return result;
}

