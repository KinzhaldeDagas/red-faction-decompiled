// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B09C0 rf_ui_window_draw_background_and_children
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI window construction/navigation/parsing/drawing/cleanup, exact flag and list operations, original stack ABI and call sites): Thiscall no stack args. Virtual slot16 nonzero AL suppresses entire draw. Otherwise resets viewport fullscreen. If signed background1236>=0,sets white RGBA and draws unscaled bitmap at stored XY using global187CD38. Otherwise style=(flags584&3):0 draws no fill;1 fills full rect using theme1248+8;2 fills inset3 and draws bevel thickness3 offset0;3 fills inset5 and draws three bevels(thickness2 offset0,thickness2 offset2 using theme+12 both edges,thickness1 offset4 with swapped base edge colors). No minimum-size guard; inset dimensions can be negative. Calls virtual slot4(event0,id-99998),draws each tree root1220 via sibling624 virtual slot28,then calls slot4(event1,id-99998). Does not walk flat
// list,restore prior viewport/color or check individual child visibility locally; child virtual handles its own state. EAX is hidden-slot result or final callback residue.
int __thiscall rf_ui_window_draw_background_and_children(int *this)
{
  int result; // eax
  int v2; // [esp+0h] [ebp-Ch]
  _DWORD *i; // [esp+8h] [ebp-4h]

  result = (*(int (__thiscall **)(int *))(*this + 16))(this);
  if ( !(_BYTE)result )
  {
    rf_renderer_reset_viewport_full_screen();
    if ( *(this + 309) < 0 )
    {
      v2 = *(this + 146) & 3;
      switch ( v2 )
      {
        case 1:
          rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(this + 312) + 8));
          rf_renderer_fill_rectangle_clipped(*(this + 3), *(this + 4), *(this + 5), *(this + 6), dword_182ABB8);
          break;
        case 2:
          rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(this + 312) + 8));
          rf_renderer_fill_rectangle_clipped(
            *(this + 3) + 3,
            *(this + 4) + 3,
            *(this + 5) - 6,
            *(this + 6) - 6,
            dword_182ABB8);
          rf_ui_draw_beveled_rect_edges(
            *(this + 3),
            *(this + 4),
            *(this + 5),
            *(this + 6),
            (unsigned __int8 *)*(this + 312),
            (unsigned __int8 *)(*(this + 312) + 4),
            3,
            0);
          break;
        case 3:
          rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(this + 312) + 8));
          rf_renderer_fill_rectangle_clipped(
            *(this + 3) + 5,
            *(this + 4) + 5,
            *(this + 5) - 10,
            *(this + 6) - 10,
            dword_182ABB8);
          rf_ui_draw_beveled_rect_edges(
            *(this + 3),
            *(this + 4),
            *(this + 5),
            *(this + 6),
            (unsigned __int8 *)*(this + 312),
            (unsigned __int8 *)(*(this + 312) + 4),
            2,
            0);
          rf_ui_draw_beveled_rect_edges(
            *(this + 3),
            *(this + 4),
            *(this + 5),
            *(this + 6),
            (unsigned __int8 *)(*(this + 312) + 12),
            (unsigned __int8 *)(*(this + 312) + 12),
            2,
            2);
          rf_ui_draw_beveled_rect_edges(
            *(this + 3),
            *(this + 4),
            *(this + 5),
            *(this + 6),
            (unsigned __int8 *)(*(this + 312) + 4),
            (unsigned __int8 *)*(this + 312),
            1,
            4);
          break;
      }
    }
    else
    {
      rf_render_color_set_rgba8(255, 255, 255, 255);
      rf_bitmap_draw_unscaled_clipped(*(this + 309), *(this + 3), *(this + 4), unk_187CD38);
    }
    (*(void (__thiscall **)(int *, _DWORD, int))(*this + 4))(this, 0, -99998);
    for ( i = (_DWORD *)*(this + 305); i; i = (_DWORD *)i[156] )
      (*(void (__thiscall **)(_DWORD *))(*i + 28))(i);
    return (*(int (__thiscall **)(int *, int, int))(*this + 4))(this, 1, -99998);
  }
  return result;
}

