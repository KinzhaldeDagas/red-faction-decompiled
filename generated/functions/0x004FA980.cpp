// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FA980 rf_event_set_ai_mode_build_from_option
// UNREALRED VERIFIED [ai-set-mode-event-20260826]: Creates event type 0x22. When its third argument is true it indexes the five observed dwords at 0x662548, [1,2,4,5,11], with the authored integer, then stores the resulting numeric mode at event +0x2B8. No local bounds check is shown.
int __cdecl rf_event_set_ai_mode_build_from_option(float *a1, int a2, char a3)
{
  int v4; // [esp+0h] [ebp-4h]

  v4 = rf_mission_event_create_at_position(a1, 0x22u);
  if ( v4 )
  {
    if ( a3 )
      a2 = rf_set_ai_mode_option_translation[a2];
    *(_DWORD *)(v4 + 696) = a2;
  }
  return v4;
}

