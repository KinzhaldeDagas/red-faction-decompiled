// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AE160 rf_ui_parse_radio_button_definition
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): ECX unused;two stack args parser,parent gadget,callee pops8. Optional name64;required $Id,$Position screen coordinates converted against parent absolute x/y,$Box size,$Label64. Optional Font(default-1),Label offset(default0,0). Allocates932-byte radio,constructor0x5B11A0,group initializer0x5F60F0(raw flag1). No parent kind/type or allocation validation. Copies name unbounded+30. Repeated Hotkey writes successive unchecked+588+4*i slots;State bitmap filename260 then comma/line64 Unchecked916,Checked920,Pressed924,Disabled928. Optional Tooltip text64,x,y[,font-1] delegates checkbox replacement. Returns radio;no Initially checked directive or explicit event emitted.
_DWORD *__stdcall rf_ui_parse_radio_button_definition(const char **parser, _DWORD *a2)
{
  int v2; // esi
  int v3; // esi
  int v4; // eax
  int v6; // [esp-4h] [ebp-1ECh]
  char v7; // [esp+Bh] [ebp-1DDh]
  _BYTE *v8; // [esp+10h] [ebp-1D8h]
  char *v9; // [esp+14h] [ebp-1D4h]
  _DWORD *v10; // [esp+18h] [ebp-1D0h]
  _DWORD *v11; // [esp+20h] [ebp-1C8h]
  int v12; // [esp+28h] [ebp-1C0h]
  int v13; // [esp+2Ch] [ebp-1BCh]
  char v14[264]; // [esp+34h] [ebp-1B4h] BYREF
  char String1[64]; // [esp+13Ch] [ebp-ACh] BYREF
  int v16; // [esp+17Ch] [ebp-6Ch]
  int v17; // [esp+180h] [ebp-68h]
  char Destination[64]; // [esp+184h] [ebp-64h] BYREF
  int v19; // [esp+1C8h] [ebp-20h]
  int v20; // [esp+1CCh] [ebp-1Ch]
  int v21; // [esp+1D0h] [ebp-18h]
  int v22; // [esp+1D4h] [ebp-14h]
  int signed_decimal_or_hex_integer; // [esp+1D8h] [ebp-10h]
  int v24; // [esp+1E4h] [ebp-4h]

  v13 = 0;
  v16 = 0;
  v17 = -1;
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ":") )
    rf_text_parser_read_delimited_cstring((int)parser, Destination, 64, 34, 34);
  else
    Destination[0] = 0;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Id:");
  signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Position:");
  v2 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  v21 = v2 - rf_ui_gadget_absolute_x(a2, 0);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
  v3 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  v22 = v3 - rf_ui_gadget_absolute_y(a2, 0);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Box size:");
  v12 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
  v19 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Label:");
  rf_text_parser_read_delimited_cstring((int)parser, String1, 64, 34, 34);
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Font:") )
    v17 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Label offset:") )
  {
    v13 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
    v16 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  }
  v11 = operator new(0x3A4u);
  v24 = 0;
  if ( v11 )
    v10 = rf_ui_radio_button_construct(v11);
  else
    v10 = nullptr;
  v24 = -1;
  rf_ui_radio_button_initialize_in_group(
    (int)v10,
    a2,
    v21,
    v22,
    v12,
    v19,
    (unsigned __int8 *)String1,
    v13,
    v16,
    v17,
    signed_decimal_or_hex_integer,
    1);
  v9 = Destination;
  v8 = (char *)v10 + 30;
  do
  {
    v7 = *v9;
    *v8++ = *v9++;
  }
  while ( v7 );
  v20 = 0;
  while ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Hotkey:") )
  {
    v6 = v20;
    v4 = rf_ui_parse_hotkey_name(parser);
    rf_ui_gadget_set_key_slot(v10, v4, v6);
    ++v20;
  }
  while ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+State bitmap:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, v14, 260, 34, 34);
    if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ",") )
    {
      rf_text_parser_skip_trivia_and_cr_lines(parser);
      rf_text_parser_read_cr_line_cstring_if_fits((int)parser, String1, 64);
      if ( !_stricmp(String1, "Unchecked") )
      {
        v10[229] = rf_bitmap_load_with_optional_mipmap_generation(v14, (void *)0xFFFFFFFF, 1);
      }
      else if ( !_stricmp(String1, "Checked") )
      {
        v10[230] = rf_bitmap_load_with_optional_mipmap_generation(v14, (void *)0xFFFFFFFF, 1);
      }
      else if ( !_stricmp(String1, "Pressed") )
      {
        v10[231] = rf_bitmap_load_with_optional_mipmap_generation(v14, (void *)0xFFFFFFFF, 1);
      }
      else if ( !_stricmp(String1, "Disabled") )
      {
        v10[232] = rf_bitmap_load_with_optional_mipmap_generation(v14, (void *)0xFFFFFFFF, 1);
      }
    }
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Tooltip:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, String1, 64, 34, 34);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
    v21 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
    v22 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ",") )
      v17 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    else
      v17 = -1;
    rf_ui_checkbox_replace_tooltip_record(v10, String1, v21, v22, v17);
  }
  return v10;
}

