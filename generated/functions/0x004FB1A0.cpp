// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FB1A0 rf_event_create_play_vclip_record
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Create event70 Play_Vclip. Assign supplied effect string+0x2B8, store0x507610(name) result at+0x2C0 and float input+0x2C4. No failed effect-id rejection or runtime effect allocation at creation.
int __cdecl rf_event_create_play_vclip_record(float *a1, char *String2, float a3)
{
  int v4; // [esp+0h] [ebp-4h]

  v4 = rf_mission_event_create_at_position(a1, 0x46u);
  if ( v4 )
  {
    rf_string_assign_from_cstr((_DWORD *)(v4 + 696), String2);
    *(_DWORD *)(v4 + 704) = sub_507610(String2);
    *(float *)(v4 + 708) = a3;
  }
  return v4;
}

