// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503680 rf_event_swap_textures_construct
// UNREALRED VERIFIED [event-lifecycle-20261028]: Calls rf_mission_event_construct_base(E), installs RTTI-backed event_swap_textures vtable. Exception-aware vector constructor initializes two8-byte RF strings at E+704 and E+712, with RF-string destructor as unwind callback. Other derived scalar fields are not explicitly initialized here. Returns E; does not activate event.
char *__thiscall rf_event_swap_textures_construct(char *this)
{
  rf_mission_event_construct_base(this);
  *(_DWORD *)this = &event_swap_textures::`vftable';
  `eh vector constructor iterator'(
    this + 704,
    8u,
    2,
    (void (__thiscall *)(void *))rf_string_construct_empty,
    rf_string_destroy_buffer);
  return this;
}

