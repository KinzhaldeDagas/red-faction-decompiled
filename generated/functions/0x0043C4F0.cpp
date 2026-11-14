// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C4F0 sub_43C4F0
// UNREALRED VERIFIED [combat-named-sphere-binding-20261112]: Mode-switchwriter loops existing modelclass+CEC40-byte records and copies storedSPfactor+8 to activefactor+4. Doesnot rematch authored override order.
void sub_43C4F0()
{
  int element_address; // esi
  char *v1; // [esp+4h] [ebp-Ch]
  int j; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  for ( i = 0; i < dword_681E14; ++i )
  {
    v1 = &rf_entity_info_definitions[5396 * i];
    for ( j = 0; j < rf_receiver_get_first_dword(v1 + 3308); ++j )
    {
      element_address = rf_inline_array40_get_element_address(v1 + 3308, j);
      *(float *)(rf_inline_array40_get_element_address(v1 + 3308, j) + 4) = *(float *)(element_address + 8);
    }
  }
}

