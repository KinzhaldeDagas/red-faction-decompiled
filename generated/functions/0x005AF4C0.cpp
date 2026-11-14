// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AF4C0 rf_ui_window_navigate_selection_by_scan_code
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI window construction/navigation/parsing/drawing/cleanup, exact flag and list operations, original stack ABI and call sites): Thiscall window,one stack scan code,RET4. Always clears shared candidate1CF7C1C and resets best metric1CF7C20=999999999. Handles200 up,203 left,205 right,208 down; recognized codes return0,unrecognized return input unchanged. With selected gadget1228,gets absolute XY and size,forms integer centers (size+2*absolute)/2,invokes matching directional wrapper using top/left/right/bottom boundary respectively; assigns candidate to1228 only if nonNULL. Without selection walks flat child list head1204 to embedded sentinel592 via next612 and chooses strict minimum signed boundary metric:up windowBottom-childBottom,left windowRight-childRight,right childX-windowX,down childY-windowY,using LOCAL stored
// rectangles. Absolute-position/size helper results in that branch are discarded. Negative metrics allowed; ties retain first. No local enabled/hidden filter or allow-arrows flag4 test in initial flat-list selection. If no candidate,retains prior selection. Shared navigation globals are not reentrant.
int __thiscall rf_ui_window_navigate_selection_by_scan_code(int this, int a2)
{
  int result; // eax
  _DWORD *i; // [esp+Ch] [ebp-24h]
  _DWORD *m; // [esp+Ch] [ebp-24h]
  _DWORD *j; // [esp+Ch] [ebp-24h]
  _DWORD *k; // [esp+Ch] [ebp-24h]
  int v8; // [esp+10h] [ebp-20h]
  int y; // [esp+14h] [ebp-1Ch]
  int x; // [esp+18h] [ebp-18h]
  int v11; // [esp+1Ch] [ebp-14h]
  int v12; // [esp+28h] [ebp-8h] BYREF
  int v13; // [esp+2Ch] [ebp-4h] BYREF

  dword_1CF7C20 = 999999999;
  unk_1CF7C1C = 0;
  if ( *(_DWORD *)(this + 1228) )
  {
    rf_ui_base_get_size(*(_DWORD **)(this + 1228), &v13, &v12);
    v8 = rf_ui_gadget_absolute_x(*(_DWORD **)(this + 1228), 0);
    y = rf_ui_gadget_absolute_y(*(_DWORD **)(this + 1228), 0);
    x = (v13 + v8 + v8) / 2;
    v11 = (v12 + y + y) / 2;
    switch ( a2 )
    {
      case 200:
        rf_ui_window_find_navigation_above_with_wrap((void *)this, x, y);
        goto LABEL_34;
      case 203:
        rf_ui_window_find_navigation_left_with_wrap((void *)this, v8, v11);
        goto LABEL_34;
      case 205:
        rf_ui_window_find_navigation_right_with_wrap((void *)this, v13 + v8, v11);
        goto LABEL_34;
      case 208:
        rf_ui_window_find_navigation_below_with_wrap((void *)this, x, v12 + y);
        goto LABEL_34;
      default:
        result = a2;
        break;
    }
  }
  else
  {
    switch ( a2 )
    {
      case 200:
        for ( i = *(_DWORD **)(this + 1204); i != (_DWORD *)(this + 592); i = (_DWORD *)i[153] )
        {
          rf_ui_gadget_absolute_y(i, 0);
          rf_ui_base_get_size(i, &v13, &v12);
          if ( *(_DWORD *)(this + 24) + *(_DWORD *)(this + 16) - i[4] - i[6] < dword_1CF7C20 )
          {
            dword_1CF7C20 = *(_DWORD *)(this + 24) + *(_DWORD *)(this + 16) - i[4] - i[6];
            unk_1CF7C1C = i;
          }
        }
        goto LABEL_34;
      case 203:
        for ( j = *(_DWORD **)(this + 1204); j != (_DWORD *)(this + 592); j = (_DWORD *)j[153] )
        {
          rf_ui_gadget_absolute_x(j, 0);
          rf_ui_base_get_size(j, &v13, &v12);
          if ( *(_DWORD *)(this + 20) + *(_DWORD *)(this + 12) - j[3] - j[5] < dword_1CF7C20 )
          {
            dword_1CF7C20 = *(_DWORD *)(this + 20) + *(_DWORD *)(this + 12) - j[3] - j[5];
            unk_1CF7C1C = j;
          }
        }
        goto LABEL_34;
      case 205:
        for ( k = *(_DWORD **)(this + 1204); k != (_DWORD *)(this + 592); k = (_DWORD *)k[153] )
        {
          rf_ui_gadget_absolute_x(k, 0);
          if ( k[3] - *(_DWORD *)(this + 12) < dword_1CF7C20 )
          {
            dword_1CF7C20 = k[3] - *(_DWORD *)(this + 12);
            unk_1CF7C1C = k;
          }
        }
        goto LABEL_34;
      case 208:
        for ( m = *(_DWORD **)(this + 1204); m != (_DWORD *)(this + 592); m = (_DWORD *)m[153] )
        {
          rf_ui_gadget_absolute_y(m, 0);
          if ( m[4] - *(_DWORD *)(this + 16) < dword_1CF7C20 )
          {
            dword_1CF7C20 = m[4] - *(_DWORD *)(this + 16);
            unk_1CF7C1C = m;
          }
        }
LABEL_34:
        if ( unk_1CF7C1C )
          *(_DWORD *)(this + 1228) = unk_1CF7C1C;
        result = 0;
        break;
      default:
        result = a2;
        break;
    }
  }
  return result;
}

