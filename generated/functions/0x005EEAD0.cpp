// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EEAD0 rf_ui_slider_draw_and_clamp_position
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): FIRST clamps position652:if>=range648,set range-1;then ifnegative,set0 (even when hidden). Hidden then returns. Resets clip,gets absolute position and thumb rectangle0x5EE010 (range1 denominator still unguarded). If enabled,draws leading track clipped before thumb using palette668+12,trailing track palette+16,then sets full-slider clip and draws raised thumb at local rect with palette0/4edge,8face,thickness2 via0x5F15F0. Uses nonzero rather than positive clip sizes. Blocked skips own track/thumb completely but still draws children/event2. Does not emit value-change event or restore prior clip;color/clip effects flow into children helper. Return incidental predicate/child helper.
int __thiscall rf_ui_slider_draw_and_clamp_position(int *this)
{
  int result; // eax
  int v3; // [esp+4h] [ebp-28h]
  int v4; // [esp+4h] [ebp-28h]
  int v5; // [esp+8h] [ebp-24h]
  int v6; // [esp+Ch] [ebp-20h] BYREF
  int v7; // [esp+10h] [ebp-1Ch] BYREF
  int v8; // [esp+14h] [ebp-18h] BYREF
  int v9; // [esp+18h] [ebp-14h] BYREF
  int v10; // [esp+1Ch] [ebp-10h]
  int v11; // [esp+20h] [ebp-Ch]
  int v12; // [esp+24h] [ebp-8h]
  int v13; // [esp+28h] [ebp-4h]

  if ( *(this + 163) >= *(this + 162) )
    *(this + 163) = *(this + 162) - 1;
  if ( *(this + 163) < 0 )
    *(this + 163) = 0;
  result = (*(unsigned __int8 (__thiscall **)(int *))(*this + 16))(this);
  if ( !(_BYTE)result )
  {
    rf_renderer_reset_viewport_full_screen();
    v10 = rf_ui_gadget_absolute_x(this, 0);
    v5 = rf_ui_gadget_absolute_y(this, 0);
    rf_ui_slider_get_thumb_rect_unclamped((int)this, &v6, &v7, &v9, &v8);
    if ( !rf_ui_gadget_is_interaction_blocked(this) )
    {
      v11 = v10;
      v12 = v5;
      v3 = *(this + 5);
      v13 = *(this + 6);
      if ( *((_BYTE *)this + 664) )
        v3 = v6;
      else
        v13 = v7;
      if ( v3 && v13 )
      {
        rf_renderer_set_viewport_and_relative_clip(v11, v12, v3, v13);
        rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(this + 167) + 12));
        rf_renderer_fill_rectangle_clipped(0, 0, *(this + 5), *(this + 6), dword_182ABB8);
      }
      v11 = v10;
      v12 = v5;
      v4 = *(this + 5);
      v13 = *(this + 6);
      if ( *((_BYTE *)this + 664) )
      {
        v11 += v9 + v6;
        v4 = *(this + 5) - v6 - v9;
      }
      else
      {
        v12 += v8 + v7;
        v13 = *(this + 6) - v7 - v8;
      }
      if ( v4 )
      {
        if ( v13 )
        {
          rf_renderer_set_viewport_and_relative_clip(v11, v12, v4, v13);
          rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(this + 167) + 16));
          rf_renderer_fill_rectangle_clipped(0, 0, *(this + 5), *(this + 6), dword_182ABB8);
        }
      }
      rf_renderer_set_viewport_and_relative_clip(v10, v5, *(this + 5), *(this + 6));
      rf_ui_draw_raised_rect(v6, v7, v9, v8, (unsigned __int8 *)*(this + 167), 2);
    }
    return rf_ui_gadget_draw_children_and_notify(this);
  }
  return result;
}

