// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00415EF0 rf_clutter_toggle_first_two_skins
// UNREALRED VERIFIED [switch-clutter-reset] Requires at least two authored class skins, maps active index 0 to 1 and every nonzero index to 0, then applies that exact named skin.
int __cdecl rf_clutter_toggle_first_two_skins(int a1)
{
  int result; // eax
  const void *v2; // eax
  char *v3; // eax
  _DWORD *v4; // [esp+0h] [ebp-4h]

  result = rf_clutter_find_by_uid(a1);
  v4 = (_DWORD *)result;
  if ( result )
  {
    result = rf_receiver_get_first_dword((void *)(*(_DWORD *)(result + 660) + 200));
    if ( result >= 2 )
    {
      if ( v4[175] )
        v4[175] = 0;
      else
        v4[175] = 1;
      v2 = (const void *)rf_clutter_skin_record_at_index((_DWORD *)(v4[165] + 200), v4[175]);
      v3 = (char *)rf_string_object_c_str_or_empty(v2);
      return rf_clutter_apply_named_skin(v4, v3);
    }
  }
  return result;
}

