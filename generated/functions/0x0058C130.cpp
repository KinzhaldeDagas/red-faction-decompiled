// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058C130 rf_font_measure_text_extent
// UNREALRED VERIFIED [text-layout-20261029]: cdecl width output,height output,optional BYTE string,signed max bytes,font ID. Null string writes both outputs0. Nonnull selects valid ID0..fontCount-1 at0x193B688 stride108,otherwise default,sets global current font. Negative max=strlen. Starts height at font DWORD+52 even when text empty/max0. Walks up to max bytes/NUL; LF resets current line width and adds font height ONLY if following byte nonzero. Other bytes call glyph advance helper0x58C290(current,next) and update maximum width. Lookahead reads following byte even at count limit. Returns height as incidental EAX on nonnull branch. No default-font null guard,pointer/output capacity checks or scaling/aspect multiplication.
_DWORD *__cdecl rf_font_measure_text_extent(_DWORD *a1, _DWORD *a2, unsigned __int8 *a3, int a4, int a5)
{
  _DWORD *result; // eax
  unsigned __int8 v6; // [esp+13h] [ebp-15h]
  int v7; // [esp+14h] [ebp-14h] BYREF
  int v8; // [esp+18h] [ebp-10h] BYREF
  int v9; // [esp+1Ch] [ebp-Ch]
  _DWORD *v10; // [esp+20h] [ebp-8h]
  int v11; // [esp+24h] [ebp-4h]

  if ( a3 )
  {
    if ( a5 >= 0 && a5 < unk_193BB98 )
      unk_193BB9C = (char *)&unk_193B688 + 108 * a5;
    else
      unk_193BB9C = unk_193BBA0;
    if ( a4 < 0 )
      a4 = strlen((const char *)a3);
    v9 = 0;
    v10 = nullptr;
    v11 = 0;
    v10 = *(_DWORD **)(unk_193BB9C + 52);
    while ( *a3 && a4 > 0 )
    {
      v6 = *a3++;
      --a4;
      if ( v6 == 10 )
      {
        v9 = 0;
        if ( *a3 )
          v10 = (_DWORD *)((char *)v10 + *(_DWORD *)(unk_193BB9C + 52));
      }
      else
      {
        rf_font_lookup_glyph_width_and_advance(v6, *a3, &v7, &v8);
        v9 += v8;
        if ( v9 > v11 )
          v11 = v9;
      }
    }
    result = v10;
    *a2 = v10;
    *a1 = v11;
  }
  else
  {
    *a1 = 0;
    *a2 = 0;
    return a1;
  }
  return result;
}

