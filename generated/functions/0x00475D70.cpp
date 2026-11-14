// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00475D70 rf_ambient_sound_record_construct
// UNREALRED VERIFIED [ambient-audio]: Constructs the embedded position, filename string, and timer/replicator fields of a 0x3C-byte persistent ambient record.
int *__thiscall rf_ambient_sound_record_construct(int *this)
{
  rf_vector3_default_construct_noop(this + 5);
  rf_string_construct_empty(this + 8);
  rf_timestamp4_construct_invalid(this + 14);
  return this;
}

