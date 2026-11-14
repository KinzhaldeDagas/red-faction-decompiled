// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C75F0 rf_positional_sound_instance_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): Constructor for the 108-byte global instance record. Calls no-op vector constructors at +36,+48,+60,+84,+96 and initializes the deadline scalar at +76 to -1 using the one-DWORD constructor at 55F1B0. Does not initialize links, flags, resource/voice handles, gain/pan/frequency caches or interval; instance_reset/creation do that later. Returns this. Inherited Replicator constructor label at the deadline helper is misleading.
int *__thiscall rf_positional_sound_instance_construct(int *this)
{
  rf_vector3_default_construct_noop(this + 9);
  rf_vector3_default_construct_noop(this + 12);
  rf_vector3_default_construct_noop(this + 15);
  rf_clock_deadline_construct_invalid(this + 19);
  rf_vector3_default_construct_noop(this + 21);
  rf_vector3_default_construct_noop(this + 24);
  return this;
}

