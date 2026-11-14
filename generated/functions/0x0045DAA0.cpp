// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045DAA0 rf_multiplayer_menu_copy_level_rotation
// UNREALRED VERIFIED [local-multiplayer-20261028] Returns false unless both selected rotation and available level catalog are nonempty. Clears the destination rotation, visits selected catalog indices in order, appends .rfl to each selected logical basename and copies each result. This is a pre-start validation boundary; an empty selection does not initialize a multiplayer session.
char __cdecl rf_multiplayer_menu_copy_level_rotation(_DWORD *a1)
{
  int first_dword; // eax
  int *v3; // eax
  int v4; // eax
  int v5; // eax
  _DWORD v6[4]; // [esp-8h] [ebp-30h] BYREF
  char v7; // [esp+Bh] [ebp-1Dh]
  _DWORD *v8; // [esp+Ch] [ebp-1Ch]
  int i; // [esp+10h] [ebp-18h]
  char *v10[2]; // [esp+14h] [ebp-14h] BYREF
  int v11; // [esp+24h] [ebp-4h]

  if ( rf_receiver_get_first_dword(unk_6F2E64) <= 0 )
    return 0;
  if ( rf_receiver_get_first_dword(dword_6F2DC4) <= 0 )
    return 0;
  rf_rfstring_array8_clear_and_release(a1);
  rf_string_construct_empty(v10);
  v11 = 0;
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword(unk_6F2E64);
    if ( i >= first_dword )
      break;
    v3 = (int *)sub_552200(unk_6F2E64, i);
    v4 = rf_two_rfstring_array16_element_address_unchecked(dword_6F2DC4, *v3);
    rf_string_assign_from_object(v10, v4 + 8);
    rf_string_append_cstr_in_place(v10, (int)".rfl");
    v8 = v6;
    rf_string_copy_construct_from_object(v6, v10);
    v6[3] = v5;
    rf_rfstring_array8_append_owned(a1, v6[0], v6[1]);
  }
  v7 = 1;
  v11 = -1;
  rf_string_destroy_buffer(v10);
  return v7;
}

