// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00501450 rf_event_enable_nav_point_reverse
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_enable_nav_point reverse, vtable0x63E370 slot+8. Same signed index bounds as forward against rf_world_solid+0x300 vector; write selected record float+0x1C=0. Does not restore prior runtime value or change authored value+0x18.
int __thiscall rf_event_enable_nav_point_reverse(char *this)
{
  int result; // eax
  int *v2; // esi
  int *v3; // eax
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
        *(float *)(*(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 768), *v3) + 28) = 0.0;
      }
    }
  }
  return result;
}

