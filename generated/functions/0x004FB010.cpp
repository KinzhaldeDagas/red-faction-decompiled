// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FB010 rf_event_create_blackout_player_record
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Create event61 Black_Out_Player. Store two raw bytes+0x2B8/+0x2B9 and duration float+0x2BC. Nonpositive duration is not replaced here: forward/reverse runtime handlers later mutate same stored duration to their respective defaults.
int __cdecl rf_event_create_blackout_player_record(float *a1, char a2, char a3, float a4)
{
  int v5; // [esp+0h] [ebp-4h]

  v5 = rf_mission_event_create_at_position(a1, 0x3Du);
  if ( v5 )
  {
    *(_BYTE *)(v5 + 696) = a2;
    *(_BYTE *)(v5 + 697) = a3;
    *(float *)(v5 + 700) = a4;
  }
  return v5;
}

