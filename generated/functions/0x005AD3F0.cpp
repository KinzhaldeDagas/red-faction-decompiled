// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AD3F0 rf_ui_window_parse_inputbox_definition
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This owner window;parser,parent arguments. Parent kind1 uses window x/y;kind0 gadget absolute coordinates/type. Optional name64 then required $Id,$Position,$Size. Fixed optional flags Ignore esc2,No scroll4,Password1 with optional quoted mask-character:firstBYTE(default42). Allocates1460-byte inputbox,constructs,initializes;reparent only kind0/type1. No allocation failure guard;unbounded name copy+30. Optional Valid chars/Invalid chars parsed64 and range helpers called,return ignored;Max text length stored raw1408 with NO cap to256-byte buffer. State bitmap filename260 plus line label64 Normal1448/Disabled1452. Optional Margin1420,Text64 via setter,Font1400,Text y offset1424,Vertical justification Top0/Center1/Bottom2. Optional cursor bitmap1444,anim loader1440,size1432/1436,y
// offset1428;Tooltip64,x,y[,font] via defective replacement helper. Order fixed;quoted/line/load failures not checked. Returns inputbox.
int *__thiscall rf_ui_window_parse_inputbox_definition(int *this, const char **parser, _DWORD *a3)
{
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  char v15; // [esp+7h] [ebp-1EDh]
  char *v16; // [esp+Ch] [ebp-1E8h]
  char *v17; // [esp+10h] [ebp-1E4h]
  int *v18; // [esp+14h] [ebp-1E0h]
  void *v20; // [esp+20h] [ebp-1D4h]
  char v21[264]; // [esp+28h] [ebp-1CCh] BYREF
  char String1[64]; // [esp+130h] [ebp-C4h] BYREF
  int v23; // [esp+170h] [ebp-84h]
  int v24; // [esp+174h] [ebp-80h]
  int type; // [esp+178h] [ebp-7Ch]
  char v26; // [esp+17Fh] [ebp-75h]
  char Destination[64]; // [esp+180h] [ebp-74h] BYREF
  int *v28; // [esp+1C4h] [ebp-30h]
  int v29; // [esp+1C8h] [ebp-2Ch]
  int v30; // [esp+1CCh] [ebp-28h]
  int v31; // [esp+1D0h] [ebp-24h]
  int v32; // [esp+1D4h] [ebp-20h]
  int v33; // [esp+1D8h] [ebp-1Ch]
  int kind; // [esp+1DCh] [ebp-18h]
  int v35; // [esp+1E0h] [ebp-14h]
  int signed_decimal_or_hex_integer; // [esp+1E4h] [ebp-10h]
  int v37; // [esp+1F0h] [ebp-4h]

  type = 0;
  v23 = 0;
  v32 = 0;
  signed_decimal_or_hex_integer = -1;
  v31 = 0;
  v26 = 42;
  kind = rf_ui_base_get_kind(a3);
  if ( kind )
  {
    if ( kind == 1 )
    {
      v23 = *(this + 3);
      v32 = *(this + 4);
    }
  }
  else
  {
    type = rf_ui_gadget_get_type(a3);
    v23 = rf_ui_gadget_absolute_x(a3, 0);
    v32 = rf_ui_gadget_absolute_y(a3, 0);
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ":") )
    rf_text_parser_read_delimited_cstring((int)parser, Destination, 64, 34, 34);
  else
    Destination[0] = 0;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Id:");
  signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Position:");
  v29 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser) - v23;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
  v3 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  v30 = v3 - v32;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Size:");
  v35 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
  v33 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Ignore esc") )
    v31 |= 2u;
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+No scroll") )
    v31 |= 4u;
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Password") )
  {
    v31 |= 1u;
    if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ":") )
    {
      rf_text_parser_read_delimited_cstring((int)parser, String1, 64, 34, 34);
      v26 = String1[0];
    }
  }
  v20 = operator new(0x5B4u);
  v37 = 0;
  if ( v20 )
    v18 = (int *)rf_ui_inputbox_construct((int)v20);
  else
    v18 = nullptr;
  v37 = -1;
  v28 = v18;
  rf_ui_inputbox_initialize((int)v18, (int)this, v29, v30, v35, v33, signed_decimal_or_hex_integer, v31, 1);
  if ( !kind && type == 1 )
    rf_ui_gadget_set_parent(v28, (int)a3);
  v17 = Destination;
  v16 = (char *)v28 + 30;
  do
  {
    v15 = *v17;
    *v16++ = *v17++;
  }
  while ( v15 );
  *((_BYTE *)v28 + 1412) = v26;
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Valid chars:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, String1, 64, 34, 34);
    rf_ui_inputbox_parse_allowed_character_ranges(v28, String1);
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Invalid chars:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, String1, 64, 34, 34);
    rf_ui_inputbox_parse_rejected_character_ranges(v28, String1);
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Max text length:") )
  {
    v4 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    v28[352] = v4;
  }
  while ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+State bitmap:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, v21, 260, 34, 34);
    if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ",") )
    {
      rf_text_parser_skip_trivia_and_cr_lines(parser);
      rf_text_parser_read_cr_line_cstring_if_fits((int)parser, String1, 64);
      if ( !_stricmp(String1, "Normal") )
      {
        v5 = rf_bitmap_load_with_optional_mipmap_generation(v21, (void *)0xFFFFFFFF, 1);
        v28[362] = v5;
      }
      else if ( !_stricmp(String1, "Disabled") )
      {
        v6 = rf_bitmap_load_with_optional_mipmap_generation(v21, (void *)0xFFFFFFFF, 1);
        v28[363] = v6;
      }
    }
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Margin:") )
  {
    v7 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    v28[355] = v7;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Text:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, String1, 64, 34, 34);
    rf_ui_inputbox_set_text_if_within_configured_limit((int)v28, String1);
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Font:") )
  {
    v8 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    v28[350] = v8;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Text y offset:") )
  {
    v9 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    v28[356] = v9;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Vertical justification:") )
  {
    rf_text_parser_skip_trivia_and_cr_lines(parser);
    rf_text_parser_read_cr_line_cstring_if_fits((int)parser, String1, 64);
    if ( !_stricmp(String1, off_6434C4) )
    {
      v28[354] = 0;
    }
    else if ( !_stricmp(String1, "Center") )
    {
      v28[354] = 1;
    }
    else if ( !_stricmp(String1, "Bottom") )
    {
      v28[354] = 2;
    }
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Cursor bitmap:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, v21, 260, 34, 34);
    v10 = rf_bitmap_load_with_optional_mipmap_generation(v21, (void *)0xFFFFFFFF, 1);
    v28[361] = v10;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Cursor anim:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, v21, 260, 34, 34);
    rf_ui_inputbox_load_cursor_animation(v28, v21);
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Cursor size:") )
  {
    v11 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    v28[358] = v11;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
    v12 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    v28[359] = v12;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Cursor y offset:") )
  {
    v13 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    v28[357] = v13;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Tooltip:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, String1, 64, 34, 34);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
    v29 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
    v30 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ",") )
      v24 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    else
      v24 = -1;
    rf_ui_inputbox_replace_tooltip_record(v28, String1, v29, v30, v24);
  }
  return v28;
}

