// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00590FB0 rf_dsound_resume_all_paused_slots
// UNREALRED VERIFIED [dsound-buffers-20261028]: Walks30 slots and resumes those with cached pause mask2 through0x590F40,without checking pointer or hardware state first. Returns30. Resume helper clears mask even on API failure.
int rf_dsound_resume_all_paused_slots()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 30; ++i )
  {
    if ( (unk_1BA1848[11 * i] & 2) != 0 )
      rf_dsound_resume_slot_from_cached_flags(i);
    result = i + 1;
  }
  return result;
}

