// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A67D0 rf_net_statistics_initialize
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Thiscall(stats). Zeros four30-DWORD histories at+8,+128,+252,+372, total outgoing/incoming bytes at+0/+4, current history indices+248/+492. Calls packet38-window reset (arms+496
// for2000ms and clears five counters+500..516). Zeros four55-DWORD opcode arrays at+520/+740 (byte totals) and+960/+1180 (counts). Arms one-second history deadline+1400 for1000ms,
// sets RTT sample count+1412=0, disarms RTT retry deadline+1416 and sets outstanding performance-clock stamp+1420=-1. Does NOT initialize two RTT sample storage DWORDs+1404/+1408;
// consumers must honor count. No mode/authority/null guard or allocation; this is an initializer, not a whole-object memset. EAX remains deadline-disarm delegate result, not a
// guaranteed stats-base pointer.
_DWORD *__thiscall rf_net_statistics_initialize(int *this)
{
  _DWORD *result; // eax
  int i; // [esp+4h] [ebp-4h]
  int j; // [esp+4h] [ebp-4h]

  for ( i = 0; i < 30; ++i )
  {
    *(this + i + 2) = 0;
    *(this + i + 32) = 0;
    *(this + i + 63) = 0;
    *(this + i + 93) = 0;
  }
  *this = 0;
  *(this + 1) = 0;
  *(this + 62) = 0;
  *(this + 123) = 0;
  rf_net_statistics_reset_packet38_window(this);
  for ( j = 0; j < 55; ++j )
  {
    *(this + j + 130) = 0;
    *(this + j + 185) = 0;
    *(this + j + 240) = 0;
    *(this + j + 295) = 0;
  }
  rf_clock_deadline_set_wrapped_offset(this + 350, 1000);
  *(this + 353) = 0;
  result = rf_clock_deadline_disarm(this + 354);
  *(this + 355) = -1;
  return result;
}

