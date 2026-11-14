// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F2B0 rf_clock_deadline_has_elapsed_half_period
// UNREALRED VERIFIED [dsound-buffers-20261028]: This deadline DWORD. Negative deadline alwaysfalse. If deadline<=current clock0x663E94,return current-deadline<=536400000; otherwise return deadline-current>536400000. Uses half-period wrap comparison for period1072800000; exact equalitydeadline/current true. Does not read system clock or mutate deadline. Correct interpretation assumes differences within half-period.
bool __thiscall rf_clock_deadline_has_elapsed_half_period(int *this)
{
  if ( *this < 0 )
    return 0;
  if ( *this <= dword_663E94 )
    return dword_663E94 - *this <= 536400000;
  return *this - dword_663E94 > 536400000;
}

