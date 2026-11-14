// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BCB20 rf_object_level_cleanup_preserve_marked
// UNREALRED VERIFIED [level-lifecycle-20261028]: Traverses global object list0x7D0C90 to sentinel0x7D0C80, saves next pointer+16 before mutation. If object flags+124 include0x800 OR2 AND current panel0x446190()!=13, retains object: unless flag0x400 set, releases nonnull model+128 through unknown_libname_26, clears pointer and sets+132=-1; common type+36==0 also calls0x43BE70. Otherwise calls rf_object_delete_dispatch. Return incidental next/sentinel pointer, not deletion count.
int rf_object_level_cleanup_preserve_marked()
{
  int result; // eax
  int v1; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  result = unk_7D0C90;
  for ( i = unk_7D0C90; (_UNKNOWN *)i != &unk_7D0C80; i = v1 )
  {
    v1 = *(_DWORD *)(i + 16);
    if ( ((*(_DWORD *)(i + 124) & 0x800) != 0 || (*(_DWORD *)(i + 124) & 2) != 0)
      && rf_ui_panel_stack_current_id() != 13 )
    {
      if ( (*(_DWORD *)(i + 124) & 0x400) == 0 && *(_DWORD *)(i + 128) )
      {
        rf_model_handle_destroy_cdecl_adapter(*(_DWORD **)(i + 128));
        *(_DWORD *)(i + 128) = 0;
        *(_DWORD *)(i + 132) = -1;
      }
      if ( !*(_DWORD *)(i + 36) )
        rf_entity_release_auxiliary_models_and_arrays(i);
    }
    else
    {
      rf_object_delete_dispatch((_DWORD *)i);
    }
    result = v1;
  }
  return result;
}

