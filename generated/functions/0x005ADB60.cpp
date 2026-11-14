// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ADB60 rf_ui_window_parse_text_list_definition
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This owner window;parser,parent args. Parent kind1 uses this x/y;kind0 gadget uses absolute x/y,type. Optional quoted name64;required $Id,$Position,$Size,$Content size first integer plus optional second default0. Fixed optional flags:Allow wrap1,Sort entries0x40,No select8,Scroll by entry0x10,Scroll by pixels0x20,Align view with bottom0x80,No background0x100,Mouseover highlights0x200,Preallocated text0x400. Mutually exclusive automatic scrollbar clauses:horizontal OR4,vertical OR2,BOTH ALSO ONLY OR2 at0x5ADE79 (not6). Allocates800-byte text list,constructs/initializes with parsed content dimensions and flags,raw flag1;reparent only kind0/type1;unchecked allocation,unbounded name copy30. Optional Entry spacing716,Margin700,Vertical margin704,Background bitmap696,Tooltip text64/x/y/font
// via0x5A6BF0. Then optional Horizontal scrollbar and Vertical scrollbar each call slider parser with list parent. Does not populate entries or reflow after direct margin/spacing assignments;returns list.
int *__thiscall rf_ui_window_parse_text_list_definition(int *this, const char **parser, _DWORD *a3)
{
  int v3; // eax
  int v4; // eax
  char v6; // [esp+7h] [ebp-1F5h]
  char *v7; // [esp+Ch] [ebp-1F0h]
  char *v8; // [esp+10h] [ebp-1ECh]
  int *v9; // [esp+14h] [ebp-1E8h]
  int *v11; // [esp+20h] [ebp-1DCh]
  char v12[264]; // [esp+28h] [ebp-1D4h] BYREF
  char v13[68]; // [esp+130h] [ebp-CCh] BYREF
  int v14; // [esp+174h] [ebp-88h]
  int v15; // [esp+178h] [ebp-84h]
  int type; // [esp+17Ch] [ebp-80h]
  int *v17; // [esp+180h] [ebp-7Ch]
  int v18; // [esp+184h] [ebp-78h]
  char Destination[64]; // [esp+188h] [ebp-74h] BYREF
  int v20; // [esp+1CCh] [ebp-30h]
  int v21; // [esp+1D0h] [ebp-2Ch]
  int v22; // [esp+1D4h] [ebp-28h]
  int v23; // [esp+1D8h] [ebp-24h]
  int v24; // [esp+1DCh] [ebp-20h]
  int v25; // [esp+1E0h] [ebp-1Ch]
  int kind; // [esp+1E4h] [ebp-18h]
  int v27; // [esp+1E8h] [ebp-14h]
  int signed_decimal_or_hex_integer; // [esp+1ECh] [ebp-10h]
  int v29; // [esp+1F8h] [ebp-4h]

  type = 0;
  v14 = 0;
  v24 = 0;
  v18 = 0;
  signed_decimal_or_hex_integer = -1;
  v23 = 0;
  kind = rf_ui_base_get_kind(a3);
  if ( kind )
  {
    if ( kind == 1 )
    {
      v14 = *(this + 3);
      v24 = *(this + 4);
    }
  }
  else
  {
    type = rf_ui_gadget_get_type(a3);
    v14 = rf_ui_gadget_absolute_x(a3, 0);
    v24 = rf_ui_gadget_absolute_y(a3, 0);
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ":") )
    rf_text_parser_read_delimited_cstring((int)parser, Destination, 64, 34, 34);
  else
    Destination[0] = 0;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Id:");
  signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Position:");
  v21 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser) - v14;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
  v3 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  v22 = v3 - v24;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Size:");
  v27 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
  v25 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Content size:");
  v20 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ",") )
    v18 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Allow wrap") )
    v23 |= 1u;
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Sort entries") )
    v23 |= 0x40u;
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+No select") )
    v23 |= 8u;
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Scroll by entry") )
    v23 |= 0x10u;
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Scroll by pixels") )
    v23 |= 0x20u;
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Align view with bottom") )
    v23 |= 0x80u;
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+No background") )
    v23 |= 0x100u;
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Mouseover highlights") )
    v23 |= 0x200u;
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Preallocated text") )
    v23 |= 0x400u;
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Add horizontal scrollbar") )
  {
    v23 |= 4u;
  }
  else if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Add vertical scrollbar") )
  {
    v23 |= 2u;
  }
  else if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Add both scrollbars") )
  {
    v23 |= 2u;
  }
  v11 = (int *)operator new(0x320u);
  v29 = 0;
  if ( v11 )
    v9 = rf_text_list_construct(v11);
  else
    v9 = nullptr;
  v29 = -1;
  v17 = v9;
  rf_text_list_initialize((int)v9, (int)this, v21, v22, v27, v25, v20, v18, signed_decimal_or_hex_integer, v23, 1);
  if ( !kind && type == 1 )
    rf_ui_gadget_set_parent(v17, (int)a3);
  v8 = Destination;
  v7 = (char *)v17 + 30;
  do
  {
    v6 = *v8;
    *v7++ = *v8++;
  }
  while ( v6 );
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Entry spacing:") )
    v17[179] = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Margin:") )
    v17[175] = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Vertical margin:") )
    v17[176] = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Background bitmap:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, v12, 260, 34, 34);
    v4 = rf_bitmap_load_with_optional_mipmap_generation(v12, (void *)0xFFFFFFFF, 1);
    v17[174] = v4;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Tooltip:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, v13, 64, 34, 34);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
    v21 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
    v22 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ",") )
      v15 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    else
      v15 = -1;
    rf_text_list_replace_tooltip_record(v17, v13, v21, v22, v15);
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Horizontal scrollbar") )
    rf_ui_window_parse_slider_definition(this, parser, (int)v17);
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Vertical scrollbar") )
    rf_ui_window_parse_slider_definition(this, parser, (int)v17);
  return v17;
}

