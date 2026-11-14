// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F73F0 rf_mission_target_activate_forward_by_uid
// UNREALRED VERIFIED [mission-when-dead-targets-20261013] Explicit generic event forwarding resolves type6 event first, then type5 trigger forward-enable, then type8 mover activation, then ambient enable. When_Dead autonomous forwarding at 0x4FE940 separately checks event/mover/trigger, and does not include the ambient fallback. Both paths enable type5 rather than activating trigger links directly.
// UNREALRED VERIFIED [mission-invert-20261020] Invert reverse calls this with retained trigger/event+0x2AC and object context=-1. Resolver order event,trigger,mover,ambient; enabling a trigger does not commit its linked actions. Unknown IDs and direct lights are no-ops unless another admitted owner resolves the same UID.
// UNREALRED VERIFIED [combat-push-region-router-20261104]: Ordinary generic forward completion resolves event UID first, then trigger UID, then mover, then ambient. A trigger and mover sharing a UID must enable the trigger and leave the mover untouched. Push_Region_State(type51) local first-region write is a separate preceding operation; it does not consume or suppress this completion lookup.
char __cdecl rf_mission_target_activate_forward_by_uid(int a1, int a2, int a3)
{
  int *v3; // eax
  int v5; // [esp+0h] [ebp-10h]
  int *v6; // [esp+4h] [ebp-Ch]
  int v7; // [esp+Ch] [ebp-4h]

  v6 = (int *)rf_mission_event_find_by_uid(a1);
  if ( v6 )
  {
    LOBYTE(v3) = rf_mission_event_activate(v6, a2, a3, 1);
  }
  else
  {
    v5 = rf_trigger_find_by_uid(a1);
    if ( v5 )
    {
      LOBYTE(v3) = rf_trigger_set_forward_enabled(v5);
    }
    else
    {
      v7 = rf_mover_resolve_handle(a1);
      if ( v7 )
      {
        LOBYTE(v3) = rf_mover_activate_forward(*(_DWORD *)(v7 + 44), a2, a3);
      }
      else
      {
        v3 = rf_ambient_sound_find_by_uid(a1);
        if ( v3 )
          LOBYTE(v3) = rf_ambient_sound_enable_by_uid(v3[2]);
      }
    }
  }
  return (char)v3;
}

