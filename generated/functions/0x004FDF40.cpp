// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FDF40 rf_event_look_at_forward
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_look_at forward, vtable0x63E03C slot+4. Entity targets with numeric state+0x520 exactly7 or3 are skipped. Nonzero event+0x2B8 is resolved by0x4BC680 and, on success, its common id+0x2C copied to entity look target+0x574. Zero event field instead copies raw event+0x30. Failed nonzero lookup leaves prior look target intact; any resulting non--1 look target requests mode8(-1,-1) and clears scripted animation context. No direct aim-matrix write in this body.
int __thiscall rf_event_look_at_forward(int *this)
{
  int result; // eax
  int *v2; // eax
  int v4; // [esp+4h] [ebp-Ch]
  int i; // [esp+8h] [ebp-8h]
  _DWORD *v6; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(this + 167);
    if ( i >= result )
      break;
    v2 = (int *)sub_552200(this + 167, i);
    v6 = (_DWORD *)rf_entity_resolve_handle(*v2);
    if ( v6 && v6[328] != 7 && v6[328] != 3 )
    {
      if ( *(this + 174) )
      {
        v4 = rf_object_find_by_saved_identifier(*(this + 174));
        if ( v4 )
          v6[349] = *(_DWORD *)(v4 + 44);
      }
      else
      {
        v6[349] = *(this + 12);
      }
      if ( v6[349] != -1 )
      {
        rf_ai_numeric_mode_write(v6 + 168, 8, -1, -1);
        rf_ai_clear_scripted_animation_context(v6 + 168);
      }
    }
  }
  return result;
}

