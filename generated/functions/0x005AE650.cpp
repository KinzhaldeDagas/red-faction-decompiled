// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AE650 rf_ui_window_parse_slider_definition
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This owner window;parser,parent. Optional name64;required $Id,$Position,$Size,$Horizontal or required $Vertical,$Marker size. Optional Scrollbar chooses derived allocation684bytes vs plain slider680. Dot slider OR4,No process OR8,Positions(default1),Marker bitmap name64,Marker position(default0). Saves parser cursor/line,scans ahead to +Left button(horizontal)/+Up button(vertical) before #;if found OR1,then restores parser state. Parent kind1 or kind0/type1 initializes slider type7;type1 then reparents. Parent kind0/type8 calls attached-text-list scrollbar initializer using derived pointer (NULL when +Scrollbar absent);other parent kinds/types leave constructed object uninitialized. No allocation guard. Base initializer uses flags only bit1 to generate arrows;bits4/8 are not persisted here.
// Unbounded name copy+30. Background bitmap reads one/two filenames260 but NEVER loads/applies them;Marker bitmap filename similarly never applied (only strlen). Optional Tooltip calls0x5EE8B0. When flag1,parses two explicit Button definitions Left/Right or Up/Down and overwrites automatically created arrow pointers676/672 WITHOUT destroying originals. Finally raw setter652=markerPosition,no clamp. Positions1 default permits zero denominator in thumb geometry until changed.
_DWORD *__thiscall rf_ui_window_parse_slider_definition(int *this, const char **parser, _DWORD *a3)
{
  int v3; // eax
  char *v4; // eax
  char *v5; // eax
  char *v6; // eax
  char v8; // [esp+17h] [ebp-36Dh]
  char *v9; // [esp+1Ch] [ebp-368h]
  char *v10; // [esp+20h] [ebp-364h]
  _DWORD *v11; // [esp+24h] [ebp-360h]
  _DWORD *v12; // [esp+28h] [ebp-35Ch]
  _DWORD *v14; // [esp+34h] [ebp-350h]
  _DWORD *v15; // [esp+3Ch] [ebp-348h]
  _DWORD v16[2]; // [esp+48h] [ebp-33Ch] BYREF
  char v17[264]; // [esp+50h] [ebp-334h] BYREF
  char v18[64]; // [esp+158h] [ebp-22Ch] BYREF
  int v19; // [esp+198h] [ebp-1ECh]
  int v20; // [esp+19Ch] [ebp-1E8h]
  char v21[71]; // [esp+1A0h] [ebp-1E4h] BYREF
  bool v22; // [esp+1E7h] [ebp-19Dh]
  int v23; // [esp+1E8h] [ebp-19Ch]
  int type; // [esp+1ECh] [ebp-198h]
  char v25[268]; // [esp+1F0h] [ebp-194h] BYREF
  _DWORD *v26; // [esp+2FCh] [ebp-88h]
  char Destination[68]; // [esp+300h] [ebp-84h] BYREF
  _DWORD *v28; // [esp+348h] [ebp-3Ch]
  char v29; // [esp+34Fh] [ebp-35h]
  int v30; // [esp+350h] [ebp-34h]
  int v31; // [esp+354h] [ebp-30h]
  int v32; // [esp+358h] [ebp-2Ch]
  int v33; // [esp+35Ch] [ebp-28h]
  int v34; // [esp+360h] [ebp-24h]
  int v35; // [esp+364h] [ebp-20h]
  int v36; // [esp+368h] [ebp-1Ch]
  int v37; // [esp+36Ch] [ebp-18h]
  int signed_decimal_or_hex_integer; // [esp+370h] [ebp-14h]
  int kind; // [esp+374h] [ebp-10h]
  int v40; // [esp+380h] [ebp-4h]

  v19 = 0;
  v35 = 0;
  v23 = 0;
  v33 = 1;
  signed_decimal_or_hex_integer = -1;
  v34 = 0;
  memset(v21, 0, 64);
  type = 0;
  kind = rf_ui_base_get_kind(a3);
  if ( kind )
  {
    if ( kind == 1 )
    {
      v19 = *(this + 3);
      v35 = *(this + 4);
    }
  }
  else
  {
    type = rf_ui_gadget_get_type(a3);
    v19 = rf_ui_gadget_absolute_x(a3, 0);
    v35 = rf_ui_gadget_absolute_y(a3, 0);
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ":") )
    rf_text_parser_read_delimited_cstring((int)parser, Destination, 64, 34, 34);
  else
    Destination[0] = 0;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Id:");
  signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Position:");
  v30 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser) - v19;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
  v3 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  v31 = v3 - v35;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Size:");
  v37 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
  v36 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "$Horizontal") )
  {
    v29 = 1;
  }
  else
  {
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Vertical");
    v29 = 0;
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Marker size:");
  v32 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  v22 = rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Scrollbar");
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Dot slider") )
    v34 |= 4u;
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+No process") )
    v34 |= 8u;
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Positions:") )
    v33 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Marker bitmap:") )
    rf_text_parser_read_delimited_cstring((int)parser, v21, 64, 34, 34);
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Marker position:") )
    v23 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  rf_text_parser_save_cursor_bookmark(parser, v16);
  if ( v29 )
  {
    if ( rf_text_parser_find_substring_before_optional_stop((char **)parser, "+Left button", "#") )
      v34 |= 1u;
  }
  else if ( rf_text_parser_find_substring_before_optional_stop((char **)parser, "+Up button", "#") )
  {
    v34 |= 1u;
  }
  rf_text_parser_restore_cursor_bookmark(parser, v16);
  if ( v22 )
  {
    v15 = operator new(0x2ACu);
    v40 = 0;
    if ( v15 )
      v12 = rf_ui_scrollbar_construct(v15);
    else
      v12 = nullptr;
    v40 = -1;
    v28 = v12;
    v26 = v12;
  }
  else
  {
    v28 = nullptr;
    v14 = operator new(0x2A8u);
    v40 = 1;
    if ( v14 )
      v11 = rf_ui_slider_construct(v14);
    else
      v11 = nullptr;
    v40 = -1;
    v26 = v11;
  }
  if ( kind )
  {
    if ( kind == 1 )
      rf_ui_slider_initialize(
        (int)v26,
        (int)this,
        v30,
        v31,
        v37,
        v36,
        v29,
        v32,
        v33,
        signed_decimal_or_hex_integer,
        v34,
        1);
  }
  else if ( type == 1 )
  {
    rf_ui_slider_initialize(
      (int)v26,
      (int)this,
      v30,
      v31,
      v37,
      v36,
      v29,
      v32,
      v33,
      signed_decimal_or_hex_integer,
      v34,
      1);
    rf_ui_gadget_set_parent(v26, (int)a3);
  }
  else if ( type == 8 )
  {
    rf_text_list_initialize_attached_scrollbar(v28, (int)a3, v29, v32, signed_decimal_or_hex_integer, v34, 1);
  }
  v10 = Destination;
  v9 = (char *)v26 + 30;
  do
  {
    v8 = *v10;
    *v9++ = *v10++;
  }
  while ( v8 );
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Background bitmap:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, v17, 260, 34, 34);
    if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ",") )
      rf_text_parser_read_delimited_cstring((int)parser, v25, 260, 34, 34);
  }
  strlen(v21);
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Tooltip:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, v18, 64, 34, 34);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
    v30 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
    v31 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ",") )
      v20 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    else
      v20 = -1;
    rf_ui_slider_replace_tooltip_record(v26, v18, v30, v31, v20);
  }
  if ( (v34 & 1) != 0 )
  {
    if ( v29 )
    {
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+Left button");
      v4 = rf_ui_window_parse_button_definition(this, parser, v26);
      v26[169] = v4;
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+Right button");
    }
    else
    {
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+Up button");
      v6 = rf_ui_window_parse_button_definition(this, parser, v26);
      v26[169] = v6;
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+Down button");
    }
    v5 = rf_ui_window_parse_button_definition(this, parser, v26);
    v26[168] = v5;
  }
  rf_scrollbar_set_position_unclamped(v26, v23);
  return v26;
}

