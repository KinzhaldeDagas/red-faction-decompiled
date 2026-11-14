// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D0650 rf_audio_stream_find_inactive_slot
// UNREALRED VERIFIED [audio-streaming-20261028]: Scans16 stream records at0x1E012F0 stride28,returns first whose flagsDWORD+24 mask1clear. All active returns-1. Does not reserve,clear or validate other fields; caller must claim slot.
int rf_audio_stream_find_inactive_slot()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 16 && (unk_1E01308[7 * i] & 1) != 0; ++i )
    ;
  if ( i < 16 )
    return i;
  else
    return -1;
}

