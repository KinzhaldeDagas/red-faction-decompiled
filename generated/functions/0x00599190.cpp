// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00599190 rf_network_statistics_reset_all_buckets
// UNREALRED VERIFIED [network-queues-20261028]: Clears all30 DWORDs in8 arrays at0x1BCA398,0x1BDB260,0x1BCA320,0x1BDB2E0,0x1C0C378,0x1BDB358,0x1BDB1E8,0x1C0C300. Sets bucket index0x1BDB2D8=0 and disarms wrapping deadline0x1C0C420 through0x55F290. Returns deadline pointer,not count. Does not clear queues,socket,peer records or callbacks.
_DWORD *rf_network_statistics_reset_all_buckets()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 30; ++i )
  {
    dword_1BCA398[i] = 0;
    dword_1BDB260[i] = 0;
    dword_1BCA320[i] = 0;
    dword_1BDB2E0[i] = 0;
    dword_1C0C378[i] = 0;
    dword_1BDB358[i] = 0;
    dword_1BDB1E8[i] = 0;
    dword_1C0C300[i] = 0;
  }
  dword_1BDB2D8 = 0;
  return rf_clock_deadline_disarm(unk_1C0C420);
}

