// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00500090 rf_event_switch_apply_targets
// UNREALRED VERIFIED [mission-mover-activation-20261013] Switch target precedence is trigger, mover, ambient, light, event/common fallback. Mover state0 starts via0x489BB0 with retained source context; nonzero state calls stop0x48ABB0. This is separate from reverse-direction generic forwarding, which suppresses movers.
// UNREALRED VERIFIED [mission-invert-20261020] Context distinction verified for Invert callers: Switch target fallback activates a nested event directly with retained +0x2AC/+0x2A8 contexts in either direction. It does not use0x4F74A0 and therefore does not apply that routers arg8 duplication.
int __thiscall rf_event_switch_apply_targets(int *this, char a2)
{
  int result; // eax
  int *v3; // eax
  int *v4; // eax
  int *v5; // eax
  int *v6; // eax
  int *v7; // eax
  int *v8; // eax
  int v9; // [esp+0h] [ebp-24h]
  int *v11; // [esp+8h] [ebp-1Ch]
  int *v12; // [esp+Ch] [ebp-18h]
  int v13; // [esp+10h] [ebp-14h]
  int v14; // [esp+14h] [ebp-10h]
  _DWORD *v15; // [esp+18h] [ebp-Ch]
  int v16; // [esp+1Ch] [ebp-8h]
  int i; // [esp+20h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(this + 167);
    if ( i >= result )
      break;
    v3 = (int *)sub_552200(this + 167, i);
    v14 = rf_trigger_find_by_uid(*v3);
    if ( v14 )
    {
      if ( *(this + 174) )
        rf_trigger_set_reverse_disabled(v14);
      else
        rf_trigger_set_forward_enabled(v14);
    }
    else
    {
      v4 = (int *)sub_552200(this + 167, i);
      v13 = rf_mover_resolve_handle(*v4);
      if ( v13 )
      {
        if ( *(this + 174) )
          rf_mover_stop_by_uid(*(_DWORD *)(v13 + 44));
        else
          rf_mover_activate_forward(*(_DWORD *)(v13 + 44), *(this + 171), *(this + 170));
      }
      else
      {
        v5 = (int *)sub_552200(this + 167, i);
        v12 = rf_ambient_sound_find_by_uid(*v5);
        if ( v12 )
        {
          if ( *(this + 174) )
            rf_ambient_sound_disable_by_uid(v12[2]);
          else
            rf_ambient_sound_enable_by_uid(v12[2]);
        }
        else
        {
          v6 = (int *)sub_552200(this + 167, i);
          v16 = rf_rfl_light_find_by_uid(*v6);
          if ( v16 )
          {
            v9 = *(this + 174);
            if ( v9 )
            {
              if ( v9 == 1 )
                rf_rfl_light_set_enabled(v16, 0);
            }
            else
            {
              rf_rfl_light_set_enabled(v16, 1);
            }
          }
          else
          {
            v7 = (int *)sub_552200(this + 167, i);
            v11 = (int *)rf_mission_event_find_by_uid(*v7);
            if ( v11 )
            {
              if ( v11[164] == 17 )
              {
                if ( *(this + 174) )
                  rf_mission_event_set_disabled_flag((int)v11);
                else
                  rf_mission_event_clear_disabled_flag((int)v11);
              }
              else if ( !a2 )
              {
                if ( *(this + 174) )
                  rf_mission_event_activate(v11, *(this + 171), *(this + 170), 0);
                else
                  rf_mission_event_activate(v11, *(this + 171), *(this + 170), 1);
              }
            }
            v8 = (int *)sub_552200(this + 167, i);
            v15 = (_DWORD *)rf_object_resolve_handle(*v8);
            if ( v15 && v15[32] )
            {
              if ( *(this + 174) )
                rf_object_mark_hidden_inactive((int)v15);
              else
                rf_object_reactivate_from_respawn(v15);
            }
          }
        }
      }
    }
  }
  return result;
}

