// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AC900 rf_ui_window_parse_checkbox_definition
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This owner window;parser,parent arguments. Parent kind1 uses this window x/y;kind0 gadget uses absolute parent x/y and type. Optional quoted name64 after colon;required $Id,$Position,$Box size,$Label64. Optional Initially checked,Font(default-1),Label offset x/y(default0) in fixed order. Allocates932-byte checkbox,constructs and initializes with owner/window,relative position,box size,label,offsets,font,checked,id,raw flag1;reparents only parent kind0/type1. No NULL allocation guard. Copies name unbounded to+30. Repeated Hotkey writes unchecked successive slots588+4*i. Repeated State bitmap takes filename260,optional comma and CR-line label64:case-insensitive Unchecked916,Checked920,Pressed924,Disabled928;unrecognized ignored. Optional Tooltip text64,x,y[,font default-1] calls0x5F2310.
// Returns checkbox;does not validate bitmap load or parser helper success.
_DWORD *__thiscall rf_ui_window_parse_checkbox_definition(int *this, const char **parser, _DWORD *a3)
{
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v10; // [esp-4h] [ebp-208h]
  char v11; // [esp+7h] [ebp-1FDh]
  char *v12; // [esp+Ch] [ebp-1F8h]
  char *v13; // [esp+10h] [ebp-1F4h]
  _DWORD *v14; // [esp+14h] [ebp-1F0h]
  void *v16; // [esp+20h] [ebp-1E4h]
  int v17; // [esp+28h] [ebp-1DCh]
  int v18; // [esp+2Ch] [ebp-1D8h]
  char v19[264]; // [esp+30h] [ebp-1D4h] BYREF
  char String1[68]; // [esp+138h] [ebp-CCh] BYREF
  int v21; // [esp+17Ch] [ebp-88h]
  int v22; // [esp+180h] [ebp-84h]
  int v23; // [esp+184h] [ebp-80h]
  _DWORD *v24; // [esp+188h] [ebp-7Ch]
  int type; // [esp+18Ch] [ebp-78h]
  char Destination[68]; // [esp+190h] [ebp-74h] BYREF
  char v27; // [esp+1DBh] [ebp-29h]
  int v28; // [esp+1DCh] [ebp-28h]
  int v29; // [esp+1E0h] [ebp-24h]
  int v30; // [esp+1E4h] [ebp-20h]
  int v31; // [esp+1E8h] [ebp-1Ch]
  int v32; // [esp+1ECh] [ebp-18h]
  int kind; // [esp+1F0h] [ebp-14h]
  int signed_decimal_or_hex_integer; // [esp+1F4h] [ebp-10h]
  int v35; // [esp+200h] [ebp-4h]

  type = 0;
  v21 = 0;
  v32 = 0;
  v18 = 0;
  v22 = 0;
  signed_decimal_or_hex_integer = -1;
  v23 = -1;
  v27 = 0;
  kind = rf_ui_base_get_kind(a3);
  if ( kind )
  {
    if ( kind == 1 )
    {
      v21 = *(this + 3);
      v32 = *(this + 4);
    }
  }
  else
  {
    type = rf_ui_gadget_get_type(a3);
    v21 = rf_ui_gadget_absolute_x(a3, 0);
    v32 = rf_ui_gadget_absolute_y(a3, 0);
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ":") )
    rf_text_parser_read_delimited_cstring((int)parser, Destination, 64, 34, 34);
  else
    Destination[0] = 0;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Id:");
  signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Position:");
  v30 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser) - v21;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
  v3 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  v31 = v3 - v32;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Box size:");
  v17 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
  v28 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Label:");
  rf_text_parser_read_delimited_cstring((int)parser, String1, 64, 34, 34);
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Initially checked") )
    v27 = 1;
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Font:") )
    v23 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Label offset:") )
  {
    v18 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
    v22 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  }
  v16 = operator new(0x3A4u);
  v35 = 0;
  if ( v16 )
    v14 = (_DWORD *)rf_ui_checkbox_construct((int)v16);
  else
    v14 = nullptr;
  v35 = -1;
  v24 = v14;
  rf_ui_checkbox_initialize(
    (int)v14,
    (int)this,
    v30,
    v31,
    v17,
    v28,
    (unsigned __int8 *)String1,
    v18,
    v22,
    v23,
    v27,
    signed_decimal_or_hex_integer,
    1);
  if ( !kind && type == 1 )
    rf_ui_gadget_set_parent(v24, (int)a3);
  v13 = Destination;
  v12 = (char *)v24 + 30;
  do
  {
    v11 = *v13;
    *v12++ = *v13++;
  }
  while ( v11 );
  v29 = 0;
  while ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Hotkey:") )
  {
    v10 = v29;
    v4 = rf_ui_parse_hotkey_name(parser);
    rf_ui_gadget_set_key_slot(v24, v4, v10);
    ++v29;
  }
  while ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+State bitmap:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, v19, 260, 34, 34);
    if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ",") )
    {
      rf_text_parser_skip_trivia_and_cr_lines(parser);
      rf_text_parser_read_cr_line_cstring_if_fits((int)parser, String1, 64);
      if ( !_stricmp(String1, "Unchecked") )
      {
        v5 = rf_bitmap_load_with_optional_mipmap_generation(v19, (void *)0xFFFFFFFF, 1);
        v24[229] = v5;
      }
      else if ( !_stricmp(String1, "Checked") )
      {
        v6 = rf_bitmap_load_with_optional_mipmap_generation(v19, (void *)0xFFFFFFFF, 1);
        v24[230] = v6;
      }
      else if ( !_stricmp(String1, "Pressed") )
      {
        v7 = rf_bitmap_load_with_optional_mipmap_generation(v19, (void *)0xFFFFFFFF, 1);
        v24[231] = v7;
      }
      else if ( !_stricmp(String1, "Disabled") )
      {
        v8 = rf_bitmap_load_with_optional_mipmap_generation(v19, (void *)0xFFFFFFFF, 1);
        v24[232] = v8;
      }
    }
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Tooltip:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, String1, 64, 34, 34);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
    v30 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
    v31 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ",") )
      v23 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    else
      v23 = -1;
    rf_ui_checkbox_replace_tooltip_record(v24, String1, v30, v31, v23);
  }
  return v24;
}

