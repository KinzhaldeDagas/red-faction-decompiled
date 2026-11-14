// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00515780 rf_benchmark_localtime64_forward
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, timedemo/framerate state machine,x87FPS extrema,log ABI and recovered console handlers,original ECX/stack flow and PE bytes): Cdeclpointer to64-bit time_t,caller pops4. Push identicalpointer intoCRT607E57(_localtime64),call,pop4,forwardEAX structtm pointer. No data copy,timezone selection,clock read,NULL/range check,allocation or failure translation. DelegatedCRT semantics,not a32-bit timestamp conversion.
struct tm *__cdecl rf_benchmark_localtime64_forward(__time64_t *Time)
{
  return _localtime64(Time);
}

