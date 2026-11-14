// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00475D20 rf_ambient_sound_scalar_delete
// UNREALRED VERIFIED [cutscene-ui-20261028]: Destroys ambient record filename string via0x475D50, then operator-deletes record only if flags low byte bit0 set. Returns original address, potentially freed. Does not stop sound/unlink registry here.
void *__thiscall rf_ambient_sound_scalar_delete(void *this, char a2)
{
  rf_ambient_sound_destroy_filename((int)this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

