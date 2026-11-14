// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FB0A0 rf_event_create_when_countdown_reaches_record
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Create event84 When_Countdown_Reaches. Explicitly initialize observed-above byte+0x2B8=0 and fired byte+0x2B9=0; store signed integer threshold+0x2BC. Does not compare shared timer, arm embedded delay or dispatch targets here.
int __cdecl rf_event_create_when_countdown_reaches_record(float *a1, int a2)
{
  int v3; // [esp+0h] [ebp-4h]

  v3 = rf_mission_event_create_at_position(a1, 0x54u);
  if ( v3 )
  {
    *(_BYTE *)(v3 + 696) = 0;
    *(_BYTE *)(v3 + 697) = 0;
    *(_DWORD *)(v3 + 700) = a2;
  }
  return v3;
}

