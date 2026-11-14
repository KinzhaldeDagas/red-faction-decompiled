// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00470540 rf_ui_edit_initialize
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall(parent,x,y,text,font,widthLimit), RET24. Sets geometry X/Y, logical width+20=widthLimit, logical height+24=fontHeight, parent+4, width
// limit+96 and font+100. Copies input including NUL to inline text+64 with UNBOUNDED byte loop (32-byte field ends at+95); no strlen or width limit gate. Measures copied text
// into+56/+60; nonpositive measured height falls back to logical font height. Creates format4 bitmap(widthLimit,measuredHeight) at+44, clears it, adds reference, sets origin(1,0),
// draws copied text with supplied font, and arms SHARED caret deadline6F911C with offset0. No own bitmap-failure gate, old-resource release, text clipping or caret-byte reset.
int __thiscall rf_ui_edit_initialize(int this, int a2, int a3, int a4, char *a5, int a6, int a7)
{
  char v8; // [esp+13h] [ebp-11h]
  _BYTE *v9; // [esp+18h] [ebp-Ch]

  *(_DWORD *)(this + 12) = a3;
  *(_DWORD *)(this + 16) = a4;
  *(_DWORD *)(this + 20) = a7;
  *(_DWORD *)(this + 24) = rf_font_get_height_select_current(a6);
  *(_DWORD *)(this + 4) = a2;
  *(_DWORD *)(this + 96) = a7;
  *(_DWORD *)(this + 100) = a6;
  v9 = (_BYTE *)(this + 64);
  do
  {
    v8 = *a5;
    *v9++ = *a5++;
  }
  while ( v8 );
  rf_font_measure_text_extent(
    (_DWORD *)(this + 56),
    (_DWORD *)(this + 60),
    (unsigned __int8 *)(this + 64),
    strlen((const char *)(this + 64)),
    *(_DWORD *)(this + 100));
  if ( *(int *)(this + 60) <= 0 )
    *(_DWORD *)(this + 60) = *(_DWORD *)(this + 24);
  *(_DWORD *)(this + 44) = rf_bitmap_create_user_bitmap(4, a7, *(_DWORD *)(this + 60));
  rf_bitmap_clear_all_locked_texture_tile_bytes(*(_DWORD *)(this + 44));
  rf_bitmap_texture_add_reference_backend_dispatch(*(_DWORD *)(this + 44));
  *(_DWORD *)(this + 48) = 1;
  *(_DWORD *)(this + 52) = 0;
  rf_font_draw_text_into_bitmap(
    *(_DWORD *)(this + 48),
    *(_DWORD *)(this + 52),
    *(_DWORD *)(this + 44),
    (const char *)(this + 64),
    a6);
  return rf_clock_deadline_set_wrapped_offset(&dword_6F911C, 0);
}

