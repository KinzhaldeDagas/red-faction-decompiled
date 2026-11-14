// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FF0B0 rf_event_switch_model_forward
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_switch_model forward, vtable0x63E140 slot+4. Walk common-object targets; missing target skips. Type0 resolves named definition via0x435A90; type4 via0x415D50 using event string+0x2B8. Any other resolved type RETURNS from whole handler, and failed supported definition lookup also returns, skipping all later targets. Success calls0x4BBFC0(old owner) then0x4BC000(owner,requested_name,new_definition). No item/type1 path or per-target failure continuation.
int __thiscall rf_event_switch_model_forward(int this)
{
  int result; // eax
  int *v2; // eax
  char *v3; // eax
  char *v4; // eax
  char *v5; // eax
  int v6; // [esp+0h] [ebp-14h]
  int v8; // [esp+8h] [ebp-Ch]
  int v9; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(this + 668));
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)(this + 668), i);
    v8 = rf_object_resolve_handle(*v2);
    if ( v8 )
    {
      result = v8;
      v6 = *(_DWORD *)(v8 + 36);
      if ( v6 )
      {
        if ( v6 != 4 )
          return result;
        v4 = (char *)rf_string_object_c_str_or_empty((const void *)(this + 696));
        result = rf_clutter_model_kind_for_first_filename_match(v4);
        v9 = result;
      }
      else
      {
        v3 = (char *)rf_string_object_c_str_or_empty((const void *)(this + 696));
        result = rf_entity_definition_field94_by_string8(v3);
        v9 = result;
      }
      if ( !v9 )
        return result;
      rf_object_release_owned_model_handle(v8);
      v5 = (char *)rf_string_object_c_str_or_empty((const void *)(this + 696));
      rf_object_bind_model_filename_by_kind(v8, v5, v9);
    }
  }
  return result;
}

