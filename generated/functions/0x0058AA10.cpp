// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058AA10 rf_mouse_record_button_transition
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): Requires mouse initialized and locks pending button array193A080, stride16. Only if stored held byte differs from supplied raw byte, stores it. Nonzero new state increments pending press count, sets double-click byte when deadline_has_elapsed returnsfalse, then resets deadline with interval663F50. Zero new state increments release count. Does not clear a preexisting double-click byte on release; frame poll consumes it. No button-index bounds check or byte normalization.
void __cdecl rf_mouse_record_button_transition(int a1, char a2)
{
  if ( byte_193A06D )
  {
    EnterCriticalSection(&unk_193A044);
    if ( unk_193A080[16 * a1] != a2 )
    {
      unk_193A080[16 * a1] = a2;
      if ( a2 )
      {
        ++unk_193A084[4 * a1];
        if ( !rf_clock_deadline_has_elapsed_half_period(&unk_193A08C[4 * a1]) )
          unk_193A081[16 * a1] = 1;
        rf_clock_deadline_set_wrapped_offset(&unk_193A08C[4 * a1], dword_663F50);
      }
      else
      {
        ++unk_193A088[4 * a1];
      }
    }
    LeaveCriticalSection(&unk_193A044);
  }
}

