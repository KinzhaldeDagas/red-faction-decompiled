// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005905B0 rf_dsound_buffer_slot_pause_mask
// UNREALRED VERIFIED [dsound-buffers-20261028]: Argument backend slot. If buffer pointer+0 nonnull,returns cached flags+40 &2,else0. Returns raw0/2,not bool. Does not query hardware playback state or validate slot.
int __cdecl rf_dsound_buffer_slot_pause_mask(int a1)
{
  if ( unk_1BA1820[11 * a1] )
    return unk_1BA1848[11 * a1] & 2;
  else
    return 0;
}

