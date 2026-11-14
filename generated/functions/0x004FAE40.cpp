// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FAE40 rf_event_skybox_state_create
// UNREALRED VERIFIED [authored-sky-renderer] Creates mission-event type 59, copies the first byte of string parameter 0 to +0x2B8, and copies float parameter 0 to +0x2BC. No boolean parameter is consumed.
int __cdecl rf_event_skybox_state_create(float *a1, _BYTE *a2, float a3)
{
  int v4; // [esp+0h] [ebp-4h]

  v4 = rf_mission_event_create_at_position(a1, 0x3Bu);
  if ( v4 )
  {
    *(_BYTE *)(v4 + 696) = *a2;
    *(float *)(v4 + 700) = a3;
  }
  return v4;
}

