// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046FFB0 rf_ui_text_widget_initialize
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall(parent,x,y,width,height,text,font), RET28. Stores logical geometry/parent, creates format4 bitmap(width,height) at+44 and adds texture
// reference. Measures text width+56, then overwrites measured height+60 with font_get_height(font); text origin+48=1/+52=0. Valid bitmap is cleared; measured width<=0 skips draw. If
// 2*fontHeight>logicalHeight draws ORIGINAL whole string once. Otherwise line capacity=min(signed logicalHeight/fontHeight,4), copies up to255 source bytes into256-byte local with
// byte255 zeroed BEFORE copy, tokenizes NEWLINES via46FB30 and draws up to capacity nonnull tokens at y+=fontHeight. This is height-selected newline tokenization, NOT width-dependent
// word wrapping. No own zero fontHeight guard before IDIV or nonpositive-capacity guard before tokenizer output[0]. Finally sets inline color+40 black opaque. No previous-bitmap
// release; return is incidental temporary color pointer.
int *__thiscall rf_ui_text_widget_initialize(int *this, int a2, int a3, int a4, int a5, int a6, char *Source, int a8)
{
  int *result; // eax
  _BYTE v10[4]; // [esp+14h] [ebp-120h] BYREF
  int i; // [esp+18h] [ebp-11Ch]
  char Destination[256]; // [esp+1Ch] [ebp-118h] BYREF
  int v13; // [esp+120h] [ebp-14h]
  int v14[4]; // [esp+124h] [ebp-10h] BYREF

  *(this + 3) = a3;
  *(this + 4) = a4;
  *(this + 5) = a5;
  *(this + 6) = a6;
  *(this + 1) = a2;
  *(this + 11) = rf_bitmap_create_user_bitmap(4, *(this + 5), *(this + 6));
  rf_bitmap_texture_add_reference_backend_dispatch(*(this + 11));
  rf_font_measure_text_extent(this + 14, this + 15, (unsigned __int8 *)Source, strlen(Source), a8);
  *(this + 15) = rf_font_get_height_select_current(a8);
  *(this + 12) = 1;
  *(this + 13) = 0;
  if ( *(this + 11) >= 0 )
  {
    rf_bitmap_clear_all_locked_texture_tile_bytes(*(this + 11));
    if ( *(this + 14) > 0 )
    {
      if ( 2 * *(this + 15) > *(this + 6) )
      {
        rf_font_draw_text_into_bitmap(*(this + 12), *(this + 13), *(this + 11), Source, a8);
      }
      else
      {
        v13 = rf_int_min_signed(*(this + 6) / *(this + 15), 4);
        Destination[255] = 0;
        strncpy(Destination, Source, 0xFFu);
        rf_text_tokenize_newline_pointers(Destination, (char **)v14, v13);
        for ( i = 0; i < v13 && v14[i]; ++i )
        {
          rf_font_draw_text_into_bitmap(*(this + 12), *(this + 13), *(this + 11), (const char *)v14[i], a8);
          *(this + 13) += *(this + 15);
        }
      }
    }
  }
  result = (int *)rf_rgba8_construct_components_return_self(v10, 0, 0, 0, 255);
  *(this + 10) = *result;
  return result;
}

