// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FA720 rf_event_create_spawn_object_record
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Reject unsigned runtime type>10, otherwise create event23 Spawn_Object. Store runtime type+0x2B8, raw definition index+0x2BC, raw byte+0x2C0, float+0x2C4. Types2/3/5..10 can be stored even though runtime forward handler only handles0/1/4. No definition-index validation or immediate object spawning.
int __cdecl rf_event_create_spawn_object_record(float *a1, unsigned int a2, int a3, char a4, float a5)
{
  int v6; // [esp+0h] [ebp-4h]

  if ( a2 > 0xA )
    return 0;
  v6 = rf_mission_event_create_at_position(a1, 0x17u);
  if ( v6 )
  {
    *(_DWORD *)(v6 + 696) = a2;
    *(_DWORD *)(v6 + 700) = a3;
    *(_BYTE *)(v6 + 704) = a4;
    *(float *)(v6 + 708) = a5;
  }
  return v6;
}

