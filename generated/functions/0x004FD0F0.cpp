// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FD0F0 rf_event_bolt_state_apply_reverse
// UNREALRED VERIFIED [world-uid-ownership]: Bolt_State type 43 reverse handler: resolves every authored target and disables the matching bolt emitter.
int __cdecl rf_event_bolt_state_apply_reverse(int a1)
{
  int result; // eax
  int *v2; // eax
  int i; // [esp+0h] [ebp-8h]
  float *v4; // [esp+4h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(a1 + 668));
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
    v4 = (float *)rf_bolt_emitter_find_by_uid(*v2);
    if ( v4 )
      rf_bolt_emitter_disable(v4);
  }
  return result;
}

