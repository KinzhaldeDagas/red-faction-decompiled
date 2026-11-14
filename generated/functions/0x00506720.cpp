// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00506720 rf_vclip_effect_system_clear
// UNREALRED VERIFIED [resource-pools-20261028]: Destroys128 active runtime records (exact byte+60==1), then across64 definitions of224 bytes at0x90DC80 assigns constants to RF string fields+0,+12,+36. Clears definition count0x90B820. Does not free fixed pool arrays.
void __cdecl rf_vclip_effect_system_clear()
{
  int i; // [esp+0h] [ebp-4h]
  int j; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 128; ++i )
  {
    if ( unk_90B8BC[72 * i] == 1 )
      rf_vclip_effect_destroy_runtime_record((int)&unk_90B880 + 72 * i);
  }
  for ( j = 0; j < 64; ++j )
  {
    rf_string_assign_from_cstr((_DWORD *)&unk_90DC80 + 56 * j, (char *)&byte_63E4DF);
    rf_string_assign_from_cstr((_DWORD *)&unk_90DC8C + 56 * j, (char *)&byte_63E4FF);
    rf_string_assign_from_cstr((_DWORD *)&unk_90DCA4 + 56 * j, (char *)&byte_63E50D);
  }
  unk_90B820 = 0;
}

