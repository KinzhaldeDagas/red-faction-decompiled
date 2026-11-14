// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00415DB0 rf_clutter_arm_seconds_timer_with_state680
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter runtime teardown/render admission, DWORD-category glass callback, cached model binding and signed-counter clock-hand geometry): Cdecl(object,secondsF32,stateDWORD),caller pops12. Native x87 loads secondsF32,multiplies DOUBLE1000,addsDOUBLE0.5 then__ftol2_sse;passes integerEAX duration to deadline helper at object676. No intermediate F32 store or symmetric negative rounding. Deadline helper uses shared millisecond clock663E90/period1072800000 with native wrap behavior;negative durations are not clamped here. AFTER arming,storesraw state680 andreturnsobjectEAX. No NULL/finite/range guard or own zero/negative-time policy;state680 meaning not inferred.
int __cdecl rf_clutter_arm_seconds_timer_with_state680(int a1, float a2, int a3)
{
  rf_replicator_arm_milliseconds((int *)(a1 + 676), (int)(a2 * 1000.0 + 0.5));
  *(_DWORD *)(a1 + 680) = a3;
  return a1;
}

