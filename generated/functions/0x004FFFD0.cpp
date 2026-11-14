// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FFFD0 rf_event_set_light_state_apply_forward
// UNREALRED VERIFIED [world-uid-ownership]: Set_Light_State type 31 forward handler: state -1 is a no-op, while observed states 0 and 1 both enable resolved light targets; no disable mapping is inferred.
int __fastcall rf_event_set_light_state_apply_forward(int a1)
{
  int result; // eax
  int *v2; // eax
  int v4; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  result = a1;
  if ( *(_DWORD *)(a1 + 696) != -1 )
  {
    for ( i = 0; ; ++i )
    {
      result = rf_receiver_get_first_dword((void *)(a1 + 668));
      if ( i >= result )
        break;
      v2 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
      v4 = rf_rfl_light_find_by_uid(*v2);
      if ( v4 )
      {
        if ( *(_DWORD *)(a1 + 696) < 2u )
          rf_rfl_light_set_enabled(v4, 1);
      }
    }
  }
  return result;
}

