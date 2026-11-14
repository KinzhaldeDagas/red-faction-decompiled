// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F0B0 rf_replicator_signed_remaining_milliseconds
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Unarmed negative deadline returns full period1072800000. Armed deadline compared to wrapped clock0x663E90 with half-period536400000; choose direct deadline-now or adjust by full period to nearest signed difference. Can return zero/negative when elapsed; this is not a nonnegative time-until clamp. Snapshot packer separately checks armed state before using this result.
int __thiscall rf_replicator_signed_remaining_milliseconds(int *this)
{
  if ( *this < 0 )
    return 1072800000;
  if ( *this <= dword_663E90 )
  {
    if ( dword_663E90 - *this <= 536400000 )
      return *this - dword_663E90;
    else
      return *this + 1072800000 - dword_663E90;
  }
  else if ( *this - dword_663E90 <= 536400000 )
  {
    return *this - dword_663E90;
  }
  else
  {
    return -(dword_663E90 + 1072800000 - *this);
  }
}

