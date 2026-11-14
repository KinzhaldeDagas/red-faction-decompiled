// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058CFC0 rf_font_draw_text_screen
// UNREALRED VERIFIED [hud-viewport-20261027] Text drawing reads glyph height from font record +52 and per-glyph bitmap width from +72 records, calls 0x571F80, and advances X by 0x58C290 output in the same coordinate units. Newline advances Y by source font height. No viewport-aspect multiplication appears here. A host proportional adapter must transform glyph extents, advances, wrapping/layout and bitmap extents together.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): NULL text writes last pen globals193BBA4/193BBA8 to input X/Y and returns X. Non-NULL chooses explicit nonnegative font index with no upper bound, else default; no NULL-font guard before reading atlas handle. Ensures atlas, then draws bytes>=32 as unscaled atlas subrectangles with glyph width and height+52, advancing by lookup output. CR/tab/other control bytes are ignored; LF adds height and resets X. X==0x8000 centers each remaining line via58D170. VERIFIED missing-glyph hazard: lookup return-1 is NOT checked before glyph and atlas-position array indexing. Normal tail updates last pen globals and returns final X; failed atlas path leaves last pen untouched and EAX incidental. No aspect/scale transform here.
int __cdecl rf_font_draw_text_screen(int a1, int a2, unsigned __int8 *a3, int a4, int a5)
{
  int result; // eax
  int v6; // [esp+0h] [ebp-28h]
  unsigned __int8 v7; // [esp+7h] [ebp-21h]
  int v8; // [esp+8h] [ebp-20h] BYREF
  int v9; // [esp+Ch] [ebp-1Ch]
  int v10; // [esp+10h] [ebp-18h] BYREF
  int v11; // [esp+14h] [ebp-14h]
  int v12; // [esp+18h] [ebp-10h]
  int v13; // [esp+1Ch] [ebp-Ch]
  int v14; // [esp+20h] [ebp-8h]
  int v15; // [esp+24h] [ebp-4h]

  if ( a3 )
  {
    if ( a4 >= 0 )
      dword_193BB9C = (int)&unk_193B688 + 108 * a4;
    else
      dword_193BB9C = unk_193BBA0;
    if ( *(int *)(dword_193BB9C + 84) >= 0
      || (rf_font_ensure_atlas_bitmap(dword_193BB9C), result = dword_193BB9C, *(int *)(dword_193BB9C + 84) >= 0) )
    {
      v14 = a1;
      v15 = a2;
      if ( a1 == 0x8000 )
        v14 = rf_font_center_current_line_x(a3);
      v13 = *(_DWORD *)(dword_193BB9C + 52);
      while ( *a3 )
      {
        v7 = *a3++;
        if ( v7 >= 0x20u )
        {
          v9 = rf_font_lookup_glyph_width_and_advance(v7, *a3, &v8, &v10);
          v6 = *(_DWORD *)(dword_193BB9C + 72) + 16 * v9;
          v12 = *(_DWORD *)(*(_DWORD *)(dword_193BB9C + 96) + 4 * v9);
          v11 = *(_DWORD *)(*(_DWORD *)(dword_193BB9C + 100) + 4 * v9);
          rf_bitmap_blit_unscaled_subrectangle_clipped(
            *(_DWORD *)(dword_193BB9C + 84),
            v14,
            v15,
            *(_DWORD *)(v6 + 4),
            v13,
            v12,
            v11,
            a5);
          v14 += v10;
        }
        else if ( v7 == 10 )
        {
          v15 += v13;
          if ( a1 == 0x8000 )
            v14 = rf_font_center_current_line_x(a3);
          else
            v14 = a1;
        }
      }
      unk_193BBA4 = v14;
      unk_193BBA8 = v15;
      return v14;
    }
  }
  else
  {
    unk_193BBA4 = a1;
    unk_193BBA8 = a2;
    return a1;
  }
  return result;
}

