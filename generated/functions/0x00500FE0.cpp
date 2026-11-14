// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00500FE0 rf_event_modify_rotating_mover_apply_forward
// UNREALRED VERIFIED [mission-mover-events-20261020] Modify_Rotating_Mover forward handler resolves each target through the COMMON object resolver and applies0x48A7E0 with operation byte+0x2B8 and percentage float+0x2BC. No automatic forwarding after type66, including reverse. Source assumes a mover-shaped object; no type check in this core call.
int __thiscall rf_event_modify_rotating_mover_apply_forward(int this)
{
  int result; // eax
  int *v2; // eax
  int v4; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(this + 668));
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)(this + 668), i);
    v4 = rf_object_resolve_handle(*v2);
    if ( v4 )
      rf_mover_modify_first_key_travel_times(v4, *(_BYTE *)(this + 696), *(float *)(this + 700));
  }
  return result;
}

