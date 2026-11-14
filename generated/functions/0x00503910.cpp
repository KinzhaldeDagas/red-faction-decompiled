// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503910 rf_event_music_start_construct
// UNREALRED VERIFIED [event-builders-20261028]: Calls rf_mission_event_construct_base(this), then installs RTTI-backed event_music_start vtable. Constructs RF string subobject at E+696 via0x55F5D0; byte E+704 is not initialized by this derived body. Returns this. Constructor alone does not trigger event activation.
int __thiscall rf_event_music_start_construct(int this)
{
  rf_mission_event_construct_base((char *)this);
  *(_DWORD *)this = &event_music_start::`vftable';
  rf_string_construct_empty((_DWORD *)(this + 696));
  return this;
}

