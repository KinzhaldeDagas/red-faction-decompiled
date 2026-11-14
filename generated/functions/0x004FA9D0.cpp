// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FA9D0 rf_event_reverse_mover_build_from_direction
// UNREALRED VERIFIED [mission-mover-events-20261020] Builds type89 and stores direction-selector byte+0x2B8 from caller. RFL loader passes (raw integer0 == 0); this is not either generic boolean field.
int __cdecl rf_event_reverse_mover_build_from_direction(float *a1, char a2)
{
  int v3; // [esp+0h] [ebp-4h]

  v3 = rf_mission_event_create_at_position(a1, 0x59u);
  if ( v3 )
    *(_BYTE *)(v3 + 696) = a2;
  return v3;
}

