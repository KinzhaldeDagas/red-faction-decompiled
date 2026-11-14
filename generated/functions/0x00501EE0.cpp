// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00501EE0 rf_mission_events_render_debug_icons
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Iterate current event registry vector0x90B0E0 and call0x501F30 for every record. Does not itself check debug flag, update events or filter event class.
int rf_mission_events_render_debug_icons()
{
  int result; // eax
  int *v1; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(unk_90B0E0);
    if ( i >= result )
      break;
    v1 = (int *)sub_552200(unk_90B0E0, i);
    rf_mission_event_render_debug_icon(*v1);
  }
  return result;
}

