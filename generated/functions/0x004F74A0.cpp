// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F74A0 rf_mission_target_activate_reverse_by_uid
// UNREALRED VERIFIED [mission-invert-20261020] Verified assembly0x4F74BB..C8 passes arg8 to BOTH nested-event context arguments, ignoring arg4 on the event branch. Invert forward supplies arg8=-1, clearing trigger/object context even across deferred activation. Target precedence event,trigger,mover(if suppression0),ambient; direct lights have no route. Invert uses suppression0; generic reverse propagation uses1.
// UNREALRED VERIFIED [combat-push-region-router-20261104]: Event-first then trigger-first reverse router. When arg_C suppression is nonzero (ordinary generic completion0x4FB200 supplies1), mover lookup is skipped and the ambient lookup still executes. Thus a mover+ambient UID collision disables ambient while leaving the mover untouched. Do not skip ambient merely because a mover with that UID exists. With suppression0 (e.g.Invert), a resolved mover stops and returns before ambient.
char __cdecl rf_mission_target_activate_reverse_by_uid(int a1, int a2, int a3, char a4)
{
  int *v4; // eax
  int v6; // [esp+0h] [ebp-10h]
  int v7; // [esp+4h] [ebp-Ch]
  int *v8; // [esp+8h] [ebp-8h]

  v8 = (int *)rf_mission_event_find_by_uid(a1);
  if ( v8 )
  {
    LOBYTE(v4) = rf_mission_event_activate(v8, a3, a3, 0);
  }
  else
  {
    v7 = rf_trigger_find_by_uid(a1);
    if ( v7 )
    {
      LOBYTE(v4) = rf_trigger_set_reverse_disabled(v7);
    }
    else if ( a4 || (v6 = rf_mover_resolve_handle(a1)) == 0 )
    {
      v4 = rf_ambient_sound_find_by_uid(a1);
      if ( v4 )
        LOBYTE(v4) = rf_ambient_sound_disable_by_uid(v4[2]);
    }
    else
    {
      LOBYTE(v4) = rf_mover_stop_by_uid(*(_DWORD *)(v6 + 44));
    }
  }
  return (char)v4;
}

