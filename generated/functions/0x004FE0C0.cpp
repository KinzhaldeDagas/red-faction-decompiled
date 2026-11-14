// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FE0C0 rf_event_shoot_once_forward
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_shoot_once forward, vtable0x63E050 slot+4. For each resolving entity first call guarded AI target setter0x40BA80(AI,-1). Mode dword event+0x2B8==0 arms entity+0x4B8 at0ms then calls0x431FD0(entity,0,0,0,0,0). Mode1 arms+0x4BC at0ms then calls0x433A90(entity,0). Other modes still request target clear but do not fire. Does not itself bypass downstream weapon/ammo/dead/cooldown gates or guarantee a successful shot.
int __thiscall rf_event_shoot_once_forward(_DWORD *this)
{
  int result; // eax
  int *v2; // eax
  int v3; // [esp+0h] [ebp-10h]
  int i; // [esp+8h] [ebp-8h]
  int *v6; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(this + 167);
    if ( i >= result )
      break;
    v2 = (int *)sub_552200(this + 167, i);
    v6 = (int *)rf_entity_resolve_handle(*v2);
    if ( v6 )
    {
      sub_40BA80(v6 + 168, -1);
      v3 = *(this + 174);
      if ( v3 )
      {
        if ( v3 == 1 )
        {
          rf_replicator_arm_milliseconds(v6 + 303, 0);
          rf_entity_fire_secondary_or_begin_charge(v6, 0);
        }
      }
      else
      {
        rf_replicator_arm_milliseconds(v6 + 302, 0);
        sub_431FD0(*(float *)&v6, 0, 0, nullptr, nullptr, nullptr);
      }
    }
  }
  return result;
}

