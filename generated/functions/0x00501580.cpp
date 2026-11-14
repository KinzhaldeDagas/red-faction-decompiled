// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00501580 rf_event_mover_pause_apply_forward
// UNREALRED VERIFIED [mission-mover-events-20261020] Mover_Pause forward handler sets pause bit0x80 for each resolved mover. Type72 then uses ordinary automatic forward propagation; a target idle mover can be activated by that later route while remaining paused. Linked events/triggers/ambient owners remain separate generic actions.
int __thiscall rf_event_mover_pause_apply_forward(int this)
{
  int result; // eax
  int *v2; // eax
  int v4; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(this + 668));
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)(this + 668), i);
    v4 = rf_mover_resolve_handle(*v2);
    if ( v4 )
      rf_mover_set_paused(v4);
  }
  return result;
}

