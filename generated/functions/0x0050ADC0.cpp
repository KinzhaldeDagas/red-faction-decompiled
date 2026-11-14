// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050ADC0 sub_50ADC0
// UNREALRED VERIFIED [combat-selected-drop-resource-20261111]: Registry-resource cleanup destroys each nonzero world handle at WeaponInfo+0x30 and writes zero. This is registry-lifetime resource ownership, separate from visibility of an equipped render component.
void __cdecl sub_50ADC0()
{
  char *v0; // [esp+0h] [ebp-Ch]
  int j; // [esp+4h] [ebp-8h]
  int k; // [esp+4h] [ebp-8h]
  int m; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  for ( i = 0; i < 64; ++i )
  {
    v0 = (char *)&rf_weapon_records + 1360 * i;
    if ( *((_DWORD *)v0 + 12) )
    {
      rf_model_handle_destroy_cdecl_adapter(*((_DWORD **)v0 + 12));
      *((_DWORD *)v0 + 12) = 0;
    }
    if ( *((_DWORD *)v0 + 338) )
    {
      rf_model_handle_destroy_cdecl_adapter(*((_DWORD **)v0 + 338));
      *((_DWORD *)v0 + 338) = 0;
    }
    for ( j = 0; j < 3; ++j )
    {
      rf_string_assign_from_cstr(&v0[28 * j + 672], (char *)&byte_63E713);
      rf_string_assign_from_cstr(&v0[28 * j + 680], (char *)&byte_63E741);
    }
    for ( k = 0; k < 12; ++k )
    {
      rf_string_assign_from_cstr(&v0[28 * k + 756], (char *)&byte_63E742);
      rf_string_assign_from_cstr(&v0[28 * k + 764], (char *)&byte_63E743);
    }
    for ( m = 0; m < *((_DWORD *)v0 + 276); ++m )
      rf_string_assign_from_cstr(&v0[8 * m + 1120], (char *)&byte_63E74D);
    rf_string_assign_from_cstr(v0, (char *)&byte_63E74E);
    rf_string_assign_from_cstr((_DWORD *)v0 + 4, (char *)&byte_63E74F);
    rf_string_assign_from_cstr((_DWORD *)v0 + 10, (char *)&byte_63E756);
    rf_string_assign_from_cstr((_DWORD *)v0 + 7, (char *)&byte_63E757);
    rf_string_assign_from_cstr((_DWORD *)v0 + 16, (char *)&byte_63E766);
    rf_string_assign_from_cstr((_DWORD *)v0 + 155, (char *)&byte_63E767);
    rf_string_assign_from_cstr((_DWORD *)v0 + 314, (char *)&byte_63E773);
    rf_string_assign_from_cstr((_DWORD *)v0 + 318, (char *)&byte_63E77D);
    rf_string_assign_from_cstr((_DWORD *)v0 + 302, (char *)&byte_63E77E);
    rf_string_assign_from_cstr((_DWORD *)v0 + 307, (char *)&byte_63E77F);
    rf_string_assign_from_cstr((_DWORD *)v0 + 336, (char *)&byte_63E78B);
    rf_string_assign_from_cstr((_DWORD *)v0 + 329, (char *)&byte_63E795);
    rf_string_assign_from_cstr((_DWORD *)v0 + 2, (char *)byte_63E796);
    if ( *((_DWORD *)v0 + 316) )
    {
      rf_model_handle_destroy_cdecl_adapter(*((_DWORD **)v0 + 316));
      *((_DWORD *)v0 + 316) = 0;
    }
    if ( *((_DWORD *)v0 + 320) )
    {
      rf_model_handle_destroy_cdecl_adapter(*((_DWORD **)v0 + 320));
      *((_DWORD *)v0 + 320) = 0;
    }
  }
  if ( dword_911CE4 )
  {
    rf_model_handle_destroy_cdecl_adapter(dword_911CE4);
    dword_911CE4 = nullptr;
  }
}

