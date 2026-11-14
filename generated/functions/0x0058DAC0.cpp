// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058DAC0 rf_font_wrap_next_line
// UNREALRED VERIFIED [text-layout-20261029]: cdecl length output,C string,width,font. Initializes length=-1,measures ENTIRE text (max width across LF lines). If full measured width<=limit,sets length=strlen and returnsNULL,so embedded LF is NOT split in this branch. Overflow branch measures each prefix,stops when prefix width>limit,tracks START of latest whitespace run(space,tab,LF). Encountering LF before overflow returns next byte pointer WITHOUT first setting length to that newline index;length remains previous run/-1. No whitespace break uses current index. Skips spaces/tabs at break then one LF,returnsNULL at end else next source pointer. Does not copy/mutate string. Negative width may return unchanged source with length0; caller has no nonprogress guard. No null/negative-width validation; repeated prefix measurement is not linear time.
char *__cdecl rf_font_wrap_next_line(int *a1, char *a2, int a3, int a4)
{
  int v6; // [esp+14h] [ebp-14h]
  int i; // [esp+18h] [ebp-10h]
  int j; // [esp+18h] [ebp-10h]
  char v9; // [esp+1Fh] [ebp-9h]
  int v10; // [esp+20h] [ebp-8h] BYREF
  int v11; // [esp+24h] [ebp-4h] BYREF

  v9 = 0;
  *a1 = -1;
  v6 = strlen(a2);
  rf_font_measure_text_extent(&v11, &v10, (unsigned __int8 *)a2, -1, a4);
  if ( v11 > a3 )
  {
    for ( i = 0; i < v6; ++i )
    {
      rf_font_measure_text_extent(&v11, &v10, (unsigned __int8 *)a2, i, a4);
      if ( v11 > a3 )
        break;
      if ( a2[i] == 10 )
        return &a2[i + 1];
      if ( rf_text_byte_is_space_tab_lf(a2[i]) )
      {
        if ( !v9 )
          *a1 = i;
        v9 = 1;
      }
      else
      {
        v9 = 0;
      }
    }
    if ( *a1 < 0 )
      *a1 = i;
    for ( j = *a1; j < v6 && rf_text_byte_is_space_or_tab(a2[j]); ++j )
      ;
    if ( j < v6 && a2[j] == 10 )
      ++j;
    if ( j == v6 )
      return nullptr;
    else
      return &a2[j];
  }
  else
  {
    *a1 = v6;
    return nullptr;
  }
}

