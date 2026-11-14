// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005034D0 rf_event_load_level_construct
// UNREALRED VERIFIED [general-gap-20260830]: Constructs the base mission event, installs event_load_level::vftable, and initializes the destination string object at +0x2B8.
int __thiscall rf_event_load_level_construct(int this)
{
  rf_mission_event_construct_base((char *)this);
  *(_DWORD *)this = &event_load_level::`vftable';
  rf_string_construct_empty((_DWORD *)(this + 696));
  return this;
}

