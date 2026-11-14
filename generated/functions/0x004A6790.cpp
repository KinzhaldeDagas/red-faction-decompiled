// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A6790 rf_net_statistics_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Thiscall(stats), no stack args, explicit EAX=receiver at exit. Constructs invalid wrapped deadlines at+496,+1400,+1416, then calls already verified net_statistics_initialize.
// Initializer subsequently arms+496 for2000ms,+1400 for1000ms,disarms+1416,sets outstanding+1420=-1 and zeros its defined arrays/counts; constructor does not zero entire object or
// RTT sample storage. Embedded in player auxiliary+4608 record at offset28. No allocation, mode or authority guard.
int *__thiscall rf_net_statistics_construct(int *this)
{
  rf_clock_deadline_construct_invalid(this + 124);
  rf_clock_deadline_construct_invalid(this + 350);
  rf_clock_deadline_construct_invalid(this + 354);
  rf_net_statistics_initialize(this);
  return this;
}

