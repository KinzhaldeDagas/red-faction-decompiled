// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568C70 rf_streamed_group_one_set_gain
// UNREALRED VERIFIED [sound-backend]: Propagates channel-group index 1 gain to the separate streamed backend instances tracked outside the 30 common voice records.
int __cdecl rf_streamed_group_one_set_gain(float a1)
{
  int result; // eax
  int j; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  unk_1808940 = a1;
  for ( i = 0; i < 2600; ++i )
  {
    if ( unk_1D85DF4[64 * i] && unk_1D85DE8[16 * i] != -1 )
    {
      for ( j = 0; j < 16; ++j )
      {
        if ( unk_1E012F0[7 * j] == unk_1D85DE8[16 * i] )
          rf_sound_backend_voice_set_gain(unk_1BA1830[11 * unk_1E012F4[7 * j]], a1);
      }
    }
    result = i + 1;
  }
  return result;
}

