// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00475D50 rf_ambient_sound_destroy_filename
// UNREALRED VERIFIED [cutscene-ui-20261028]: Destroys RF string at record+32 through0x55F6D0. No explicit timer/vector destructor or allocation free in this body.
void __thiscall rf_ambient_sound_destroy_filename(int this)
{
  rf_string_destroy_buffer((void *)(this + 32));
}

