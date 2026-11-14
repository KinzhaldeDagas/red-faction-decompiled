// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FA920 rf_event_create_swap_textures_record
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Create event33 Swap_Textures. Store first material index+0x2B8 and second+0x2BC; copy supplied filename strings to+0x2C0/+0x2C8. No index-range validation, bitmap loading or target model lookup at creation; runtime callback performs those separate steps.
_DWORD *__cdecl rf_event_create_swap_textures_record(float *a1, int a2, char *Source, int a4, char *a5)
{
  _DWORD *v6; // [esp+0h] [ebp-4h]

  v6 = (_DWORD *)rf_mission_event_create_at_position(a1, 0x21u);
  if ( v6 )
  {
    v6[174] = a2;
    v6[175] = a4;
    rf_string_assign_from_cstr(v6 + 176, Source);
    rf_string_assign_from_cstr(v6 + 178, a5);
  }
  return v6;
}

