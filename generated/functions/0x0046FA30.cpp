// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046FA30 rf_demo_upsell_advance_if_ready
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): Only if minimum deadline6F9114 elapsed: increments index6F910C, rearms minimum1000ms, reads display delay DWORD66244C[newIndex] and rearms6F9110. NO index bound before
// duration read, even transition index2->3: index3 actually reads neighboring original DWORD0x00648F3C (6590268), outside three-slide durations. Frame later routes index>=3 to
// panel2. No separate armed test.
int rf_demo_upsell_advance_if_ready()
{
  int result; // eax

  result = rf_clock_deadline_has_elapsed_half_period(&dword_6F9114);
  if ( (_BYTE)result )
  {
    ++unk_6F910C;
    rf_clock_deadline_set_wrapped_offset(&dword_6F9114, 1000);
    return rf_clock_deadline_set_wrapped_offset(&dword_6F9110, dword_66244C[unk_6F910C]);
  }
  return result;
}

