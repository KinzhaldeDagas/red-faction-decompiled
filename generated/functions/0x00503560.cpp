// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503560 rf_event_follow_waypoints_construct
// UNREALRED VERIFIED [event-lifecycle-20261028]: Calls rf_mission_event_construct_base(E), installs RTTI-backed event_follow_waypoints vtable. Constructs RF string at E+700. Other derived scalar fields are not explicitly initialized here. Returns E; does not activate event.
int __thiscall rf_event_follow_waypoints_construct(int this)
{
  rf_mission_event_construct_base((char *)this);
  *(_DWORD *)this = &event_follow_waypoints::`vftable';
  rf_string_construct_empty((_DWORD *)(this + 700));
  return this;
}

