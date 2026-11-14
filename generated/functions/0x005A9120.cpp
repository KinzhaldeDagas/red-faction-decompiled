// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A9120 rf_text_list_draw
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall list. Virtual predicate+16 true skips draw. Reflows dirty entries,DISABLES each scrollbar when content fits corresponding inner extent,ENABLES when overflow (0x5F1210/0x5F1260 modify disabled BYTE+28,not visibility). Resets clip to viewport. Unless flags+628 mask0x100,draws themed background(style+792 normal offset0,blocked offset12) when bitmap handle+696<0,else white-tinted unscaled bitmap at absolute widget origin. Mask0x200 computes hover entry from mouse plus scroll minus widget origin. Sets padded inner clip rectangle. For each vertically intersecting entry,gets font height and selects8-byte text/shadow color pair: blocked uses list style+24,selected entry style+56 offset8,hover offset16,normal0. Re-layouts each entry to shared line tables,draws complete lines;mask0x20 also permits partially clipped lines. Copies each line
// into512-byte local with stored length,adds NUL WITHOUT length<=511 check. Nonzero shadow alpha byte7 draws offset(1,1),then foreground at indent-scrollX,Y-scrollY. First/later indent and line gap respected. Ends by drawing child gadgets/emitting event2 through0x5ABF00. Does not explicitly restore incoming clip or validate shared-table line count; return branch-dependent predicate/helper result.
int __thiscall rf_text_list_draw(_DWORD *this)
{
  int result; // eax
  int v2; // eax
  int v3; // esi
  int v4; // esi
  int v5; // eax
  int v6; // eax
  int v7; // edx
  int v8; // esi
  int v9; // [esp-Ch] [ebp-23Ch]
  int v10; // [esp-8h] [ebp-238h]
  int v11; // [esp-8h] [ebp-238h]
  int v12; // [esp-8h] [ebp-238h]
  int v13; // [esp-4h] [ebp-234h]
  int v14; // [esp-4h] [ebp-234h]
  char Destination[512]; // [esp+8h] [ebp-228h] BYREF
  int *i; // [esp+20Ch] [ebp-24h]
  unsigned __int8 *v18; // [esp+210h] [ebp-20h]
  int *block_at_content_position; // [esp+214h] [ebp-1Ch]
  int height_select_current; // [esp+218h] [ebp-18h]
  bool v21; // [esp+21Fh] [ebp-11h]
  int v22; // [esp+220h] [ebp-10h]
  int j; // [esp+224h] [ebp-Ch]
  int v24; // [esp+228h] [ebp-8h]
  int v25; // [esp+22Ch] [ebp-4h]

  result = (*(int (__thiscall **)(_DWORD *))(*this + 16))(this);
  if ( !(_BYTE)result )
  {
    rf_text_list_reflow_dirty_blocks(this);
    if ( *(this + 197) )
    {
      if ( *(this + 170) <= rf_text_list_inner_width(this) )
        rf_ui_base_set_disabled_raw((_BYTE *)*(this + 197), 1);
      else
        rf_ui_base_set_enabled((_BYTE *)*(this + 197), (int)this, 1);
    }
    if ( *(this + 196) )
    {
      if ( *(this + 171) <= rf_text_list_inner_height(this) )
        rf_ui_base_set_disabled_raw((_BYTE *)*(this + 196), 1);
      else
        rf_ui_base_set_enabled((_BYTE *)*(this + 196), (int)this, 1);
    }
    rf_renderer_reset_viewport_full_screen();
    if ( (*(this + 157) & 0x100) == 0 )
    {
      if ( (int)*(this + 174) < 0 )
      {
        if ( rf_ui_gadget_is_interaction_blocked(this) )
          rf_ui_gadget_draw_sunken_face(this, (unsigned __int8 *)(*(this + 198) + 12), 1);
        else
          rf_ui_gadget_draw_sunken_face(this, (unsigned __int8 *)*(this + 198), 1);
      }
      else
      {
        rf_render_color_set_rgba8(255, 255, 255, 255);
        v13 = unk_187CD38;
        v10 = rf_ui_gadget_absolute_y(this, 0);
        v2 = rf_ui_gadget_absolute_x(this, 0);
        rf_bitmap_draw_unscaled_clipped(*(this + 174), v2, v10, v13);
      }
    }
    block_at_content_position = nullptr;
    if ( (*(this + 157) & 0x200) != 0 )
    {
      v3 = unk_1CF75C0 + *(this + 178);
      v11 = v3 - rf_ui_gadget_absolute_y(this, 0);
      v4 = unk_1CF7594 + *(this + 177);
      v5 = rf_ui_gadget_absolute_x(this, 0);
      block_at_content_position = rf_text_list_find_block_at_content_position(this, v4 - v5, v11, 0);
    }
    v14 = *(this + 6) - 2 * *(this + 176);
    v12 = *(this + 5) - 2 * *(this + 175);
    v9 = *(this + 176) + rf_ui_gadget_absolute_y(this, 0);
    v6 = rf_ui_gadget_absolute_x(this, 0);
    rf_renderer_set_viewport_and_relative_clip(*(this + 175) + v6, v9, v12, v14);
    for ( i = (int *)*(this + 183); i != this + 181; i = (int *)i[2] )
    {
      if ( rf_text_list_block_intersects_vertical_view(this, (int)i) )
      {
        height_select_current = rf_font_get_height_select_current(i[10]);
        if ( rf_ui_gadget_is_interaction_blocked(this) )
        {
          v18 = (unsigned __int8 *)(*(this + 198) + 24);
        }
        else if ( i == (int *)*(this + 173) )
        {
          v18 = (unsigned __int8 *)(i[14] + 8);
        }
        else if ( (*(this + 157) & 0x200) != 0 && block_at_content_position == i )
        {
          v18 = (unsigned __int8 *)(i[14] + 16);
        }
        else
        {
          v18 = (unsigned __int8 *)i[14];
        }
        v25 = i[4] - *(this + 178);
        v22 = rf_text_list_layout_block((int)this, i, v25);
        for ( j = 0; j < v22; ++j )
        {
          if ( j )
            v7 = i[8];
          else
            v7 = i[7];
          v24 = v7 - *(this + 177);
          v21 = 0;
          if ( v25 >= 0 )
          {
            v8 = height_select_current + v25;
            v21 = v8 <= rf_text_list_inner_height(this);
          }
          if ( v21 || (*(this + 157) & 0x20) != 0 )
          {
            strncpy(Destination, (&unk_1CF7540)[j], MEMORY[0x1CF74F0][j]);
            Destination[MEMORY[0x1CF74F0][j]] = 0;
            if ( v18[7] )
            {
              rf_render_color_set_packed_rgba8(v18 + 4);
              rf_font_draw_text_screen(v24 + 1, v25 + 1, (unsigned __int8 *)Destination, i[10], dword_182ABBC);
            }
            rf_render_color_set_packed_rgba8(v18);
            rf_font_draw_text_screen(v24, v25, (unsigned __int8 *)Destination, i[10], dword_182ABBC);
          }
          v25 += i[9] + height_select_current;
        }
      }
    }
    return rf_ui_gadget_draw_children_and_notify(this);
  }
  return result;
}

