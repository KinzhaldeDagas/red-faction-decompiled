// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058C290 rf_font_lookup_glyph_width_and_advance
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Uses global current font193BB9C. glyphIndex=unsigned currentByte-firstCode(+44); outside[0,glyphCount+40) writes bitmapWidth0, advance=defaultAdvance+48 and returns-1. Otherwise writes glyph+4 bitmap width and glyph+0 advance from16-byte record at+72. Signed-short glyph+12 is first kerning index. With valid following byte (not0/LF and in font range), scans 3-byte kerning records at+68; all three bytes are SIGN-extended, including pair indices and adjustment. Loads pair bytes before testing kerningIndex<count+60 and has no initial upper-bound check. After scan only second-character equality is checked before adding adjustment, without rechecking first index or record limit. Returns glyph index; no NULL current-font/output checks.
int __cdecl rf_font_lookup_glyph_width_and_advance(unsigned __int8 a1, unsigned __int8 a2, _DWORD *a3, _DWORD *a4)
{
  char *i; // [esp+0h] [ebp-18h]
  int v6; // [esp+8h] [ebp-10h]
  int v7; // [esp+Ch] [ebp-Ch]
  int v8; // [esp+10h] [ebp-8h]
  int v9; // [esp+14h] [ebp-4h]

  v8 = a1 - *(_DWORD *)(unk_193BB9C + 44);
  if ( v8 >= 0 && v8 < *(_DWORD *)(unk_193BB9C + 40) )
  {
    v7 = *(_DWORD *)(unk_193BB9C + 72) + 16 * v8;
    *a3 = *(_DWORD *)(v7 + 4);
    *a4 = *(_DWORD *)v7;
    v9 = *(__int16 *)(v7 + 12);
    if ( v9 > -1 )
    {
      if ( a2 )
      {
        if ( a2 != 10 )
        {
          v6 = a2 - *(_DWORD *)(unk_193BB9C + 44);
          if ( v6 >= 0 && v6 < *(_DWORD *)(unk_193BB9C + 40) )
          {
            for ( i = (char *)(*(_DWORD *)(unk_193BB9C + 68) + 3 * v9);
                  *i == v8 && i[1] < v6 && v9 < *(_DWORD *)(unk_193BB9C + 60);
                  i += 3 )
            {
              ++v9;
            }
            if ( i[1] == v6 )
              *a4 += i[2];
          }
        }
      }
    }
    return v8;
  }
  else
  {
    *a3 = 0;
    *a4 = *(_DWORD *)(unk_193BB9C + 48);
    return -1;
  }
}

