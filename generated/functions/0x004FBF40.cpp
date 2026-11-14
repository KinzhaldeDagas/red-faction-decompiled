// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FBF40 rf_event_bolt_state_apply_forward
// UNREALRED VERIFIED [world-uid-ownership]: Bolt_State type 43 forward handler: refreshes each target emitter's saved attachment and derived endpoint state, then enables it.
int __cdecl rf_event_bolt_state_apply_forward(int a1)
{
  int result; // eax
  int *v2; // eax
  int i; // [esp+0h] [ebp-8h]
  int *v4; // [esp+4h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(a1 + 668));
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
    v4 = (int *)rf_bolt_emitter_find_by_uid(*v2);
    if ( v4 )
    {
      rf_bolt_emitter_refresh_attachment(v4);
      rf_bolt_emitter_enable((int)v4);
    }
  }
  return result;
}

