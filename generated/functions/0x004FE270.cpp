// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FE270 rf_script_apply_entity_state_or_action
// UNREALRED VERIFIED [mission-play-animation-20261013] Correction/expansion:0x437370 does NOT clear a general script context; it arms the entity idle-variation deadline for an inclusive random30000..60000ms before checking that entity slot. Resolved absent slots are skipped. Held action clears CYCLIC state weights via0x565000 and ACTIONS via0x565020, requests action mix1/hold/audio, then sets Entity+0x810 bit8. Unheld action retains existing records and does not clear bit8. State branch clears ACTIONS via0x565020 and adds/updates a CYCLIC record at mix1 via0x564F60; it neither clears all cyclic weights nor changes the normal scheduler state indices nor sets/clears bit8. State hold byte is unused. Type11 participates in common post-handler forwarding. Raw serialized Boolean is normalized by the RFL reader before the exact-one checks here.
int __thiscall rf_script_apply_entity_state_or_action(int this)
{
  int result; // eax
  int *v2; // eax
  int v4; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(this + 668));
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)(this + 668), i);
    v4 = rf_entity_resolve_handle(*v2);
    if ( v4 )
    {
      rf_entity_refresh_idle_animation_deadline(v4);
      if ( *(_BYTE *)(this + 700) == 1 )
      {
        if ( *(int *)(v4 + 16 * *(_DWORD *)(this + 696) + 2644) >= 0 )
        {
          if ( *(_BYTE *)(this + 701) == 1 )
          {
            rf_model_handle_reset_cyclic_adapter(*(_DWORD *)(v4 + 128));
            rf_model_handle_reset_actions_adapter(*(_DWORD *)(v4 + 128));
          }
          rf_entity_request_body_action(v4, *(_DWORD *)(this + 696), 1.0, *(_BYTE *)(this + 701), 1);
          if ( *(_BYTE *)(this + 701) == 1 )
            *(_DWORD *)(v4 + 2064) |= 8u;
        }
      }
      else if ( *(int *)(v4 + 16 * *(_DWORD *)(this + 696) + 2276) >= 0 )
      {
        rf_model_handle_reset_actions_adapter(*(_DWORD *)(v4 + 128));
        rf_model_handle_set_cyclic_mix_adapter(
          *(int **)(v4 + 128),
          *(_DWORD *)(v4 + 16 * *(_DWORD *)(this + 696) + 2276),
          1.0);
      }
    }
  }
  return result;
}

