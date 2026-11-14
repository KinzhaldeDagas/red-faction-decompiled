// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00476E10 rf_cutscene_segment_destroy_string
// UNREALRED VERIFIED [cutscene-ui-20261028]: Destroys RF string at segment+24 via0x55F6D0; called for each fixed32-byte segment in cutscene record destructor. No other field cleanup.
void __thiscall rf_cutscene_segment_destroy_string(char *this)
{
  rf_string_destroy_buffer(this + 24);
}

