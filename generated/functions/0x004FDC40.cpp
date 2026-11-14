// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FDC40 rf_event_slay_forward
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] event_slay forward callback, vtable0x63E000 slot+4. Resolve each target as a common object, clear common flags+0x7C bit4, then send damage100000.0f for exact runtime types0,1,4 with argument tail(-1,-1,-1,0,-1,0); all other types are marked for deferred deletion. After damage, type0 is resolved again as entity and event raw dword+0x2B8 copied to entity+0x83C if resolution succeeds, without checking damage return or death state. No direct immediate object destruction or explicit mission forwarding in this body.
int __thiscall rf_event_slay_forward(_DWORD *this)
{
  int result; // eax
  int *v2; // eax
  int v4; // [esp+20h] [ebp-Ch]
  int i; // [esp+24h] [ebp-8h]
  _DWORD *v6; // [esp+28h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(this + 167);
    if ( i >= result )
      break;
    v2 = (int *)sub_552200(this + 167, i);
    v6 = (_DWORD *)rf_object_resolve_handle(*v2);
    if ( v6 )
    {
      v6[31] &= ~4u;
      if ( v6[9] < 2u || v6[9] == 4 )
        rf_damage_dispatch(v6[11], 100000.0, -1, -1, -1, 0, -1, 0);
      else
        rf_object_mark_for_deferred_delete((int)v6);
      if ( !v6[9] )
      {
        v4 = rf_entity_resolve_handle(v6[11]);
        if ( v4 )
          *(_DWORD *)(v4 + 2108) = *(this + 174);
      }
    }
  }
  return result;
}

