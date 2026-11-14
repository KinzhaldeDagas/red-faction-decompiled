// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FC840 rf_event_activate_capek_shield_apply_forward
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic forward type76 Activate_Capek_Shield. For each entity target clear entity+0x814 bit0x20; when ambient handle+0x804!=-1 set its source gain1.0. Does not allocate a new ambient voice or invoke a graphics/shield renderer directly.
int __cdecl rf_event_activate_capek_shield_apply_forward(int a1)
{
  int result; // eax
  int *v2; // eax
  int v3; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(a1 + 668));
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
    v3 = rf_entity_resolve_handle(*v2);
    if ( v3 )
    {
      *(_DWORD *)(v3 + 2068) &= ~0x20u;
      if ( *(_DWORD *)(v3 + 2052) != -1 )
        rf_ambient_voice_set_source_gain(*(_DWORD *)(v3 + 2052), 1.0);
    }
  }
  return result;
}

