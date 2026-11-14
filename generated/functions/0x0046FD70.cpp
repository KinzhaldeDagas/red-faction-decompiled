// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046FD70 rf_ui_panel_render_bitmap
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall ECX panel, no stack arguments. Sets white RGBA255, computes physical X/Y=trunc(absolute control X/Y*respective UI scale), physical
// width/height=trunc(logical DWORD+20/+24*respective scale). Blits bitmap+40, full logical source dimensions from(0,0), flags0/0, style187CD34;12 stack arguments/48-byte caller
// cleanup. No handle validity or BYTE8/9 gate, no color restore beyond initial white.
int __thiscall rf_ui_panel_render_bitmap(int *this)
{
  int v3; // [esp+Ch] [ebp-10h]
  int v4; // [esp+10h] [ebp-Ch]

  rf_render_color_set_rgba8(255, 255, 255, 255);
  v4 = (int)((double)rf_ui_control_absolute_x(this) * rf_ui_scale_x);
  v3 = (int)((double)rf_ui_control_absolute_y(this) * rf_ui_scale_y);
  return rf_bitmap_blit_subrectangle_backend_dispatch(
           *(this + 10),
           v4,
           v3,
           (int)((double)*(this + 5) * rf_ui_scale_x),
           (int)((double)*(this + 6) * rf_ui_scale_y),
           0,
           0,
           *(this + 5),
           *(this + 6),
           0,
           0,
           unk_187CD34);
}

