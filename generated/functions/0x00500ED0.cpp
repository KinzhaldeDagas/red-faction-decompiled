// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00500ED0 rf_event_detach_forward
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_detach forward, vtable0x63E30C slot+4. Iterate common-object targets; call player predicate then require non-null nonplayer owner. Resolve parent/entity identifier owner+0x200; if entity resolves call0x4343A0(entity,owner id,1). Repeatedly query0x48B1B0(owner); for each nonzero result call0x48B280(result,owner) and write owner+0x30=-1. No detach attempts for player-associated owners; helper internals and full heterogeneous attachment teardown are not inferred from this handler alone.
int __thiscall rf_event_detach_forward(char *this)
{
  int result; // eax
  int *v2; // eax
  int v4; // [esp+4h] [ebp-10h]
  int *v5; // [esp+8h] [ebp-Ch]
  int v6; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(this + 668);
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)this + 167, i);
    v5 = (int *)rf_object_resolve_handle(*v2);
    if ( !rf_object_has_player_flag((int)v5) && v5 )
    {
      v4 = rf_entity_resolve_handle(v5[128]);
      if ( v4 )
        rf_entity_detach_first_matching_child(v4, v5[11], 1);
      while ( 1 )
      {
        v6 = rf_mover_find_for_linked_object((int)v5);
        if ( !v6 )
          break;
        rf_mover_detach_linked_object(v6, (int)v5);
        v5[12] = -1;
      }
    }
  }
  return result;
}

