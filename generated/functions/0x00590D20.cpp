// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00590D20 rf_dsound_service_all_fades
// UNREALRED VERIFIED [dsound-buffers-20261028]: Walks30 records; flags mask8 set delegates0x590D60. Returns30 loop artifact. Does not clear fade flags on paused/nonplaying slots itself.
int rf_dsound_service_all_fades()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 30; ++i )
  {
    if ( (unk_1BA1848[11 * i] & 8) != 0 )
      rf_dsound_service_fade_slot(i);
    result = i + 1;
  }
  return result;
}

