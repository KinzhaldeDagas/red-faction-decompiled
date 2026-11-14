// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FDE30 rf_event_goto_player_forward
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_goto_player forward, vtable0x63E028 slot+4. Resolve each authored target as entity; clear entity+0x7D0 bits0x800 and8, arm entity+0x4D0 at0ms, assign AI mode10(-1,-1), secondary state12, and clear scripted animation context. Byte event+0x2B8==1 calls0x4355A0(entity); all other byte values call0x435500(entity,0). No player-position lookup or route construction directly in this handler; downstream AI owns movement.
int __thiscall rf_event_goto_player_forward(_BYTE *this)
{
  int result; // eax
  int *v2; // eax
  int i; // [esp+4h] [ebp-8h]
  _DWORD *v5; // [esp+8h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(this + 668);
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)this + 167, i);
    v5 = (_DWORD *)rf_entity_resolve_handle(*v2);
    if ( v5 )
    {
      v5[500] &= ~0x800u;
      v5[500] &= ~8u;
      rf_replicator_arm_milliseconds(v5 + 308, 0);
      rf_ai_numeric_mode_write(v5 + 168, 10, -1, -1);
      rf_ai_secondary_state_write((int)(v5 + 168), 12);
      rf_ai_clear_scripted_animation_context(v5 + 168);
      if ( *(this + 696) == 1 )
        sub_4355A0((int)v5);
      else
        sub_435500((int)v5, 0);
    }
  }
  return result;
}

