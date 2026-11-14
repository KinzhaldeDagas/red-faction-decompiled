// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F320 rf_clock_deadline_remaining_signed_half_period
// UNREALRED VERIFIED [list-selection-20261029]: Thiscall deadline DWORD. Negative deadline returns fixed period1072800000. Otherwise raw delta=deadline-global clock0x663E94;when delta>536400000 subtracts period,when delta<-536400000 adds period;ties at half-period retain raw sign. Returns signed nearest-wrap remaining clock units. No clock advance or mutation;not a boolean elapsed test. No independent validity check on clock global.
int __thiscall rf_clock_deadline_remaining_signed_half_period(int *this)
{
  if ( *this < 0 )
    return 1072800000;
  if ( *this <= dword_663E94 )
  {
    if ( dword_663E94 - *this <= 536400000 )
      return *this - dword_663E94;
    else
      return *this + 1072800000 - dword_663E94;
  }
  else if ( *this - dword_663E94 <= 536400000 )
  {
    return *this - dword_663E94;
  }
  else
  {
    return -(dword_663E94 + 1072800000 - *this);
  }
}

