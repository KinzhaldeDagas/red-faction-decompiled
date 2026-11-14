// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00501390 rf_event_enable_nav_point_forward
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_enable_nav_point forward, vtable0x63E370 slot+4. Treat authored target values as SIGNED INDICES into vector rf_world_solid+0x300, requiring0<=index<count. Copy selected nav record float+0x18 to+0x1C. These are not common-object identifiers; no entity resolver or flags mutation in body.
int __thiscall rf_event_enable_nav_point_forward(char *this)
{
  int result; // eax
  int *v2; // esi
  int *v3; // eax
  int v4; // eax
  int i; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(this + 668);
    if ( i >= result )
      break;
    if ( *(int *)sub_552200((_DWORD *)this + 167, i) >= 0 )
    {
      v2 = (int *)sub_552200((_DWORD *)this + 167, i);
      if ( *v2 < rf_receiver_get_first_dword((void *)(rf_world_solid + 768)) )
      {
        v3 = (int *)sub_552200((_DWORD *)this + 167, i);
        v4 = sub_552200((_DWORD *)(rf_world_solid + 768), *v3);
        *(float *)(*(_DWORD *)v4 + 28) = *(float *)(*(_DWORD *)v4 + 24);
      }
    }
  }
  return result;
}

