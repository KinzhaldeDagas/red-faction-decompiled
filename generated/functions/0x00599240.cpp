// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00599240 rf_network_statistics_advance_second_bucket
// UNREALRED VERIFIED [system-progress-20261028]: Uses wrapping deadline0x1C0C420. If armed and not elapsed,returns immediately. If armed and elapsed, increments bucket index0x1BDB2D8 while<30; once>=30, shifts8 arrays left by one DWORD (116bytes) and clears their final DWORD. Arrays at0x1BCA320,0x1BDB2E0,0x1BCA398,0x1BDB260,0x1BDB1E8,0x1C0C300,0x1C0C378,0x1BDB358 each hold30 DWORD counters. Arms deadline1000ms on other paths, including initially unarmed path. Advances at most one bucket per call; no catch-up loop. Index30 remains saturated and writers target bucket29.
unsigned __int8 rf_network_statistics_advance_second_bucket()
{
  unsigned __int8 result; // al

  if ( rf_timestamp_is_armed_nonnegative(unk_1C0C420) )
  {
    result = rf_clock_deadline_has_elapsed_half_period(unk_1C0C420);
    if ( !result )
      return result;
    if ( dword_1BDB2D8 < 30 )
    {
      ++dword_1BDB2D8;
    }
    else
    {
      memcpy_0(dword_1BCA320, &unk_1BCA324, 0x74u);
      unk_1BCA394 = 0;
      memcpy_0(dword_1BDB2E0, &unk_1BDB2E4, 0x74u);
      unk_1BDB354 = 0;
      memcpy_0(dword_1BCA398, &unk_1BCA39C, 0x74u);
      unk_1BCA40C = 0;
      memcpy_0(dword_1BDB260, &unk_1BDB264, 0x74u);
      unk_1BDB2D4 = 0;
      memcpy_0(dword_1BDB1E8, &unk_1BDB1EC, 0x74u);
      unk_1BDB25C = 0;
      memcpy_0(dword_1C0C300, &unk_1C0C304, 0x74u);
      unk_1C0C374 = 0;
      memcpy_0(dword_1C0C378, &unk_1C0C37C, 0x74u);
      unk_1C0C3EC = 0;
      memcpy_0(dword_1BDB358, &unk_1BDB35C, 0x74u);
      unk_1BDB3CC = 0;
    }
  }
  return (unsigned __int8)rf_clock_deadline_set_wrapped_offset(unk_1C0C420, 1000);
}

