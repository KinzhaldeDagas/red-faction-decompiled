// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005673A0 rf_performance_clock_elapsed_scaled
// UNREALRED VERIFIED [system-progress-20261028]: Argument signed integer units per second. Not ready returns0. Under critical section0x180690C, samples QPC; backward counter resets epoch0x1806900 to current value. Updates previous0x1806928, computes elapsed=current-epoch, leaves lock. Multiplies elapsed64 by signed scale and divides using low32 QPC frequency0x1806934 via custom high-word reduction, returning32-bit result. Scale1000 is elapsed milliseconds,1000000 microseconds. No overflow,negative-scale,zero-frequency or QPC-error guard; backward jump resets elapsed to0. Timer consumers use signed comparisons, so do not assume indefinite monotonic positive output.
int __cdecl rf_performance_clock_elapsed_scaled(int a1)
{
  LONGLONG v2; // rax
  unsigned __int64 v3; // rtt
  LONGLONG v4; // [esp+10h] [ebp-14h]
  LARGE_INTEGER PerformanceCount; // [esp+1Ch] [ebp-8h] BYREF

  if ( !byte_1806930[0] )
    return 0;
  EnterCriticalSection(&MEMORY[0x180690C]);
  QueryPerformanceCounter(&PerformanceCount);
  if ( PerformanceCount.QuadPart < qword_1806928.QuadPart )
    MEMORY[0x1806900] = PerformanceCount;
  qword_1806928 = PerformanceCount;
  v4 = PerformanceCount.QuadPart - MEMORY[0x1806900].QuadPart;
  LeaveCriticalSection(&MEMORY[0x180690C]);
  v2 = v4 * a1;
  do
    HIDWORD(v2) -= dword_1806934;
  while ( v2 >= 0 );
  LODWORD(v3) = v2;
  HIDWORD(v3) = dword_1806934 + HIDWORD(v2);
  return v3 / dword_1806934;
}

