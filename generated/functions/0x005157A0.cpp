// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005157A0 rf_benchmark_time64_forward
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, timedemo/framerate state machine,x87FPS extrema,log ABI and recovered console handlers,original ECX/stack flow and PE bytes): Cdecloptional64-bit outputpointer,caller pops4. Forward pointerunchanged toCRT609630(_time64),call,pop4,forward64-bit EDX:EAX returnunchanged (no register modifications aftercall exceptstack/frame). No independentclocksource,unit conversion,32-bit truncation,NULL check orerror translation;backend handlesoptionaloutput.
__time64_t __cdecl rf_benchmark_time64_forward(__time64_t *Time)
{
  return _time64(Time);
}

