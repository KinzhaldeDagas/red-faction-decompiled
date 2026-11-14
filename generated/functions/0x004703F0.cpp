// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004703F0 rf_ui_label_render
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall ECX label. Signed bitmap+44<0 returns without drawing. For focused BYTE8 AND enabled BYTE9 sets RGBA240/240/240/255; enabled unfocused uses
// inline packed color+40; disabled uses48/48/48/128. Blits bitmap at trunc(absoluteXY*axisScale), destination trunc(logicalWH*axisScale), full logical sourceWH, offsets0, flags0/0,
// style187CD34,12 stack arguments. Does not restore color; BYTE9 selects tint rather than suppressing draw.
int __thiscall rf_ui_label_render(int this)
{
  int result; // eax
  int v3; // [esp+Ch] [ebp-10h]
  int v4; // [esp+10h] [ebp-Ch]

  result = this;
  if ( *(int *)(this + 44) >= 0 )
  {
    if ( *(_BYTE *)(this + 8) && *(_BYTE *)(this + 9) )
    {
      rf_render_color_set_rgba8(240, 240, 240, 255);
    }
    else if ( *(_BYTE *)(this + 9) )
    {
      rf_render_color_set_packed_rgba8((unsigned __int8 *)(this + 40));
    }
    else
    {
      rf_render_color_set_rgba8(48, 48, 48, 128);
    }
    v4 = (int)((double)rf_ui_control_absolute_x((_DWORD *)this) * rf_ui_scale_x);
    v3 = (int)((double)rf_ui_control_absolute_y((_DWORD *)this) * rf_ui_scale_y);
    return rf_bitmap_blit_subrectangle_backend_dispatch(
             *(_DWORD *)(this + 44),
             v4,
             v3,
             (int)((double)*(int *)(this + 20) * rf_ui_scale_x),
             (int)((double)*(int *)(this + 24) * rf_ui_scale_y),
             0,
             0,
             *(_DWORD *)(this + 20),
             *(_DWORD *)(this + 24),
             0,
             0,
             unk_187CD34);
  }
  return result;
}

