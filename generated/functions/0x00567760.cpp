// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567760 rf_random_event_for_fractional_trial_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, signed pool divisions, lookup-table floating arithmetic, RNG trial counts, formatting and strict epsilon predicates): cdecl(probability,trialCountFloat),returns32bit0/1. Repeatedly subtracts1 from count;while newCount>0,draws randomUnit567730 and returns1 on probability>draw. Final draw tests (remainingCount+1)*probability>draw. For finite countN>=0,uses full trials plus one fractional probability,short-circuits first success; even count0 consumes ONE final RNG draw. No clamp of probability/count,not exact pow-based fractional Bernoulli interpolation. Nonfinite/large nondecreasing count can loop without success. Random unit uses CRT rand/32768.
int __cdecl rf_random_event_for_fractional_trial_count(float probability, float trials)
{
  while ( 1 )
  {
    trials = trials - 1.0;
    if ( trials <= 0.0 )
      break;
    if ( probability > sub_567730() )
      return 1;
  }
  return (trials + 1.0) * probability > sub_567730();
}

