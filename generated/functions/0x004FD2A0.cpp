// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FD2A0 rf_event_activate_capek_shield_apply_reverse
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic reverse type76. Set entity+0x814 bit0x20 and, when ambient handle+0x804!=-1, set source gain0.0. Voice handle remains stored; no stop/release call or field clear.
int __cdecl rf_event_activate_capek_shield_apply_reverse(int a1)
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
      *(_DWORD *)(v3 + 2068) |= 0x20u;
      if ( *(_DWORD *)(v3 + 2052) != -1 )
        rf_ambient_voice_set_source_gain(*(_DWORD *)(v3 + 2052), 0.0);
    }
  }
  return result;
}

