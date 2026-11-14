// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058CF40 rf_font_draw_text_aligned
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Measures complete text extent with maxBytes=-1 and supplied font. Alignment1 subtracts half maximum line width from X; alignment2 subtracts full width; other values retain X. Calls ordinary screen text drawer with resulting X,Y,font,mode and returns its EAX. It does not independently center each line; the drawer special X sentinel0x8000 has separate per-line behavior.
int __cdecl rf_font_draw_text_aligned(int a1, int a2, int a3, unsigned __int8 *a4, int a5, int a6)
{
  int v7; // [esp+4h] [ebp-8h] BYREF
  int v8; // [esp+8h] [ebp-4h] BYREF

  rf_font_measure_text_extent(&v8, &v7, a4, -1, a5);
  if ( a1 == 1 )
  {
    a2 -= v8 / 2;
  }
  else if ( a1 == 2 )
  {
    a2 -= v8;
  }
  return rf_font_draw_text_screen(a2, a3, a4, a5, a6);
}

