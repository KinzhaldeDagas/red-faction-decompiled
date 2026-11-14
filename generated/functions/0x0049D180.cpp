// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049D180 rf_multiplayer_time_left_split
// UNREALRED VERIFIED [multiplayer-hud] Truncates synchronized end-time minus current-time to whole seconds, then splits the result into hours, minutes, and seconds globals.
int rf_multiplayer_time_left_split()
{
  int result; // eax

  rf_multiplayer_time_left_minutes = 0;
  result = (int)(*(float *)&dword_704EE4 - *(float *)&dword_6FC428);
  rf_multiplayer_time_left_seconds = result;
  if ( result >= 3600 )
  {
    rf_multiplayer_time_left_hours = rf_multiplayer_time_left_seconds / 3600;
    result = rf_multiplayer_time_left_seconds % 3600;
    rf_multiplayer_time_left_seconds %= 3600;
  }
  if ( rf_multiplayer_time_left_seconds >= 60 )
  {
    rf_multiplayer_time_left_minutes = rf_multiplayer_time_left_seconds / 60;
    result = rf_multiplayer_time_left_seconds % 60;
    rf_multiplayer_time_left_seconds %= 60;
  }
  return result;
}

