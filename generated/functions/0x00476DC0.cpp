// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00476DC0 rf_cutscene_record_scalar_delete
// UNREALRED VERIFIED [cutscene-ui-20261028]: Calls record member destructor0x476DF0; operator delete only when flags low byte bit0 set. Returns original pointer, potentially freed. No registry removal or playback stop in wrapper.
char *__thiscall rf_cutscene_record_scalar_delete(char *this, char a2)
{
  rf_cutscene_record_destroy_segments(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

