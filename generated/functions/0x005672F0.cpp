// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005672F0 rf_performance_clock_initialize
// UNREALRED VERIFIED [system-progress-20261028]: Once BYTE0x1806930 is clear, queries QPC frequency, stores ONLY LowPart at0x1806934, samples QPC epoch0x1806900 and previous0x1806928, initializes critical section0x180690C. Reads low32 RDTSC, sleeps250ms, reads unused intermediate low32, sleeps250ms, stores signed(last-first)/2 at0x1806908. Sets ready byte1 and registers0x5672C0 with atexit. No QPC success, zero frequency, TSC support or race checks. Already-ready returns1; first call returns atexit result, not consistent success boolean.
int rf_performance_clock_initialize()
{
  int result; // eax
  int timestamp_counter; // [esp+4h] [ebp-10h]
  LARGE_INTEGER Frequency; // [esp+8h] [ebp-Ch] BYREF
  int v3; // [esp+10h] [ebp-4h]

  result = byte_1806930[0];
  if ( !byte_1806930[0] )
  {
    QueryPerformanceFrequency(&Frequency);
    unk_1806934 = Frequency.LowPart;
    QueryPerformanceCounter((LARGE_INTEGER *)&dword_17F1120[22008]);
    QueryPerformanceCounter(&unk_1806928);
    InitializeCriticalSection(&MEMORY[0x180690C]);
    timestamp_counter = rf_clock_read_timestamp_counter();
    Sleep(0xFAu);
    v3 = rf_clock_read_timestamp_counter();
    Sleep(0xFAu);
    unk_1806908 = (int)(rf_clock_read_timestamp_counter() - timestamp_counter) / 2;
    byte_1806930[0] = 1;
    return atexit(rf_performance_clock_shutdown);
  }
  return result;
}

