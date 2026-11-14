// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00446050 rf_music_request_owned_filename
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] When global0x6E6D94==1 return false with no later effects. Otherwise set rf_music_channel_group_index to(byte_arg==0), fade existing owned music for1000ms if rf_music_owned_is_playing reports true, then return whether rf_music_play_owned_filename(filename,1.0)==0. No wait for fade completion before new request.
bool __cdecl rf_music_request_owned_filename(int a1, char a2)
{
  if ( unk_6E6D94 == 1 )
    return 0;
  rf_music_channel_group_index = a2 == 0;
  if ( rf_music_owned_is_playing() )
    rf_music_owned_fade(1000);
  return rf_music_play_owned_filename(a1, 1.0) == 0;
}

