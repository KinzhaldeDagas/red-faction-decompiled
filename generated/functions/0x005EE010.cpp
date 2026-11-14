// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EE010 rf_ui_slider_get_thumb_rect_unclamped
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This slider;four output pointers x,y,w,h. Computes FLOAT-rounded fraction=(signed position652)/(range648-1) without denominator guard or clamp. Initializes x=y0,w=width20,h=height24. Horizontal BYTE664!=0:x=truncate((width-thumb656)*fraction),w=thumb;vertical:y=truncate((height-thumb)*fraction),h=thumb. Coordinates local to slider. Range1 yields floating invalid/divide-by-zero;out-of-range position/thumb produces off-track geometry. No output NULL guards;return incidental this(horizontal) or height-output pointer(vertical).
_DWORD *__thiscall rf_ui_slider_get_thumb_rect_unclamped(int this, _DWORD *a2, _DWORD *a3, _DWORD *a4, _DWORD *a5)
{
  float v6; // [esp+10h] [ebp-4h]

  v6 = (double)*(int *)(this + 652) / (double)(*(_DWORD *)(this + 648) - 1);
  *a3 = 0;
  *a2 = 0;
  *a4 = *(_DWORD *)(this + 20);
  *a5 = *(_DWORD *)(this + 24);
  if ( *(_BYTE *)(this + 664) )
  {
    *a2 = (int)((double)(*(_DWORD *)(this + 20) - *(_DWORD *)(this + 656)) * v6);
    *a4 = *(_DWORD *)(this + 656);
    return (_DWORD *)this;
  }
  else
  {
    *a3 = (int)((double)(*(_DWORD *)(this + 24) - *(_DWORD *)(this + 656)) * v6);
    *a5 = *(_DWORD *)(this + 656);
    return a5;
  }
}

