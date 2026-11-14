// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AFDC0 rf_ui_window_read_table_definition
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI window construction/navigation/parsing/drawing/cleanup, exact flag and list operations, original stack ABI and call sites): Thiscall window,path,parser context,RET8. Constructs memory text parser; open failure only formats diagnostic then CONTINUES parsing. Requires ordered $Position:x,y and $Size:w,h. Defaults ID=-99998,flags1. Optional ordered +Name quoted64-byte local buffer,+Id,+Modal dialog20h,+Modeless dialog40h,+Allow arrows4,+Allow wrap8,+Always a selection10h; initializes and links window. Then copies local name through NUL to window+30 without bound; if +Name absent local name buffer was never initialized. Optional +Background bitmap uses5B0900;optional +Mask bitmap uses5B0820. Tooltip loop occurs ONLY INSIDE mask-bitmap branch: quoted text,integer a,comma x,comma y,optional comma final
// integer(default-1),appends record5B0560. Repeatedly accepts #Button,#Checkbox,#Container,#Inputbox,#Listbox,#Slider,#Static through established per-control readers,then requires #End,closes parser and invokes destructor. Tags are ordered/case-insensitive according to parser helpers; no top-level rollback on failed open or later parse failure. Raw ECX before both bitmap loaders is window; decompiler may omit it because inferred call signatures. Return is parser destructor residue,not window.
void **__thiscall rf_ui_window_read_table_definition(int *this, char *Str, void *context)
{
  char v4; // [esp+7h] [ebp-195h]
  char *v5; // [esp+Ch] [ebp-190h]
  char *v6; // [esp+10h] [ebp-18Ch]
  char Destination[64]; // [esp+18h] [ebp-184h] BYREF
  int v9; // [esp+58h] [ebp-144h]
  int v10; // [esp+5Ch] [ebp-140h]
  int signed_decimal_or_hex_integer; // [esp+60h] [ebp-13Ch]
  int v12; // [esp+64h] [ebp-138h]
  int v13; // [esp+68h] [ebp-134h]
  int v14; // [esp+6Ch] [ebp-130h]
  int v15; // [esp+70h] [ebp-12Ch]
  int v16; // [esp+74h] [ebp-128h]
  void *self[69]; // [esp+78h] [ebp-124h] BYREF
  int v18; // [esp+198h] [ebp-4h]

  v16 = -99998;
  v13 = 1;
  rf_memory_text_parser_construct_empty(self);
  v18 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, Str, context, 0) )
    sprintf(&unk_18CD828, "unable to open UI table file \"%s\"\n", Str);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Position:");
  signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer((char **)self);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, ",");
  v12 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)self);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Size:");
  v15 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)self);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, ",");
  v14 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)self);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "+Name:") )
    rf_text_parser_read_delimited_cstring((int)self, Destination, 64, 34, 34);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "+Id:") )
    v16 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)self);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "+Modal dialog") )
    v13 |= 0x20u;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "+Modeless dialog") )
    v13 |= 0x40u;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "+Allow arrows") )
    v13 |= 4u;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "+Allow wrap") )
    v13 |= 8u;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "+Always a selection") )
    v13 |= 0x10u;
  rf_ui_window_initialize_and_link(this, signed_decimal_or_hex_integer, v12, v15, v14, v16, v13);
  v6 = Destination;
  v5 = (char *)this + 30;
  do
  {
    v4 = *v6;
    *v5++ = *v6++;
  }
  while ( v4 );
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "+Background bitmap:") )
  {
    rf_text_parser_read_delimited_cstring((int)self, Destination, 64, 34, 34);
    rf_ui_window_load_background_bitmap(Destination);
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "+Mask bitmap:") )
  {
    rf_text_parser_read_delimited_cstring((int)self, Destination, 64, 34, 34);
    rf_ui_window_load_mask_bitmap(Destination);
    while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "+Tooltip:") )
    {
      rf_text_parser_read_delimited_cstring((int)self, Destination, 64, 34, 34);
      rf_text_parser_require_case_insensitive_prefix_or_fatal(self, ",");
      v10 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)self);
      rf_text_parser_require_case_insensitive_prefix_or_fatal(self, ",");
      signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer((char **)self);
      rf_text_parser_require_case_insensitive_prefix_or_fatal(self, ",");
      v12 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)self);
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, ",") )
        v9 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)self);
      else
        v9 = -1;
      rf_ui_window_append_tooltip_record(this, Destination, v10, signed_decimal_or_hex_integer, v12, v9);
    }
  }
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
              while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#Button") )
                rf_ui_window_parse_button_definition(this, (const char **)self, this);
              if ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#Checkbox") )
                break;
              rf_ui_window_parse_checkbox_definition(this, (const char **)self, this);
            }
            if ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#Container") )
              break;
            rf_ui_window_parse_container_definition(this, (const char **)self, this);
          }
          if ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#Inputbox") )
            break;
          rf_ui_window_parse_inputbox_definition(this, (const char **)self, this);
        }
        if ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#Listbox") )
          break;
        rf_ui_window_parse_text_list_definition(this, (const char **)self, this);
      }
      if ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#Slider") )
        break;
      rf_ui_window_parse_slider_definition(this, (const char **)self, this);
    }
    if ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#Static") )
      break;
    rf_ui_window_parse_staticbox_definition(this, (const char **)self, this);
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "#End");
  rf_memory_text_parser_close_buffer(self);
  v18 = -1;
  return rf_memory_text_parser_destroy_buffer_adapter(self);
}

