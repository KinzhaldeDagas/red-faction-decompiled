// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00472AC0 rf_item_definition_parse
// UNREALRED VERIFIED [combat-native-pickups-20261111]: Record stride80 base6F9130. Ordered required ClassName RFString254max, HUDMsg XSTR buffer256(max255), optional4 pickup-message XSTRs in order, required V3DFilename RFString and V3DType RFString->4BC1A0, required signed Count579890 at+30, optional signed CountMulti+34 else exactSPcopy, required signed RespawnTime with wrapping32 multiply1000 at+38. Optional direct PickupSound446750 defaults-1. AmmoFor+3C and GivesWeapon+40 each initialize-1; PRESENT authored empty string still unconditionally calls50FB80, absent token does not. Required Flags two native table entries662540(no_pickup,spins_in_multi). No native nonnegative count clamp or alias/trim/name-dedup. Callback+48 is assigned by later startup registration, not this parser.
void __cdecl rf_item_definition_parse(_DWORD *parser)
{
  int v1; // eax
  int signed_decimal_or_hex_integer; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  char *v6; // eax
  char *v7; // eax
  int parenthesized_named_flag_mask; // eax
  int v9; // [esp+4h] [ebp-150h]
  int v10; // [esp+8h] [ebp-14Ch]
  int v11; // [esp+Ch] [ebp-148h]
  int v12; // [esp+10h] [ebp-144h]
  int string_pointer_slot; // [esp+14h] [ebp-140h]
  int v14; // [esp+18h] [ebp-13Ch]
  _DWORD v15[2]; // [esp+1Ch] [ebp-138h] BYREF
  int v16; // [esp+24h] [ebp-130h]
  _DWORD v17[2]; // [esp+28h] [ebp-12Ch] BYREF
  _DWORD v18[2]; // [esp+30h] [ebp-124h] BYREF
  char Destination[260]; // [esp+38h] [ebp-11Ch] BYREF
  void *destination; // [esp+140h] [ebp-14h]
  int xstr_id_and_delimited_text; // [esp+144h] [ebp-10h]
  int v22; // [esp+150h] [ebp-4h]

  rf_string_construct_empty(v18);
  v22 = 0;
  destination = (char *)&unk_6F9130 + 80 * unk_6F9124;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Class Name:");
  rf_text_parser_read_delimited_rfstring(parser, destination, 34, 34);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$HUD Msg Name:");
  xstr_id_and_delimited_text = rf_text_parser_read_xstr_id_and_delimited_text(parser, Destination, 256, 34, 34);
  if ( xstr_id_and_delimited_text >= 0 )
    string_pointer_slot = 4 * xstr_id_and_delimited_text + 8967224;
  else
    string_pointer_slot = rf_localization_get_string_pointer_slot((int)Destination, xstr_id_and_delimited_text);
  *((_DWORD *)destination + 4) = string_pointer_slot;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Pickup Msg Single:") )
  {
    xstr_id_and_delimited_text = rf_text_parser_read_xstr_id_and_delimited_text(parser, Destination, 256, 34, 34);
    if ( xstr_id_and_delimited_text >= 0 )
      v12 = 4 * xstr_id_and_delimited_text + 8967224;
    else
      v12 = rf_localization_get_string_pointer_slot((int)Destination, xstr_id_and_delimited_text);
    *((_DWORD *)destination + 5) = v12;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Pickup Msg Multi:") )
  {
    xstr_id_and_delimited_text = rf_text_parser_read_xstr_id_and_delimited_text(parser, Destination, 256, 34, 34);
    if ( xstr_id_and_delimited_text >= 0 )
      v11 = 4 * xstr_id_and_delimited_text + 8967224;
    else
      v11 = rf_localization_get_string_pointer_slot((int)Destination, xstr_id_and_delimited_text);
    *((_DWORD *)destination + 6) = v11;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Pickup Msg W&A Single:") )
  {
    xstr_id_and_delimited_text = rf_text_parser_read_xstr_id_and_delimited_text(parser, Destination, 256, 34, 34);
    if ( xstr_id_and_delimited_text >= 0 )
      v10 = 4 * xstr_id_and_delimited_text + 8967224;
    else
      v10 = rf_localization_get_string_pointer_slot((int)Destination, xstr_id_and_delimited_text);
    *((_DWORD *)destination + 7) = v10;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Pickup Msg W&A Multi:") )
  {
    xstr_id_and_delimited_text = rf_text_parser_read_xstr_id_and_delimited_text(parser, Destination, 256, 34, 34);
    if ( xstr_id_and_delimited_text >= 0 )
      v9 = 4 * xstr_id_and_delimited_text + 8967224;
    else
      v9 = rf_localization_get_string_pointer_slot((int)Destination, xstr_id_and_delimited_text);
    *((_DWORD *)destination + 8) = v9;
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$V3D Filename:");
  rf_text_parser_read_delimited_rfstring(parser, (char *)destination + 8, 34, 34);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$V3D Type:");
  rf_text_parser_read_delimited_rfstring(parser, v18, 34, 34);
  v1 = sub_4BC1A0((int)v18);
  *((_DWORD *)destination + 9) = v1;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Count:");
  signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
  *((_DWORD *)destination + 12) = signed_decimal_or_hex_integer;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Count Multi:") )
  {
    v3 = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
    *((_DWORD *)destination + 13) = v3;
  }
  else
  {
    *((_DWORD *)destination + 13) = *((_DWORD *)destination + 12);
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Respawn Time:");
  v4 = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
  *((_DWORD *)destination + 14) = v4;
  *((_DWORD *)destination + 14) *= 1000;
  *((_DWORD *)destination + 10) = -1;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Pickup Sound:") )
  {
    v5 = rf_gamesound_parse_direct_sound(parser);
    *((_DWORD *)destination + 10) = v5;
  }
  *((_DWORD *)destination + 15) = -1;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Ammo For:") )
  {
    rf_string_construct_empty(v17);
    LOBYTE(v22) = 1;
    rf_text_parser_read_delimited_rfstring(parser, v17, 34, 34);
    v6 = (char *)rf_string_object_c_str_or_empty(v17);
    v16 = sub_50FB80(v6);
    *((_DWORD *)destination + 15) = v16;
    LOBYTE(v22) = 0;
    rf_string_destroy_buffer(v17);
  }
  *((_DWORD *)destination + 16) = -1;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Gives Weapon:") )
  {
    rf_string_construct_empty(v15);
    LOBYTE(v22) = 2;
    rf_text_parser_read_delimited_rfstring(parser, v15, 34, 34);
    v7 = (char *)rf_string_object_c_str_or_empty(v15);
    v14 = sub_50FB80(v7);
    *((_DWORD *)destination + 16) = v14;
    LOBYTE(v22) = 0;
    rf_string_destroy_buffer(v15);
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Flags:");
  parenthesized_named_flag_mask = rf_text_parser_read_parenthesized_named_flag_mask(
                                    (_BYTE **)parser,
                                    (int)off_662540,
                                    2);
  *((_DWORD *)destination + 17) = parenthesized_named_flag_mask;
  v22 = -1;
  rf_string_destroy_buffer(v18);
}

