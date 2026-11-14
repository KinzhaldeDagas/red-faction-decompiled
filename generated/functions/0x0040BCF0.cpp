// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040BCF0 rf_ai_clear_scripted_animation_context
// UNREALRED VERIFIED [ai-script-animation-release-20261013] Activity-gated cleanup: if filename owner Entity+0x1368 is valid AND 0x40BC40 reports nonzero remaining time, reset ALL action records and set that owner to -1. Then unconditionally clear Entity+0x810 bit 0x02000000 (custom loop) and pending state Entity+0x834, then call 0x40BC90 for the separate canonical idle owner. Ordering matters: resetting a file action can make the subsequent idle check inactive, leaving the idle identity retained. Entity+0x810 bit 8 is NOT cleared. No dead-entity guard, Foley stop, stance reset or unconditional action reset exists here.
char __cdecl rf_ai_clear_scripted_animation_context(int *a1)
{
  if ( *(_DWORD *)(*a1 + 4968) != -1 && rf_ai_scripted_action_has_remaining_time((int)a1) )
  {
    rf_model_handle_reset_actions_adapter(*(_DWORD *)(*a1 + 128));
    *(_DWORD *)(*a1 + 4968) = -1;
  }
  *(_DWORD *)(*a1 + 2064) &= ~0x2000000u;
  *(_DWORD *)(*a1 + 2100) = -1;
  return rf_ai_cancel_tracked_body_action(a1);
}

