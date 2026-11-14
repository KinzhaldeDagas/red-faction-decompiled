// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FA460 rf_event_create_cyclic_timer_record
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Create event20 Cyclic_Timer. Enabled byte+0x2B8=0, interval float+0x2BC=input, raw repeat byte+0x2C0=input, signed limit+0x2C4=input. Arm embedded deadline+0x2C8 at0ms and set current count+0x2CC=0. Thus later forward callback only enabling can admit an immediate first cycle; forward/reverse themselves do not initialize timer/count. No interval clamp or repeat-byte normalization.
int __cdecl rf_event_create_cyclic_timer_record(float *a1, float a2, int a3, char a4)
{
  int v5; // [esp+0h] [ebp-4h]

  v5 = rf_mission_event_create_at_position(a1, 0x14u);
  if ( v5 )
  {
    *(_BYTE *)(v5 + 696) = 0;
    *(float *)(v5 + 700) = a2;
    *(_BYTE *)(v5 + 704) = a4;
    *(_DWORD *)(v5 + 708) = a3;
    rf_replicator_arm_milliseconds((int *)(v5 + 712), 0);
    *(_DWORD *)(v5 + 716) = 0;
  }
  return v5;
}

