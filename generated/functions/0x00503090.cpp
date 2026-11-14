// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503090 rf_event_sound_construct
// UNREALRED VERIFIED [sound-event-duration-continuation-20261027] Construct event_sound: call common event constructor, install vtable 0x63DFEC, construct primary/alternate strings at +0x2B8/+0x2C0 and Replicator deadline +0x2E0. This body does not explicitly initialize cached sound id +0x2CC, voice +0x2D0, active byte +0x2DD, duration/distance or target; do not infer their defaults from this constructor alone.
int __thiscall rf_event_sound_construct(int this)
{
  rf_mission_event_construct_base((char *)this);
  *(_DWORD *)this = &event_sound::`vftable';
  rf_string_construct_empty((_DWORD *)(this + 696));
  rf_string_construct_empty((_DWORD *)(this + 704));
  rf_timestamp4_construct_invalid((int *)(this + 736));
  return this;
}

