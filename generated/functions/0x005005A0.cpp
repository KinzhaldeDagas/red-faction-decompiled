// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005005A0 rf_event_set_ai_mode_dispatch
// UNREALRED VERIFIED [ai-set-mode-event-20260826]: Dispatches Set_AI_Mode by iterating target identifiers at event +0x29C, resolving entities only, running sub_40C340 first when owner +0x520 is 13, and writing event +0x2B8 with -1/-1. It also scans direct-owner attachment slots at +0x8CC, resolves each slot's +4 identifier, and writes the same mode only when sub_438AC0 is false. It does not recurse into target events.
int __thiscall rf_event_set_ai_mode_dispatch(int *this)
{
  int result; // eax
  int *v2; // eax
  int v3; // eax
  int v5; // [esp+4h] [ebp-10h]
  int j; // [esp+8h] [ebp-Ch]
  int *v7; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(this + 167);
    if ( i >= result )
      break;
    v2 = (int *)sub_552200(this + 167, i);
    v7 = (int *)rf_entity_resolve_handle(*v2);
    if ( v7 )
    {
      if ( v7[328] == 13 )
        sub_40C340(v7 + 168);
      rf_ai_numeric_mode_write(v7 + 168, *(this + 174), -1, -1);
      for ( j = 0; j < rf_receiver_get_first_dword(v7 + 563); ++j )
      {
        v3 = sub_552200(v7 + 563, j);
        v5 = rf_entity_resolve_handle(*(_DWORD *)(*(_DWORD *)v3 + 4));
        if ( v5 )
        {
          if ( !sub_438AC0(v5) )
            rf_ai_numeric_mode_write((_DWORD *)(v5 + 672), *(this + 174), -1, -1);
        }
      }
    }
  }
  return result;
}

