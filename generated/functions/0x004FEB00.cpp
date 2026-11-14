// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FEB00 rf_event_continuous_damage_update
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Recurring-damage detail: target-vector entries resolving as COMMON objects receive signed integer rate event+0x2B8*frame_delta_seconds when nonzero, else10000.0 instant amount, with authored cause+0x2BC and final dispatcher bypass argument1. Separate stored context id+0x2A8!=-1 resolves entity; reject null/dead or attached-use-vehicle context before extra damage using that entity id as source. Context also present in targets can receive both routes. No common delayed/special update, explicit enabled-byte/dead-target gate for listed objects, or per-target uniqueness in this body. No claim that negative rates are accepted by downstream damage dispatcher.
char __thiscall rf_event_continuous_damage_update(int *this)
{
  int first_dword; // eax
  int *v2; // eax
  int *v3; // eax
  int *v4; // eax
  int v6; // [esp+Ch] [ebp-2Ch]
  int v7; // [esp+Ch] [ebp-2Ch]
  float v8; // [esp+20h] [ebp-18h]
  float v9; // [esp+24h] [ebp-14h]
  int v11; // [esp+2Ch] [ebp-Ch]
  int i; // [esp+30h] [ebp-8h]
  int v13; // [esp+34h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword(this + 167);
    if ( i >= first_dword )
      break;
    v2 = (int *)sub_552200(this + 167, i);
    if ( rf_object_resolve_handle(*v2) )
    {
      if ( *(this + 174) )
      {
        v7 = *(this + 175);
        v9 = (double)*(this + 174) * rf_frame_delta_seconds;
        v4 = (int *)sub_552200(this + 167, i);
        rf_damage_dispatch(*v4, v9, -1, -1, v7, 0, -1, 1);
      }
      else
      {
        v6 = *(this + 175);
        v3 = (int *)sub_552200(this + 167, i);
        rf_damage_dispatch(*v3, 10000.0, -1, -1, v6, 0, -1, 1);
      }
    }
  }
  if ( *(this + 170) != -1 )
  {
    v11 = rf_entity_resolve_handle(*(this + 170));
    LOBYTE(first_dword) = rf_entity_has_attached_use_vehicle(v11);
    if ( (unsigned __int8)first_dword != 1 )
    {
      LOBYTE(first_dword) = rf_entity_is_dead(v11);
      if ( (unsigned __int8)first_dword != 1 )
      {
        if ( *(this + 174) )
        {
          v8 = (double)*(this + 174) * rf_frame_delta_seconds;
          rf_damage_dispatch(*(this + 170), v8, *(_DWORD *)(v11 + 44), -1, *(this + 175), 0, -1, 1);
        }
        else
        {
          rf_damage_dispatch(*(this + 170), 10000.0, *(_DWORD *)(v11 + 44), -1, *(this + 175), 0, -1, 1);
        }
        v13 = rf_object_resolve_handle(*(this + 170));
        LOBYTE(first_dword) = rf_entity_has_player_pointer_if_type0(v13);
        if ( (_BYTE)first_dword )
        {
          first_dword = *(this + 175);
          switch ( first_dword )
          {
            case 0:
            case 3:
            case 5:
            case 6:
              LOBYTE(first_dword) = rf_entity_set_player_linked_perturbation_timer(
                                      *(_DWORD *)(*(_DWORD *)(v13 + 5168) + 196),
                                      0.0099999998,
                                      0.5);
              break;
            default:
              return first_dword;
          }
        }
      }
    }
  }
  return first_dword;
}

