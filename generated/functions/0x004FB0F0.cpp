// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FB0F0 rf_event_create_when_life_reaches_record
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Create event87 When_Life_Reaches. Initialize one-shot latch byte+0x2B8=0 and store SIGNED INTEGER threshold+0x2BC unchanged. No float reinterpretation, health/armor clamp or target scan here.
int __cdecl rf_event_create_when_life_reaches_record(float *a1, int a2)
{
  int v3; // [esp+0h] [ebp-4h]

  v3 = rf_mission_event_create_at_position(a1, 0x57u);
  if ( v3 )
  {
    *(_BYTE *)(v3 + 696) = 0;
    *(_DWORD *)(v3 + 700) = a2;
  }
  return v3;
}

