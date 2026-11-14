// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005672C0 rf_performance_clock_shutdown
// UNREALRED VERIFIED [system-progress-20261028]: If BYTE ready0x1806930 set, clears it then deletes critical section0x180690C. Does not clear epoch,frequency,previous counter or calibration fields. No synchronization against active clock readers.
void __cdecl rf_performance_clock_shutdown()
{
  if ( unk_1806930 )
  {
    unk_1806930 = 0;
    DeleteCriticalSection(&MEMORY[0x180690C]);
  }
}

