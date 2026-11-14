// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040BC90 rf_ai_cancel_tracked_body_action
// UNREALRED VERIFIED [ai-script-animation-release-20261013] The tracked canonical slot at Entity+0x1364 is written by idle variation launcher 0x438B80, not by generic action request 0x436490. Reset ALL action records through 0x565020 and clear this owner only when that slot has nonzero remaining time. An absent/inactive slot retains its stored identity. Does not clear the filename owner, custom-state flag or scheduler bit 8.
char __cdecl rf_ai_cancel_tracked_body_action(int *a1)
{
  int v1; // eax

  LOBYTE(v1) = (_BYTE)a1;
  if ( *(_DWORD *)(*a1 + 4964) != -1 )
  {
    LOBYTE(v1) = rf_entity_body_action_is_active(*a1, *(_DWORD *)(*a1 + 4964));
    if ( (unsigned __int8)v1 == 1 )
    {
      rf_model_handle_reset_actions_adapter(*(_DWORD *)(*a1 + 128));
      v1 = *a1;
      *(_DWORD *)(*a1 + 4964) = -1;
    }
  }
  return v1;
}

