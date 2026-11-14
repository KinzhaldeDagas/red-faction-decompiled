// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FAF00 rf_event_modify_rotating_mover_build_from_fields
// UNREALRED VERIFIED [mission-mover-events-20261020] Builds type66. Case-insensitive equality of raw string0 with literal Increase sets byte+0x2B8; any other string clears it. Raw float0 is copied to percentage+0x2BC. Increase therefore decreases travel times in0x48A7E0; whitespace is not trimmed.
int __cdecl rf_event_modify_rotating_mover_build_from_fields(float *a1, int a2, int a3, float a4)
{
  int v5; // [esp+8h] [ebp-10h]

  v5 = rf_mission_event_create_at_position(a1, 0x42u);
  if ( v5 )
  {
    *(_BYTE *)(v5 + 696) = rf_string_equals_case_insensitive((int)&a2, "Increase");
    *(float *)(v5 + 700) = a4;
  }
  rf_string_destroy_buffer(&a2);
  return v5;
}

