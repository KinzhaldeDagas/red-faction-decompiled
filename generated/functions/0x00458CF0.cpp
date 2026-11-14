// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00458CF0 rf_ui_trim_cstring_to_width_with_ellipsis
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Cdecl(mutableCstring,font,maxPixelWidth,maxCharacters). Measure full Cstring;only signed measuredWidth>maxPixelWidth
// changes it. If signed strlen>maxCharacters-3,set text[maxCharacters-3]=NUL. Then copy original ellipsis pointer661E7C ("...") at CURRENT strlen-1,OVERWRITING last byte rather than
// appending. Remeasure;while still too wide overwrite at current strlen-4 with ellipsis,remeasure. With3-byte ellipsis,each subsequent iteration removes one more byte. No minimum
// length/maxCharacters,buffer capacity,min ellipsis-width,NULL or UTF8 guard. Can write before buffer for invalid/small limits or widths narrower than ellipsis;does not safely
// guarantee fitting every width. Return font-measure EAX residue,not new length/success. Level row usesmaxCharacters32 after already-unbounded copies.
_DWORD *__cdecl rf_ui_trim_cstring_to_width_with_ellipsis(char *a1, int a2, int a3, int a4)
{
  _DWORD *result; // eax
  char v5; // [esp+13h] [ebp-75h]
  char *v6; // [esp+18h] [ebp-70h]
  char *v7; // [esp+1Ch] [ebp-6Ch]
  char v8; // [esp+43h] [ebp-45h]
  char *v9; // [esp+48h] [ebp-40h]
  char *v10; // [esp+4Ch] [ebp-3Ch]
  int v11; // [esp+80h] [ebp-8h] BYREF
  int v12; // [esp+84h] [ebp-4h] BYREF

  result = rf_font_measure_text_extent(&v12, &v11, (unsigned __int8 *)a1, strlen(a1), a2);
  if ( v12 > a3 )
  {
    if ( (int)strlen(a1) > a4 - 3 )
      a1[a4 - 3] = 0;
    v10 = off_661E7C;
    v9 = &a1[strlen(a1) - 1];
    do
    {
      v8 = *v10;
      *v9++ = *v10++;
    }
    while ( v8 );
    while ( 1 )
    {
      result = rf_font_measure_text_extent(&v12, &v11, (unsigned __int8 *)a1, strlen(a1), a2);
      if ( v12 <= a3 )
        break;
      v7 = off_661E7C;
      v6 = &a1[strlen(a1) - 4];
      do
      {
        v5 = *v7;
        *v6++ = *v7++;
      }
      while ( v5 );
    }
  }
  return result;
}

