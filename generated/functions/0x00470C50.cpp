// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00470C50 rf_ui_image_button_initialize
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall(normalFilename,selectedFilename,x,y,hotkey,label,font), RET28. Sets X/Y/hotkey. Each nonempty texture filename loads(-1,0) and adds
// reference; empty filename PRESERVES old handle. Logical dimensions come from valid normal handle+40, else valid selected+44. Creates format4 label surface+48 at logicalWH, adds
// reference, measures whole label into+60/+64, centers text origin+52/+56 using signed division truncation. If surface valid clears it; if measured width>0, prewrites local32-byte
// buffer[31]=NUL THEN strncpy(buffer,label,32), which CAN OVERWRITE terminator for long label. Tokenizes up to2 newline tokens; no second token draws ORIGINAL full label at
// whole-label-centered origin. Two tokens: independently measure/center each horizontally; y1=(height-line1Height)/3, y2=(2*(height-line2Height))/3 with signed IDIV, leaving
// extents/origin for line2. No word wrap, parent/state setup, previous-resource release, source-null or own local-string termination repair.
char *__thiscall rf_ui_image_button_initialize(
        int *this,
        char *a2,
        char *a3,
        int a4,
        int a5,
        int a6,
        char *Source,
        int a8)
{
  char *result; // eax
  char Destination[32]; // [esp+54h] [ebp-2Ch] BYREF
  int v11; // [esp+78h] [ebp-8h] BYREF
  unsigned __int8 *v12; // [esp+7Ch] [ebp-4h]

  *(this + 3) = a4;
  *(this + 4) = a5;
  *(this + 7) = a6;
  if ( strlen(a2) )
  {
    *(this + 10) = rf_bitmap_load_with_optional_mipmap_generation(a2, (void *)0xFFFFFFFF, 0);
    rf_bitmap_texture_add_reference_backend_dispatch(*(this + 10));
  }
  if ( *(this + 10) >= 0 )
    rf_bitmap_get_resolved_dimensions(*(this + 10), this + 5, this + 6);
  if ( strlen(a3) )
  {
    *(this + 11) = rf_bitmap_load_with_optional_mipmap_generation(a3, (void *)0xFFFFFFFF, 0);
    rf_bitmap_texture_add_reference_backend_dispatch(*(this + 11));
  }
  if ( *(this + 11) >= 0 && *(this + 10) < 0 )
    rf_bitmap_get_resolved_dimensions(*(this + 11), this + 5, this + 6);
  *(this + 12) = rf_bitmap_create_user_bitmap(4, *(this + 5), *(this + 6));
  rf_bitmap_texture_add_reference_backend_dispatch(*(this + 12));
  rf_font_measure_text_extent(this + 15, this + 16, (unsigned __int8 *)Source, strlen(Source), a8);
  *(this + 13) = (*(this + 5) - *(this + 15)) / 2;
  *(this + 14) = (*(this + 6) - *(this + 16)) / 2;
  result = (char *)this;
  if ( *(this + 12) >= 0 )
  {
    rf_bitmap_clear_all_locked_texture_tile_bytes(*(this + 12));
    result = (char *)this;
    if ( *(this + 15) > 0 )
    {
      Destination[31] = 0;
      strncpy(Destination, Source, 0x20u);
      rf_text_tokenize_newline_pointers(Destination, (char **)&v11, 2);
      if ( v12 )
      {
        rf_font_measure_text_extent(this + 15, this + 16, (unsigned __int8 *)v11, strlen((const char *)v11), a8);
        *(this + 13) = (*(this + 5) - *(this + 15)) / 2;
        *(this + 14) = (*(this + 6) - *(this + 16)) / 3;
        rf_font_draw_text_into_bitmap(*(this + 13), *(this + 14), *(this + 12), (const char *)v11, a8);
        rf_font_measure_text_extent(this + 15, this + 16, v12, strlen((const char *)v12), a8);
        *(this + 13) = (*(this + 5) - *(this + 15)) / 2;
        *(this + 14) = 2 * (*(this + 6) - *(this + 16)) / 3;
        return rf_font_draw_text_into_bitmap(*(this + 13), *(this + 14), *(this + 12), (const char *)v12, a8);
      }
      else
      {
        return rf_font_draw_text_into_bitmap(*(this + 13), *(this + 14), *(this + 12), Source, a8);
      }
    }
  }
  return result;
}

