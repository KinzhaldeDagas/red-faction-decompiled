// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FFE40 rf_event_follow_waypoints_forward
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_follow_waypoints forward, vtable0x63E17C slot+4. For each resolving entity, byte event+0x2C5==1 sets entity+0x810 bit0x100000 before route installation; other values do not clear it. Call0x434070(target id,event string+0x2BC,dword+0x2B8). Only return!=-1 assigns AI mode4(-1,-1) and writes entity+0x7D0 bit8 according to byte event+0x2C4==1. Failed installation retains earlier bit0x100000 and does not update mode or bit8 in this body.
int __thiscall rf_event_follow_waypoints_forward(int this)
{
  int result; // eax
  int *v2; // eax
  int *v3; // eax
  unsigned int v4; // ecx
  char *v5; // [esp-8h] [ebp-14h]
  int v6; // [esp-4h] [ebp-10h]
  int i; // [esp+4h] [ebp-8h]
  _DWORD *v9; // [esp+8h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(this + 668));
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)(this + 668), i);
    v9 = (_DWORD *)rf_entity_resolve_handle(*v2);
    if ( v9 )
    {
      if ( *(_BYTE *)(this + 709) == 1 )
        v9[516] |= 0x100000u;
      v6 = *(_DWORD *)(this + 696);
      v5 = (char *)rf_string_object_c_str_or_empty((const void *)(this + 700));
      v3 = (int *)sub_552200((_DWORD *)(this + 668), i);
      if ( sub_434070(*v3, v5, v6) != -1 )
      {
        rf_ai_numeric_mode_write(v9 + 168, 4, -1, -1);
        if ( *(_BYTE *)(this + 708) == 1 )
          v4 = v9[500] | 8;
        else
          v4 = v9[500] & 0xFFFFFFF7;
        v9[500] = v4;
      }
    }
  }
  return result;
}

