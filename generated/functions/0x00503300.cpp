// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503300 rf_event_message_construct
// UNREALRED VERIFIED [serialized-event-bool-20260923]: Constructs the Message event by invoking the base event constructor, installing event_message vtable 0x0063E0C8, then constructing its text object at +0x2C0. The vtable forward-dispatch slot +4 points to 0x004FE700.
int __thiscall rf_event_message_construct(int this)
{
  rf_mission_event_construct_base((char *)this);
  *(_DWORD *)this = &event_message::`vftable';
  rf_string_construct_empty((_DWORD *)(this + 704));
  return this;
}

