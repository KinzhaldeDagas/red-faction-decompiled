// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FA340 rf_event_when_dead_create
// UNREALRED VERIFIED [mission-when-dead-20261013] Creates type 16 with fired byte event+0x2B8 zero and missing-target option byte +0x2B9. RFL loader case 16 at 0x47EFBD passes generic Boolean 0 (normalized versioned read), not Boolean 1 or the pre-delay Boolean.
int __cdecl rf_event_when_dead_create(float *a1, char a2)
{
  int v3; // [esp+0h] [ebp-4h]

  v3 = rf_mission_event_create_at_position(a1, 0x10u);
  if ( v3 )
  {
    *(_BYTE *)(v3 + 696) = 0;
    *(_BYTE *)(v3 + 697) = a2;
  }
  return v3;
}

