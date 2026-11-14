// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005017F0 rf_event_when_countdown_reaches_update
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Threshold precision: only positive remaining countdown is examined. remaining>signed integer threshold sets observed-above byte+0x2B8; ordinary branch fires whenever remaining<threshold and fired byte+0x2B9==0, without needing prior above observation. Only L17S1/L17S2/L17S3 plus name-helper match countdown_sound requires above byte first. Equality never fires. Dispatch event/mover/ordinary-trigger checks independently with anonymous context, then set fired byte AFTER full target traversal. This clarifies earlier broad crossing wording: ordinary threshold is a level condition; no countdown epoch reset or reentrancy latch-before-dispatch here.
void __thiscall rf_event_when_countdown_reaches_update(int this)
{
  int *v1; // eax
  int *v2; // eax
  int *v3; // eax
  int v5; // [esp+4h] [ebp-14h]
  int v6; // [esp+8h] [ebp-10h]
  int *v7; // [esp+Ch] [ebp-Ch]
  int i; // [esp+10h] [ebp-8h]
  char v9; // [esp+17h] [ebp-1h]

  if ( rf_mission_countdown_remaining_seconds > 0.0 )
  {
    if ( rf_mission_countdown_remaining_seconds > (double)*(int *)(this + 700) )
      *(_BYTE *)(this + 696) = 1;
    if ( !*(_BYTE *)(this + 697) )
    {
      v9 = 0;
      if ( (rf_string_equals_case_insensitive((int)unk_6FC31C, "L17S1.rfl")
         || rf_string_equals_case_insensitive((int)unk_6FC31C, "L17S2.rfl")
         || rf_string_equals_case_insensitive((int)unk_6FC31C, "L17S3.rfl"))
        && rf_rf_string_not_equals_cstring_case_insensitive(this + 28, "countdown_sound") )
      {
        if ( *(_BYTE *)(this + 696) && rf_mission_countdown_remaining_seconds < (double)*(int *)(this + 700) )
          v9 = 1;
      }
      else if ( rf_mission_countdown_remaining_seconds < (double)*(int *)(this + 700) )
      {
        v9 = 1;
      }
      if ( v9 )
      {
        for ( i = 0; i < rf_receiver_get_first_dword((void *)(this + 668)); ++i )
        {
          v1 = (int *)sub_552200((_DWORD *)(this + 668), i);
          v7 = (int *)rf_mission_event_find_by_uid(*v1);
          if ( v7 )
            rf_mission_event_activate(v7, -1, -1, 1);
          v2 = (int *)sub_552200((_DWORD *)(this + 668), i);
          v6 = rf_mover_resolve_handle(*v2);
          if ( v6 )
            rf_mover_activate_forward(*(_DWORD *)(v6 + 44), -1, -1);
          v3 = (int *)sub_552200((_DWORD *)(this + 668), i);
          v5 = rf_trigger_find_by_uid(*v3);
          if ( v5 )
            rf_trigger_set_forward_enabled(v5);
        }
        *(_BYTE *)(this + 697) = 1;
      }
    }
  }
}

