// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058D5F0 rf_font_draw_text_into_bitmap
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Gets destination bitmap dimensions, selects explicit nonnegative font index without upper bound or default, checks pointer and ensures atlas. Uses strlen, then iterates unsigned text bytes with lookahead. Valid glyph and penX<bitmapWidth copies its atlas subrect via horizontal-tile CPU copier573A80; height is font+52. Always advances by lookup output, including fallback for missing glyphs. No newline/control-byte layout handling here; unlike screen drawing, LF does not start another row. Negative X/Y and source clipping follow copier behavior; no explicit lower X or Y checks. Success returns starting X in EAX despite inherited char* type; other paths vary.
char *__cdecl rf_font_draw_text_into_bitmap(int a1, int a2, unsigned int a3, const char *a4, int a5)
{
  char *result; // eax
  unsigned __int8 v6; // [esp+13h] [ebp-25h]
  signed int i; // [esp+14h] [ebp-24h]
  int v8; // [esp+18h] [ebp-20h] BYREF
  int v9; // [esp+1Ch] [ebp-1Ch] BYREF
  int v10; // [esp+20h] [ebp-18h]
  int v11; // [esp+24h] [ebp-14h] BYREF
  int v12; // [esp+28h] [ebp-10h] BYREF
  int v13; // [esp+2Ch] [ebp-Ch]
  int v14; // [esp+30h] [ebp-8h]
  signed int v15; // [esp+34h] [ebp-4h]

  result = (char *)rf_bitmap_get_resolved_dimensions(a3, &v8, &v12);
  if ( a5 >= 0 )
  {
    result = (char *)&unk_193B688 + 108 * a5;
    dword_193BB9C = (int)result;
  }
  else
  {
    dword_193BB9C = unk_193BBA0;
  }
  if ( dword_193BB9C )
  {
    if ( *(int *)(dword_193BB9C + 84) >= 0
      || (rf_font_ensure_atlas_bitmap(dword_193BB9C), result = (char *)dword_193BB9C, *(int *)(dword_193BB9C + 84) >= 0) )
    {
      v13 = a1;
      v14 = a2;
      v11 = 0;
      v15 = strlen(a4);
      for ( i = 0; i < v15; ++i )
      {
        v6 = a4[i];
        if ( !v6 )
          break;
        v10 = rf_font_lookup_glyph_width_and_advance(v6, a4[i + 1], &v9, &v11);
        if ( v10 >= 0 && v13 < v8 )
          rf_bitmap_copy_subrectangle_to_horizontal_tiles(
            v13,
            v14,
            a3,
            *(_DWORD *)(*(_DWORD *)(dword_193BB9C + 96) + 4 * v10),
            *(_DWORD *)(*(_DWORD *)(dword_193BB9C + 100) + 4 * v10),
            v9,
            *(_DWORD *)(dword_193BB9C + 52),
            *(_DWORD *)(dword_193BB9C + 84));
        v13 += v11;
      }
      return (char *)a1;
    }
  }
  return result;
}

