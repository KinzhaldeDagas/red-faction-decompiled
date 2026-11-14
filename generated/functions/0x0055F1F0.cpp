// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F1F0 rf_clock_deadline_set_wrapped_offset
// UNREALRED VERIFIED [dsound-buffers-20261028]: This points to signed deadline DWORD; argument signed offset. Base clock0x663E94 wraps with period1072800000. Negative offset stores base+offset,adds period once if result<0. Nonnegative offset stores base+offset ifoffset<=period-base,else offset-(period-base). No full modulo for offsets beyond one period,overflow handling or atomicity. Returns path-dependent arithmetic value/this pointer,not consistent deadline value; state write is authoritative.
int *__thiscall rf_clock_deadline_set_wrapped_offset(int *this, int a2)
{
  int *result; // eax

  if ( a2 < 0 )
  {
    result = (int *)(a2 + dword_663E94);
    *this = a2 + dword_663E94;
    if ( *this < 0 )
    {
      *this += 1072800000;
      return this;
    }
  }
  else
  {
    result = (int *)(1072800000 - dword_663E94);
    if ( a2 <= 1072800000 - dword_663E94 )
    {
      *this = a2 + dword_663E94;
    }
    else
    {
      *this = a2 - (1072800000 - dword_663E94);
      return this;
    }
  }
  return result;
}

