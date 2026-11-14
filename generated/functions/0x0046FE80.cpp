// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046FE80 rf_ui_label_initialize_measured_text
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall(parent,x,y,text,font), RET20. Sets parent+4/X+12/Y+16. Measures strlen(text) into extents+56/+60, copies those into logical
// width/height+20/+24; sets text origin+48=1/+52=0. Creates format4 bitmap(width+2,height) at+44 and adds texture reference BEFORE signed handle validity check. If handle>=0 clears
// and draws original text/font at(1,0). Sets packed color+40=black RGBA(0,0,0,255) even on load failure. No old-bitmap release, null/source/size guard or word wrapping; return is
// packed color residue.
int __thiscall rf_ui_label_initialize_measured_text(int *this, int a2, int a3, int a4, char *a5, int a6)
{
  int result; // eax
  _BYTE v8[4]; // [esp+14h] [ebp-4h] BYREF

  *(this + 3) = a3;
  *(this + 4) = a4;
  *(this + 1) = a2;
  rf_font_measure_text_extent(this + 14, this + 15, (unsigned __int8 *)a5, strlen(a5), a6);
  *(this + 5) = *(this + 14);
  *(this + 6) = *(this + 15);
  *(this + 12) = 1;
  *(this + 13) = 0;
  *(this + 11) = rf_bitmap_create_user_bitmap(4, *(this + 5) + 2, *(this + 6));
  rf_bitmap_texture_add_reference_backend_dispatch(*(this + 11));
  if ( *(this + 11) >= 0 )
  {
    rf_bitmap_clear_all_locked_texture_tile_bytes(*(this + 11));
    rf_font_draw_text_into_bitmap(*(this + 12), *(this + 13), *(this + 11), a5, a6);
  }
  result = *(_DWORD *)rf_rgba8_construct_components_return_self(v8, 0, 0, 0, 255);
  *(this + 10) = result;
  return result;
}

