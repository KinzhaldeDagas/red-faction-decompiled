// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A9F80 rf_ui_draw_windows_tooltips_and_drag_preview
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: cdecl optional void hook. Ensures theme,resets clip,draws windows from head0x1CF7B5C via next+1252 using0x5B09C0,resetting clip after each;then invokes hook. Tooltip-ready0x1CF75C6 with hover0x1CF75E0 selects auxiliary record:base kind1(window) uses optional byte hit mask+1240 and region value0x5B1020;kind0 gadget type1 gates virtual region hit on DWORD+892,other types2,4,5,7,8 use first record. Region match compares record tag+284;candidate initializedNULL. Selected non-sentinel record draws via0x5F1E00. Dragged object0x1CF75D0 gets preview rectangle at mouse+offset,bitmap helper0x5F1B70 or fallback fill/border depending flags. Copies drag text to260-byte local WITHOUT length bound,centers measured text using font+908 and palette pointer+912;shadow if palette alpha+19 nonzero,foreground+12. No tooltip record allocation,input processing or
// drag count transfer. Return incidental final helper/result.
int __cdecl rf_ui_draw_windows_tooltips_and_drag_preview(void (*a1)(void))
{
  int result; // eax
  int height_select_current; // esi
  int spacing_select_current; // eax
  _BYTE *v4; // [esp+10h] [ebp-160h]
  char v5; // [esp+17h] [ebp-159h]
  unsigned __int8 *v6; // [esp+1Ch] [ebp-154h]
  char *label_buffer; // [esp+20h] [ebp-150h]
  unsigned __int8 *v8; // [esp+28h] [ebp-148h]
  int type; // [esp+2Ch] [ebp-144h]
  int v10; // [esp+30h] [ebp-140h]
  int v11; // [esp+30h] [ebp-140h]
  int v12; // [esp+34h] [ebp-13Ch] BYREF
  int v13; // [esp+38h] [ebp-138h] BYREF
  _DWORD *v14; // [esp+3Ch] [ebp-134h]
  int *v15; // [esp+40h] [ebp-130h]
  int v16; // [esp+44h] [ebp-12Ch] BYREF
  int v17; // [esp+48h] [ebp-128h] BYREF
  int *i; // [esp+4Ch] [ebp-124h]
  int v19; // [esp+50h] [ebp-120h] BYREF
  int flags; // [esp+54h] [ebp-11Ch]
  int v21; // [esp+58h] [ebp-118h]
  int v22; // [esp+5Ch] [ebp-114h]
  unsigned __int8 v23; // [esp+60h] [ebp-110h] BYREF
  _BYTE v24[259]; // [esp+61h] [ebp-10Fh] BYREF
  int v25; // [esp+168h] [ebp-8h] BYREF
  int v26; // [esp+16Ch] [ebp-4h]

  i = nullptr;
  rf_ui_initialize_default_theme_once();
  rf_renderer_reset_viewport_full_screen();
  v15 = (int *)unk_1CF7B5C;
  while ( v15 != dword_1CF7678 )
  {
    rf_ui_window_draw_background_and_children(v15);
    v15 = (int *)v15[313];
    rf_renderer_reset_viewport_full_screen();
  }
  if ( a1 )
    a1();
  result = unk_1CF75C6;
  if ( unk_1CF75C6 && dword_1CF75E0 )
  {
    result = rf_ui_base_get_kind(dword_1CF75E0);
    v26 = result;
    if ( result )
    {
      if ( v26 == 1 )
      {
        v15 = dword_1CF75E0;
        result = rf_ui_window_get_hit_mask(dword_1CF75E0);
        if ( result )
        {
          v11 = rf_ui_window_hit_mask_value_at_screen_point(v15, dword_1CF7594, dword_1CF75C0);
          for ( i = (int *)v15[73]; ; i = (int *)*i )
          {
            result = (int)(v15 + 73);
            if ( i == v15 + 73 || i[71] == v11 )
              break;
          }
        }
      }
    }
    else
    {
      type = rf_ui_gadget_get_type(dword_1CF75E0);
      switch ( type )
      {
        case 1:
          v14 = dword_1CF75E0;
          result = sub_5AAE60(dword_1CF75E0);
          if ( result )
          {
            result = (*(int (__thiscall **)(_DWORD *, int, int))(*v14 + 24))(v14, dword_1CF7594, dword_1CF75C0);
            v10 = result;
            for ( i = (int *)v14[73]; i != v14 + 73; i = (int *)*i )
            {
              result = (int)i;
              if ( i[71] == v10 )
                break;
              result = (int)i;
            }
          }
          break;
        case 2:
        case 4:
        case 5:
        case 7:
        case 8:
          result = dword_1CF75E0[73];
          i = (int *)result;
          break;
        default:
          result = type;
          break;
      }
    }
    if ( i )
    {
      result = (int)(dword_1CF75E0 + 73);
      if ( i != dword_1CF75E0 + 73 )
        result = rf_ui_tooltip_record_draw((int)i);
    }
  }
  if ( dword_1CF75D0 )
  {
    flags = rf_ui_button_get_flags(dword_1CF75D0);
    v8 = *((unsigned __int8 **)dword_1CF75D0 + 228);
    rf_ui_base_get_size(dword_1CF75D0, &v12, &v13);
    rf_ui_button_get_press_relative_draw_origin(dword_1CF75D0, &v25, &v19);
    if ( !rf_ui_state_image_draw((int *)dword_1CF75D0 + 261, v25 + dword_1CF7594, v19 + dword_1CF75C0, v12, v13, -1, -1) )
    {
      if ( (flags & 4) != 0 || (flags & 1) != 0 )
      {
        rf_render_color_set_packed_rgba8(v8 + 8);
        rf_renderer_fill_rectangle_clipped(v25 + dword_1CF7594, v19 + dword_1CF75C0, v12, v13, dword_182ABB8);
      }
      else
      {
        rf_render_color_set_packed_rgba8(v8 + 8);
        rf_renderer_fill_rectangle_clipped(
          dword_1CF7594 + v25 + 2,
          dword_1CF75C0 + v19 + 2,
          v12 - 4,
          v13 - 4,
          dword_182ABB8);
        rf_ui_draw_beveled_rect_edges(v25 + dword_1CF7594, v19 + dword_1CF75C0, v12, v13, v8, v8 + 4, 2, 0);
      }
    }
    label_buffer = rf_ui_button_get_label_buffer(dword_1CF75D0);
    v6 = &v23;
    do
    {
      v5 = *label_buffer;
      *v6++ = *label_buffer++;
    }
    while ( v5 );
    v4 = &v24[strlen((const char *)&v23)];
    result = v4 - v24;
    if ( v4 != v24 )
    {
      rf_font_measure_text_extent(&v17, &v16, &v23, -1, *((_DWORD *)dword_1CF75D0 + 227));
      height_select_current = rf_font_get_height_select_current(*((_DWORD *)dword_1CF75D0 + 227));
      spacing_select_current = rf_font_get_spacing_select_current(*((_DWORD *)dword_1CF75D0 + 227));
      v16 -= height_select_current - spacing_select_current - 1;
      v21 = v12 / 2 + v25 + dword_1CF7594 - v17 / 2;
      v22 = v13 / 2 + v19 + dword_1CF75C0 - v16 / 2;
      if ( v8[19] )
      {
        rf_render_color_set_packed_rgba8(v8 + 16);
        rf_font_draw_text_screen(v21 + 1, v22 + 1, &v23, *((_DWORD *)dword_1CF75D0 + 227), dword_182ABBC);
      }
      rf_render_color_set_packed_rgba8(v8 + 12);
      return rf_font_draw_text_screen(v21, v22, &v23, *((_DWORD *)dword_1CF75D0 + 227), dword_182ABBC);
    }
  }
  return result;
}

