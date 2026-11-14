// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AEDE0 rf_ui_window_parse_staticbox_definition
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This owner window;parser,parent args. Optional name64;required $Id,$Position,$Size;parent kind1 uses this x/y,kind0 uses absolute gadget coordinates. Allocates988-byte staticbox,constructs/initializes type3(raw1);reparents only kind0/type1. No allocation guard;unbounded name+30 copy. Fixed optional horizontal justification Left0/Center1/Right2 at972;vertical Top0/Center1/Bottom2 at976;Font900;Text64 via unbounded setter;Text x980/y984 overrides. Repeated State bitmap filename260 with comma/line64 Normal or Disabled loads handle and state-image bitmap setter on908/940;then repeated State anim similarly uses0x5F6680. Optional Tooltip text64,x,y[,font-1] calls0x5F6450. Ignores helper/load success,does not parse image crop/draw dimensions;returns staticbox.
char *__thiscall rf_ui_window_parse_staticbox_definition(int *this, const char **parser, _DWORD *a3)
{
  int v3; // eax
  char v4; // dl
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  char *v11; // [esp+Ch] [ebp-1E0h]
  char *v12; // [esp+10h] [ebp-1DCh]
  char *v13; // [esp+14h] [ebp-1D8h]
  void *v15; // [esp+20h] [ebp-1CCh]
  char v16[264]; // [esp+28h] [ebp-1C4h] BYREF
  char String1[64]; // [esp+130h] [ebp-BCh] BYREF
  int v18; // [esp+170h] [ebp-7Ch]
  int v19; // [esp+174h] [ebp-78h]
  char *v20; // [esp+178h] [ebp-74h]
  int type; // [esp+17Ch] [ebp-70h]
  char Destination[64]; // [esp+180h] [ebp-6Ch] BYREF
  int v23; // [esp+1C4h] [ebp-28h]
  int v24; // [esp+1C8h] [ebp-24h]
  int v25; // [esp+1CCh] [ebp-20h]
  int v26; // [esp+1D0h] [ebp-1Ch]
  int kind; // [esp+1D4h] [ebp-18h]
  int v28; // [esp+1D8h] [ebp-14h]
  int signed_decimal_or_hex_integer; // [esp+1DCh] [ebp-10h]
  int v30; // [esp+1E8h] [ebp-4h]

  type = 0;
  v18 = 0;
  v25 = 0;
  signed_decimal_or_hex_integer = -1;
  kind = rf_ui_base_get_kind(a3);
  if ( kind )
  {
    if ( kind == 1 )
    {
      v18 = *(this + 3);
      v25 = *(this + 4);
    }
  }
  else
  {
    type = rf_ui_gadget_get_type(a3);
    v18 = rf_ui_gadget_absolute_x(a3, 0);
    v25 = rf_ui_gadget_absolute_y(a3, 0);
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ":") )
    rf_text_parser_read_delimited_cstring((int)parser, Destination, 64, 34, 34);
  else
    Destination[0] = 0;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Id:");
  signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Position:");
  v23 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser) - v18;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
  v3 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  v24 = v3 - v25;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Size:");
  v28 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
  v26 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  v15 = operator new(0x3DCu);
  v30 = 0;
  if ( v15 )
    v13 = (char *)rf_ui_staticbox_construct((int)v15);
  else
    v13 = nullptr;
  v30 = -1;
  v20 = v13;
  rf_ui_staticbox_initialize((int)v13, (int)this, v23, v24, v28, v26, signed_decimal_or_hex_integer, 1);
  if ( !kind && type == 1 )
    rf_ui_gadget_set_parent(v20, (int)a3);
  v12 = Destination;
  v11 = v20 + 30;
  do
  {
    v4 = *v12;
    *v11++ = *v12++;
  }
  while ( v4 );
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Horizontal justification:") )
  {
    rf_text_parser_skip_trivia_and_cr_lines(parser);
    rf_text_parser_read_cr_line_cstring_if_fits((int)parser, String1, 64);
    if ( !_stricmp(String1, "Left") )
    {
      *((_DWORD *)v20 + 243) = 0;
    }
    else if ( !_stricmp(String1, "Center") )
    {
      *((_DWORD *)v20 + 243) = 1;
    }
    else if ( !_stricmp(String1, "Right") )
    {
      *((_DWORD *)v20 + 243) = 2;
    }
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Vertical justification:") )
  {
    rf_text_parser_skip_trivia_and_cr_lines(parser);
    rf_text_parser_read_cr_line_cstring_if_fits((int)parser, String1, 64);
    if ( !_stricmp(String1, off_643948) )
    {
      *((_DWORD *)v20 + 244) = 0;
    }
    else if ( !_stricmp(String1, "Center") )
    {
      *((_DWORD *)v20 + 244) = 1;
    }
    else if ( !_stricmp(String1, "Bottom") )
    {
      *((_DWORD *)v20 + 244) = 2;
    }
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Font:") )
  {
    v5 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    *((_DWORD *)v20 + 225) = v5;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Text:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, String1, 64, 34, 34);
    rf_ui_staticbox_copy_text_unbounded(v20, String1);
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Text x position:") )
  {
    v6 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    *((_DWORD *)v20 + 245) = v6;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Text y position:") )
  {
    v7 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    *((_DWORD *)v20 + 246) = v7;
  }
  while ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+State bitmap:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, v16, 260, 34, 34);
    if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ",") )
    {
      rf_text_parser_skip_trivia_and_cr_lines(parser);
      rf_text_parser_read_cr_line_cstring_if_fits((int)parser, String1, 64);
      if ( !_stricmp(String1, "Normal") )
      {
        v8 = rf_bitmap_load_with_optional_mipmap_generation(v16, (void *)0xFFFFFFFF, 1);
        rf_ui_state_image_set_bitmap((_DWORD *)v20 + 227, v8);
      }
      else if ( !_stricmp(String1, "Disabled") )
      {
        v9 = rf_bitmap_load_with_optional_mipmap_generation(v16, (void *)0xFFFFFFFF, 1);
        rf_ui_state_image_set_bitmap((_DWORD *)v20 + 235, v9);
      }
    }
  }
  while ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+State anim:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, v16, 260, 34, 34);
    if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ",") )
    {
      rf_text_parser_skip_trivia_and_cr_lines(parser);
      rf_text_parser_read_cr_line_cstring_if_fits((int)parser, String1, 64);
      if ( !_stricmp(String1, "Normal") )
      {
        rf_ui_staticbox_load_state_animation(v20, 0, v16);
      }
      else if ( !_stricmp(String1, "Disabled") )
      {
        rf_ui_staticbox_load_state_animation(v20, 1, v16);
      }
    }
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Tooltip:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, String1, 64, 34, 34);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
    v23 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
    v24 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ",") )
      v19 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    else
      v19 = -1;
    rf_ui_staticbox_replace_tooltip_record(v20, String1, v23, v24, v19);
  }
  return v20;
}

