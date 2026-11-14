// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FE040 rf_event_look_at_reverse
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_look_at reverse, vtable0x63E03C slot+8. For every entity target call AI restore helper0x40A2A0(entity+0x2A0), then set look target entity+0x574=-1. Unlike forward, does not skip numeric states3/7 or resolve the requested look target.
int __thiscall rf_event_look_at_reverse(int this)
{
  int result; // eax
  int *v2; // eax
  int i; // [esp+4h] [ebp-8h]
  int v5; // [esp+8h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(this + 668));
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)(this + 668), i);
    v5 = rf_entity_resolve_handle(*v2);
    if ( v5 )
    {
      sub_40A2A0((int *)(v5 + 672));
      *(_DWORD *)(v5 + 1396) = -1;
    }
  }
  return result;
}

