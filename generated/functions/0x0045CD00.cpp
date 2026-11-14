// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045CD00 rf_multiplayer_setup_rebuild_filtered_level_list
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Noarg. Clear/destroy filtered pair-array6F2DC4,release selected rotation-index array6F2E64,store
// scroll6F2D04=0,current row6F2D08=0,set slider6F3740 tofloat0. Then traverse master pair-array6F2E14 in order;record+8 extensionless filename passes case-insensitive game-mode
// prefix predicate45B4D0(currentMode6F35C4). Matching record copied as16-byte owned pair to stack and appended45DD80,which consumes/destroys the by-value copy. No
// sort,selected-rotation retention,auto-select-first or title reread. Prefix predicate has no index bound;this caller does not add one. Empty results still current row0;returns final
// master count residue,not filtered count.
int rf_multiplayer_setup_rebuild_filtered_level_list()
{
  int result; // eax
  int v1; // eax
  char *v2; // eax
  char **v3; // eax
  char v4; // [esp-Ch] [ebp-1Ch] BYREF
  int v5; // [esp-8h] [ebp-18h]
  int v6; // [esp-4h] [ebp-14h]
  int v7; // [esp+0h] [ebp-10h]
  _lambda_8b695f9820225e821433c25f6ed27cb8_ *v8; // [esp+4h] [ebp-Ch]
  char *v9; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  rf_two_rfstring_array16_clear_and_release(dword_6F2DC4);
  rf_pointer_array_release_storage((void **)unk_6F2E64);
  dword_6F2D04 = 0;
  unk_6F2D08 = 0;
  rf_ui_slider_set_value_clamped(flt_6F3740, 0.0);
  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(dword_6F2E14);
    if ( i >= result )
      break;
    v7 = unk_6F35C4;
    v1 = rf_two_rfstring_array16_element_address_unchecked(dword_6F2E14, i);
    v2 = (char *)rf_string_object_c_str_or_empty((const void *)(v1 + 8));
    if ( rf_level_name_matches_game_mode_prefix(v2, v7) )
    {
      v3 = (char **)rf_two_rfstring_array16_element_address_unchecked(dword_6F2E14, i);
      v9 = &v4;
      v8 = rf_two_rfstring_copy_construct((_lambda_8b695f9820225e821433c25f6ed27cb8_ *)&v4, v3);
      rf_two_rfstring_array16_append_owned(dword_6F2DC4, v4, v5, v6, v7);
    }
  }
  return result;
}

