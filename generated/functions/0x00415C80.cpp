// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00415C80 rf_clutter_prepare_primary_and_corpse_models
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter runtime teardown/render admission, DWORD-category glass callback, cached model binding and signed-counter clock-hand geometry): Noargs. Walks clutter head through object652 until sentinel666D18. Prepares materials on primarymodel128 via NULL-aware helper. If corpseClass668!=integer-1,uses unchecked class slot667000+232*id,RFString filename+8;loads V3M mode1 with requested mode1/arg-1,stores result into secondarymodel696,then prepares it ifnonNULL. No own classindex/modelkind validation or destruction of previous696 before overwrite. Does not use corpse-class .vfx kind dispatch;no list-integrity guard/rollback. Returns incidental last iterator/delegateEAX,not loaded count.
int rf_clutter_prepare_primary_and_corpse_models()
{
  int result; // eax
  char *v1; // eax
  int i; // [esp+0h] [ebp-4h]

  result = rf_clutter_list_head;
  for ( i = rf_clutter_list_head; (_UNKNOWN *)i != &unk_666D18; i = *(_DWORD *)(i + 652) )
  {
    result = rf_model_handle_prepare_materials_if_nonnull(*(_DWORD **)(i + 128));
    if ( *(_DWORD *)(i + 668) != -1 )
    {
      v1 = (char *)rf_string_object_c_str_or_empty((char *)&unk_667008 + 232 * *(_DWORD *)(i + 668));
      result = rf_model_handle_load_v3m_mode1(v1, 1, (void *)0xFFFFFFFF);
      *(_DWORD *)(i + 696) = result;
      if ( *(_DWORD *)(i + 696) )
        result = rf_model_handle_prepare_materials_if_nonnull(*(_DWORD **)(i + 696));
    }
  }
  return result;
}

