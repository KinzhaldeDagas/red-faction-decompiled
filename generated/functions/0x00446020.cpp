// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00446020 rf_music_request_owned_fade
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] When global dword0x6E6D94==1 return-1 without fading; otherwise call rf_music_owned_fade with supplied integer milliseconds and return0. Does not immediately release/stop common gamesound voices in this body.
int __cdecl rf_music_request_owned_fade(int a1)
{
  if ( unk_6E6D94 == 1 )
    return -1;
  rf_music_owned_fade(a1);
  return 0;
}

