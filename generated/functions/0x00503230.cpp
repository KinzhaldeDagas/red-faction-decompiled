// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503230 rf_event_play_animation_construct
// UNREALRED VERIFIED [mission-event-play-animation]: Constructs the base event object and installs event_play_animation::vftable.
char *__thiscall rf_event_play_animation_construct(char *this)
{
  rf_mission_event_construct_base(this);
  *(_DWORD *)this = &event_play_animation::`vftable';
  return this;
}

