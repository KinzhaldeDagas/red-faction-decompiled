// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ACE90 rf_ui_window_parse_container_definition
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This owner window;parser,parent arguments. Parent kind1 uses this x/y;kind0 absolute gadget position/type;other kind origin0. Optional name64;required $Id,$Position,$Size. Allocates904-byte container,constructs,initializes with flags0 and final unused argument1;reparents only parent kind0/type1. No allocation guard;unbounded name copy+30. Optional Font writes896;optional $Label quoted64 copies+628. Optional Mask bitmap loads filename260 and then permits repeated Tooltip text64,regionID,x,y[,font default-1] append;these tooltip directives are parsed only inside mask clause. Requires $Inventory start;dispatches nested Button,Checkbox,Container(recursive),Inputbox,Listbox,Radio button,Slider,Static parsers until unrecognized directive;requires $Inventory end. Returns container;no generic
// unknown-token skip or rollback.
char *__thiscall rf_ui_window_parse_container_definition(int *this, const char **parser, _DWORD *a3)
{
  int v3; // eax
  char v4; // dl
  char *v6; // [esp+Ch] [ebp-1E8h]
  char *v7; // [esp+10h] [ebp-1E4h]
  char *v8; // [esp+14h] [ebp-1E0h]
  void *v10; // [esp+20h] [ebp-1D4h]
  char v11[264]; // [esp+28h] [ebp-1CCh] BYREF
  char v12[68]; // [esp+130h] [ebp-C4h] BYREF
  int v13; // [esp+174h] [ebp-80h]
  int v14; // [esp+178h] [ebp-7Ch]
  int type; // [esp+17Ch] [ebp-78h]
  int v16; // [esp+180h] [ebp-74h]
  char *v17; // [esp+184h] [ebp-70h]
  char Destination[64]; // [esp+188h] [ebp-6Ch] BYREF
  int v19; // [esp+1CCh] [ebp-28h]
  int v20; // [esp+1D0h] [ebp-24h]
  int v21; // [esp+1D4h] [ebp-20h]
  int v22; // [esp+1D8h] [ebp-1Ch]
  int kind; // [esp+1DCh] [ebp-18h]
  int v24; // [esp+1E0h] [ebp-14h]
  int signed_decimal_or_hex_integer; // [esp+1E4h] [ebp-10h]
  int v26; // [esp+1F0h] [ebp-4h]

  type = 0;
  v13 = 0;
  v21 = 0;
  signed_decimal_or_hex_integer = -1;
  kind = rf_ui_base_get_kind(a3);
  if ( kind )
  {
    if ( kind == 1 )
    {
      v13 = *(this + 3);
      v21 = *(this + 4);
    }
  }
  else
  {
    type = rf_ui_gadget_get_type(a3);
    v13 = rf_ui_gadget_absolute_x(a3, 0);
    v21 = rf_ui_gadget_absolute_y(a3, 0);
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ":") )
    rf_text_parser_read_delimited_cstring((int)parser, Destination, 64, 34, 34);
  else
    Destination[0] = 0;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Id:");
  signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Position:");
  v19 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser) - v13;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
  v3 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  v20 = v3 - v21;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Size:");
  v24 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
  v22 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  v10 = operator new(0x388u);
  v26 = 0;
  if ( v10 )
    v8 = (char *)rf_ui_container_construct((int)v10);
  else
    v8 = nullptr;
  v26 = -1;
  v17 = v8;
  rf_ui_container_initialize((int)v8, (int)this, v19, v20, v24, v22, signed_decimal_or_hex_integer, 0, 1);
  if ( !kind && type == 1 )
    rf_ui_gadget_set_parent(v17, (int)a3);
  v7 = Destination;
  v6 = v17 + 30;
  do
  {
    v4 = *v7;
    *v6++ = *v7++;
  }
  while ( v4 );
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Font:") )
    *((_DWORD *)v17 + 224) = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "$Label:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, v12, 64, 34, 34);
    rf_ui_container_copy_label_unbounded(v17, v12);
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Mask bitmap:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, v11, 260, 34, 34);
    rf_ui_container_load_mask_bitmap(v11);
    while ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Tooltip:") )
    {
      rf_text_parser_read_delimited_cstring((int)parser, v12, 64, 34, 34);
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
      v16 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
      v19 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
      v20 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
      if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ",") )
        v14 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
      else
        v14 = -1;
      rf_ui_container_append_region_tooltip(v17, v12, v16, v19, v20, v14);
    }
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Inventory start");
  while ( 1 )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        while ( 1 )
        {
          while ( 1 )
          {
            while ( 1 )
            {
              while ( 1 )
              {
                while ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "#Button") )
                  rf_ui_window_parse_button_definition(this, parser, v17);
                if ( !rf_text_parser_try_consume_case_insensitive_prefix(parser, "#Checkbox") )
                  break;
                rf_ui_window_parse_checkbox_definition(this, parser, v17);
              }
              if ( !rf_text_parser_try_consume_case_insensitive_prefix(parser, "#Container") )
                break;
              rf_ui_window_parse_container_definition(this, parser, v17);
            }
            if ( !rf_text_parser_try_consume_case_insensitive_prefix(parser, "#Inputbox") )
              break;
            rf_ui_window_parse_inputbox_definition(this, parser, v17);
          }
          if ( !rf_text_parser_try_consume_case_insensitive_prefix(parser, "#Listbox") )
            break;
          rf_ui_window_parse_text_list_definition(this, parser, (int)v17);
        }
        if ( !rf_text_parser_try_consume_case_insensitive_prefix(parser, "#Radio button") )
          break;
        rf_ui_parse_radio_button_definition(parser, v17);
      }
      if ( !rf_text_parser_try_consume_case_insensitive_prefix(parser, "#Slider") )
        break;
      rf_ui_window_parse_slider_definition(this, parser, (int)v17);
    }
    if ( !rf_text_parser_try_consume_case_insensitive_prefix(parser, "#Static") )
      break;
    rf_ui_window_parse_staticbox_definition(this, parser, v17);
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Inventory end");
  return v17;
}

