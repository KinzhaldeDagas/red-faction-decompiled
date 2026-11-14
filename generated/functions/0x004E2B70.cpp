// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E2B70 rf_player_advance_attached_cockpit_animation
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): Assumes player nonNULL; resolve own entity UID+20, missing exits. Linked jeep seat0 predicate439000 NONZERO: only if GLOBAL byte87C6B4==0 resolve linked cockpit model handle via2C40, advance animation564F30(handle,F320.25,0,own entity position2004,matrix72,1) WITHOUT checking returned handle, then set global byte1. Later seat0 calls skip until4E4C30 clears global latch. Other seats/modes resolve handle, advance with frame delta only if handle!=0. Latch is shared, not per-player, and not cleared by leaving seat0. Return EAX is delegate/predicate residue, not uniform handle/status.
int *__cdecl rf_player_advance_attached_cockpit_animation(int a1)
{
  int *result; // eax
  int *attached_cockpit_model_handle; // [esp+18h] [ebp-8h]
  int *v3; // [esp+1Ch] [ebp-4h]

  result = (int *)rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  v3 = result;
  if ( result )
  {
    result = (int *)rf_entity_is_parent_jeep_relation0((int)result);
    if ( (_BYTE)result )
    {
      if ( !unk_87C6B4 )
      {
        attached_cockpit_model_handle = (int *)rf_player_get_attached_cockpit_model_handle(a1);
        result = rf_vfx_update_instance(attached_cockpit_model_handle, 0.25, 0, (int)(v3 + 501), (int)(v3 + 18), 1);
        unk_87C6B4 = 1;
      }
    }
    else
    {
      result = (int *)rf_player_get_attached_cockpit_model_handle(a1);
      if ( result )
        return rf_vfx_update_instance(result, rf_frame_delta_seconds, 0, (int)(v3 + 501), (int)(v3 + 18), 1);
    }
  }
  return result;
}

