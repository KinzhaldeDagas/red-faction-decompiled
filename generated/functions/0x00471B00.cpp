// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00471B00 rf_ui_cycle_list_render
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall cycle list. countDWORD360==0 returns without drawing. For nonzero count, signed selected364<0 sets0; ELSE selected>=count sets count-1 (no
// second lower clamp). Focus8/enabled9 selects white255, enabled-only192, disabled96. Uses parallel arrays selected index: bitmap+40, xOffset104,yOffset168,width232,height296, each
// DWORD stride4. DestinationXY=trunc((absoluteXY+itemOffset)*axisScale), WH=trunc(itemWH*axisScale); full item sourceWH/style187CD34,12 arguments. No count<=16/negative-count guard,
// bitmap validity check, callbacks or color restore. Negative selection branch does not also run upper clamp.
int __thiscall rf_ui_cycle_list_render(int this)
{
  int result; // eax
  int v3; // [esp+Ch] [ebp-10h]
  int v4; // [esp+10h] [ebp-Ch]

  result = this;
  if ( *(_DWORD *)(this + 360) )
  {
    if ( *(int *)(this + 364) >= 0 )
    {
      if ( *(_DWORD *)(this + 364) >= *(_DWORD *)(this + 360) )
        *(_DWORD *)(this + 364) = *(_DWORD *)(this + 360) - 1;
    }
    else
    {
      *(_DWORD *)(this + 364) = 0;
    }
    if ( *(_BYTE *)(this + 8) && *(_BYTE *)(this + 9) )
    {
      rf_render_color_set_rgba8(255, 255, 255, 255);
    }
    else if ( *(_BYTE *)(this + 9) )
    {
      rf_render_color_set_rgba8(192, 192, 192, 255);
    }
    else
    {
      rf_render_color_set_rgba8(96, 96, 96, 255);
    }
    v4 = (int)((double)(*(_DWORD *)(this + 4 * *(_DWORD *)(this + 364) + 104) + rf_ui_control_absolute_x((_DWORD *)this))
             * rf_ui_scale_x);
    v3 = (int)((double)(*(_DWORD *)(this + 4 * *(_DWORD *)(this + 364) + 168) + rf_ui_control_absolute_y((_DWORD *)this))
             * rf_ui_scale_y);
    return rf_bitmap_blit_subrectangle_backend_dispatch(
             *(_DWORD *)(this + 4 * *(_DWORD *)(this + 364) + 40),
             v4,
             v3,
             (int)((double)*(int *)(this + 4 * *(_DWORD *)(this + 364) + 232) * rf_ui_scale_x),
             (int)((double)*(int *)(this + 4 * *(_DWORD *)(this + 364) + 296) * rf_ui_scale_y),
             0,
             0,
             *(_DWORD *)(this + 4 * *(_DWORD *)(this + 364) + 232),
             *(_DWORD *)(this + 4 * *(_DWORD *)(this + 364) + 296),
             0,
             0,
             unk_187CD34);
  }
  return result;
}

