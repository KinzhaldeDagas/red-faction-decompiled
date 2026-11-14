// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AC210 rf_ui_window_parse_button_definition
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This=owner window; parser and parent UI object arguments. Uses parent kind+8:window1 uses this window x/y; gadget0 uses absolute parent position and type+596. Optional colon quoted name64,required $Id,$Position x,y,$Size w,h; subtract parent absolute position. Flags parsed in fixed order:Drag and drop0x10,Repeats2,Always use face color8,Use right mouse button0x400. Allocates0x450 button and constructs; window parent initializes normally; type1 gadget initializes window-owned then reparents; type7 uses parent initializer forcing repeat flag2. Other kinds/types leave constructed button uninitialized. No allocation failure guard. Unbounded name copy to+30. Optional Text64 copies to+636,Font writes+908; repeated Hotkey entries write+588+4*unchecked index (more than2 overwrites adjacent fields);
// optional Hotspot sets+600. Repeated State bitmap/anim entries load quoted filename260 and comma-separated case-insensitive names Normal916,Highlighted948,Pressed980,Disabled1012,Drag1044. First bitmap loaded once per entry; first anim allocated/loaded then shared across named states. Unknown/absent state leaves NULL/stale state pointer; no validation before image setter. Optional Tooltip text64,x,y[,font default-1] invokes0x5EFC00. Returns button pointer; no rendering.
char *__thiscall rf_ui_window_parse_button_definition(int *this, const char **parser, _DWORD *a3)
{
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v8; // [esp-4h] [ebp-20Ch]
  char v9; // [esp+7h] [ebp-201h]
  char *v10; // [esp+Ch] [ebp-1FCh]
  char *v11; // [esp+10h] [ebp-1F8h]
  char *v12; // [esp+14h] [ebp-1F4h]
  void *v14; // [esp+20h] [ebp-1E8h]
  _DWORD *v15; // [esp+28h] [ebp-1E0h]
  char v16[264]; // [esp+2Ch] [ebp-1DCh] BYREF
  char String1[64]; // [esp+134h] [ebp-D4h] BYREF
  int v18; // [esp+174h] [ebp-94h]
  int v19; // [esp+178h] [ebp-90h]
  int type; // [esp+17Ch] [ebp-8Ch]
  int v21; // [esp+180h] [ebp-88h]
  char Destination[64]; // [esp+184h] [ebp-84h] BYREF
  bool v23; // [esp+1CAh] [ebp-3Eh]
  bool v24; // [esp+1CBh] [ebp-3Dh]
  char v25[4]; // [esp+1CCh] [ebp-3Ch] BYREF
  int v26; // [esp+1D0h] [ebp-38h]
  int v27; // [esp+1D4h] [ebp-34h]
  int v28; // [esp+1D8h] [ebp-30h]
  int v29; // [esp+1DCh] [ebp-2Ch]
  int animation; // [esp+1E0h] [ebp-28h]
  int v31; // [esp+1E4h] [ebp-24h]
  int v32; // [esp+1E8h] [ebp-20h]
  int v33; // [esp+1ECh] [ebp-1Ch]
  int signed_decimal_or_hex_integer; // [esp+1F0h] [ebp-18h]
  char *v35; // [esp+1F4h] [ebp-14h]
  int kind; // [esp+1F8h] [ebp-10h]
  int v37; // [esp+204h] [ebp-4h]

  signed_decimal_or_hex_integer = -1;
  v29 = 0;
  v19 = 0;
  v32 = 0;
  type = 0;
  v25[0] = 13;
  v25[1] = 0;
  kind = rf_ui_base_get_kind(a3);
  if ( kind )
  {
    if ( kind == 1 )
    {
      v19 = *(this + 3);
      v32 = *(this + 4);
    }
  }
  else
  {
    type = rf_ui_gadget_get_type(a3);
    v19 = rf_ui_gadget_absolute_x(a3, 0);
    v32 = rf_ui_gadget_absolute_y(a3, 0);
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ":") )
    rf_text_parser_read_delimited_cstring((int)parser, Destination, 64, 34, 34);
  else
    Destination[0] = 0;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Id:");
  signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Position:");
  v27 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser) - v19;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
  v3 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  v28 = v3 - v32;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Size:");
  v33 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
  v31 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Drag and drop") )
    v29 |= 0x10u;
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Repeats") )
    v29 |= 2u;
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Always use face color") )
    v29 |= 8u;
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Use right mouse button") )
    v29 |= 0x400u;
  v14 = operator new(0x450u);
  v37 = 0;
  if ( v14 )
    v12 = (char *)rf_ui_button_construct((int)v14);
  else
    v12 = nullptr;
  v37 = -1;
  v35 = v12;
  if ( kind )
  {
    if ( kind == 1 )
      rf_ui_button_initialize_in_window((int)v35, (int)this, v27, v28, v33, v31, signed_decimal_or_hex_integer, v29, 1);
  }
  else if ( type == 1 )
  {
    rf_ui_button_initialize_in_window((int)v35, (int)this, v27, v28, v33, v31, signed_decimal_or_hex_integer, v29, 1);
    rf_ui_gadget_set_parent(v35, (int)a3);
  }
  else if ( type == 7 )
  {
    rf_ui_button_initialize_as_child((int)v35, a3, v27, v28, v33, v31, signed_decimal_or_hex_integer, v29, 1);
  }
  v11 = Destination;
  v10 = v35 + 30;
  do
  {
    v9 = *v11;
    *v10++ = *v11++;
  }
  while ( v9 );
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Text:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, String1, 64, 34, 34);
    rf_ui_button_copy_label_unbounded(v35, String1);
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Font:") )
  {
    v4 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    *((_DWORD *)v35 + 227) = v4;
  }
  v26 = 0;
  while ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Hotkey:") )
  {
    v8 = v26;
    v5 = rf_ui_parse_hotkey_name(parser);
    rf_ui_gadget_set_key_slot(v35, v5, v8);
    ++v26;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Hotspot:") )
  {
    v6 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    rf_ui_gadget_set_region_id(v35, v6);
  }
  while ( 1 )
  {
    v23 = 0;
    v24 = rf_text_parser_try_consume_case_insensitive_prefix(parser, "+State bitmap:");
    if ( !v24 )
    {
      v23 = rf_text_parser_try_consume_case_insensitive_prefix(parser, "+State anim:");
      if ( !v23 )
        break;
    }
    v15 = nullptr;
    animation = 0;
    v21 = -1;
    rf_text_parser_read_delimited_cstring((int)parser, v16, 260, 34, 34);
    while ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ",") )
    {
      rf_text_parser_skip_trivia_and_cr_lines(parser);
      rf_text_parser_copy_until_substring_or_read_line((char **)parser, String1, 64, ",", v25);
      if ( !_stricmp(String1, "Normal") )
      {
        v15 = v35 + 916;
      }
      else if ( !_stricmp(String1, "Highlighted") )
      {
        v15 = v35 + 948;
      }
      else if ( !_stricmp(String1, "Pressed") )
      {
        v15 = v35 + 980;
      }
      else if ( !_stricmp(String1, "Disabled") )
      {
        v15 = v35 + 1012;
      }
      else if ( !_stricmp(String1, "Drag") )
      {
        v15 = v35 + 1044;
      }
      if ( v24 )
      {
        if ( v21 == -1 )
          v21 = rf_bitmap_load_with_optional_mipmap_generation(v16, (void *)0xFFFFFFFF, 1);
        rf_ui_state_image_set_bitmap(v15, v21);
      }
      if ( v23 )
      {
        if ( animation )
          rf_ui_state_image_attach_animation(v15, animation);
        else
          animation = rf_ui_state_image_load_animation((int)v15, v16);
      }
    }
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "+Tooltip:") )
  {
    rf_text_parser_read_delimited_cstring((int)parser, String1, 64, 34, 34);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
    v27 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, ",");
    v28 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, ",") )
      v18 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)parser);
    else
      v18 = -1;
    rf_ui_button_replace_tooltip_record(v35, String1, v27, v28, v18);
  }
  return v35;
}

