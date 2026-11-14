// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00414520 rf_clutter_class_registry_shutdown
// UNREALRED VERIFIED [switch-clutter-reset] Destroys all 450 clutter class slots, including every ordered named-skin record and its positional texture-name array.
void __cdecl rf_clutter_class_registry_shutdown()
{
  _DWORD *v0; // eax
  int v1; // eax
  int k; // [esp+0h] [ebp-10h]
  char *v3; // [esp+4h] [ebp-Ch]
  int j; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  for ( i = 0; i < 450; ++i )
  {
    v3 = &byte_667000[232 * i];
    rf_string_assign_from_cstr(v3, (char *)&byte_631296);
    rf_string_assign_from_cstr((_DWORD *)v3 + 2, (char *)&byte_631297);
    rf_string_assign_from_cstr((_DWORD *)v3 + 4, (char *)&byte_6312A1);
    rf_string_assign_from_cstr((_DWORD *)v3 + 6, (char *)&byte_6312A2);
    rf_string_assign_from_cstr((_DWORD *)v3 + 8, (char *)&byte_6312A3);
    rf_pointer_array_clear_count_keep_storage((_DWORD *)v3 + 33);
    rf_pointer_array_release_storage((void **)v3 + 10);
    for ( j = 0; j < rf_receiver_get_first_dword(v3 + 200); ++j )
    {
      v0 = (_DWORD *)rf_clutter_skin_record_at_index((_DWORD *)v3 + 50, j);
      rf_string_assign_from_cstr(v0, (char *)&byte_6312AE);
      for ( k = 0; k < *(_DWORD *)(rf_clutter_skin_record_at_index((_DWORD *)v3 + 50, j) + 8); ++k )
      {
        v1 = rf_clutter_skin_record_at_index((_DWORD *)v3 + 50, j);
        rf_string_assign_from_cstr((_DWORD *)(v1 + 8 * k + 12), (char *)&byte_6312AF);
      }
    }
    rf_clutter_skin_array_release_storage((_DWORD *)v3 + 50);
    rf_pointer_array_release_storage((void **)v3 + 53);
  }
}

