// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00476DF0 rf_cutscene_record_destroy_segments
// UNREALRED VERIFIED [cutscene-ui-20261028]: Exception-aware vector destructor visits64 segment objects of32 bytes starting record+8, callback0x476E10. Does not free record storage itself or validate an authored segment count.
void __thiscall rf_cutscene_record_destroy_segments(char *this)
{
  `eh vector destructor iterator'(this + 8, 0x20u, 64, (void (__thiscall *)(void *))rf_cutscene_segment_destroy_string);
}

