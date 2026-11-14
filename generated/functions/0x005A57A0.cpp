// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A57A0 rf_text_block_layout_wrapped_lines
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall block,default width,starting callback Y,optional width callback(Y,linePitch). Block fields: dirty BYTE+4,next+8,previous+12,topY+16,width+20,height+24,first indent+28,later indent+32,line gap+36,font+40,line count+44,text pointer+48. Pitch=gap+font height. Resets count,width; wraps through0x58DAC0 using callback width when NONZERO,otherwise default,minus current indent. Stores borrowed line pointers in shared table0x1CF7540 and lengths at0x1CF74F0,measures prefix width+indent,maximizes block width,advances source/Y and uses later indent after first line. Final height=lineCount*pitch-gap; ignores measured height returned by text metric helper. Empty string still yields one line. NO line-count bound: table bases are only80bytes apart,so zero-based length entry20 overwrites pointer entry0. Width callback negative/nonprogressing wrap can
// repeat source indefinitely. Newline early-return from wrap helper may leave length=-1,causing strlen of remaining source. Does not clear dirty byte,copy text,allocate per-block line arrays or validate pointers.
int __thiscall rf_text_block_layout_wrapped_lines(int *this, int a2, int a3, int (__cdecl *a4)(int, int))
{
  int v5; // [esp+10h] [ebp-2Ch]
  char *v7; // [esp+18h] [ebp-24h]
  int v8; // [esp+1Ch] [ebp-20h] BYREF
  int v9; // [esp+20h] [ebp-1Ch]
  int v10; // [esp+24h] [ebp-18h]
  char *v11; // [esp+28h] [ebp-14h]
  int v12; // [esp+2Ch] [ebp-10h]
  int v13; // [esp+30h] [ebp-Ch]
  int v14; // [esp+34h] [ebp-8h] BYREF
  int v15; // [esp+38h] [ebp-4h] BYREF

  v13 = *(this + 9) + rf_font_get_height_select_current(*(this + 10));
  *(this + 11) = 0;
  v7 = (char *)*(this + 12);
  *(this + 5) = 0;
  v12 = *(this + 7);
  while ( 1 )
  {
    if ( a4 )
    {
      v9 = a4(a3, v13);
      v5 = v9 ? v9 : a2;
      v10 = v5;
    }
    else
    {
      v10 = a2;
    }
    v11 = rf_font_wrap_next_line(&v8, v7, v10 - v12, *(this + 10));
    (&unk_1CF7540)[*(this + 11)] = v7;
    MEMORY[0x1CF74F0][(*(this + 11))++] = v8 < 0 ? strlen(v7) : v8;
    rf_font_measure_text_extent(&v15, &v14, (unsigned __int8 *)v7, v8, *(this + 10));
    v15 += v12;
    if ( v15 > *(this + 5) )
      *(this + 5) = v15;
    if ( !v11 )
      break;
    v12 = *(this + 8);
    v7 = v11;
    a3 += v13;
  }
  *(this + 6) = *(this + 11) * v13 - *(this + 9);
  return *(this + 11);
}

