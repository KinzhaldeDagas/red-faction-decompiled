// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F04B0 rf_ui_button_draw
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Skips virtual hidden+16;resets clip. Branch priority:blocked uses disabled image+1012/palette+40;pressed predicate or global drag source uses pressed+980/palette+20;state5 or navigation target with(hover target or primary button not held) uses highlighted+948/palette+20;else normal+916/palette+0. Image helper0x5F1B70 attempts selected image;success optionally overlays full face color if flag8. On no image,flag4 forces flat fill;else pressed predicate or flag0x20 uses sunken bevel and text offset1;else flag1 flat;otherwise raised bevel,thickness2. Palette block20bytes:edge colors0/4,face8,text12,shadow16. Centers nonempty label636 using font908;adjusts measured height by fontHeight-metric58c0e0-1;optional shadow when alpha19,then foreground. Flagmask0x3C0 draws direction triangle in foreground
// color. Draws no children and emits no draw event here. Does not restore color,font or previous clip.
void __thiscall rf_ui_button_draw(int this)
{
  int v1; // eax
  int height_select_current; // esi
  int spacing_select_current; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // esi
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // esi
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // esi
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // [esp-14h] [ebp-A4h]
  int v22; // [esp-14h] [ebp-A4h]
  int v23; // [esp-14h] [ebp-A4h]
  int v24; // [esp-14h] [ebp-A4h]
  int v25; // [esp-10h] [ebp-A0h]
  int v26; // [esp-10h] [ebp-A0h]
  int v27; // [esp-10h] [ebp-A0h]
  int v28; // [esp-10h] [ebp-A0h]
  int v29; // [esp-Ch] [ebp-9Ch]
  int v30; // [esp-Ch] [ebp-9Ch]
  int v31; // [esp-Ch] [ebp-9Ch]
  int v32; // [esp-Ch] [ebp-9Ch]
  int v34; // [esp+48h] [ebp-48h]
  int v35; // [esp+4Ch] [ebp-44h] BYREF
  int v36; // [esp+50h] [ebp-40h] BYREF
  int v37; // [esp+54h] [ebp-3Ch]
  int v38; // [esp+58h] [ebp-38h]
  int v39; // [esp+5Ch] [ebp-34h] BYREF
  int v40; // [esp+60h] [ebp-30h] BYREF
  int v41; // [esp+64h] [ebp-2Ch]
  int v42; // [esp+68h] [ebp-28h]
  int v43; // [esp+6Ch] [ebp-24h] BYREF
  int v44; // [esp+70h] [ebp-20h] BYREF
  int v45; // [esp+74h] [ebp-1Ch]
  int v46; // [esp+78h] [ebp-18h]
  int v47; // [esp+7Ch] [ebp-14h] BYREF
  int v48; // [esp+80h] [ebp-10h] BYREF
  int v49; // [esp+84h] [ebp-Ch]
  unsigned __int8 *v50; // [esp+88h] [ebp-8h]
  int v51; // [esp+8Ch] [ebp-4h]

  v51 = 0;
  if ( !(*(unsigned __int8 (__thiscall **)(int))(*(_DWORD *)this + 16))(this) )
  {
    rf_renderer_reset_viewport_full_screen();
    if ( rf_ui_gadget_is_interaction_blocked((_DWORD *)this) )
    {
      v50 = (unsigned __int8 *)(*(_DWORD *)(this + 912) + 40);
      v29 = *(_DWORD *)(this + 24);
      v25 = *(_DWORD *)(this + 20);
      v21 = rf_ui_gadget_absolute_y((_DWORD *)this, 0);
      v1 = rf_ui_gadget_absolute_x((_DWORD *)this, 0);
      if ( rf_ui_state_image_draw((int *)(this + 1012), v1, v21, v25, v29, -1, -1) )
      {
        if ( (*(_DWORD *)(this + 628) & 8) != 0 )
          rf_ui_gadget_draw_inset_solid_face((_DWORD *)this, *((_DWORD *)v50 + 2), 0);
        goto LABEL_14;
      }
      if ( (*(_DWORD *)(this + 628) & 4) != 0 )
        goto LABEL_8;
      if ( rf_ui_button_is_pressed_visual((_DWORD *)this) || (*(_DWORD *)(this + 628) & 0x20) != 0 )
      {
        rf_ui_gadget_draw_sunken_face((int *)this, v50, 2);
        v51 = 1;
      }
      else
      {
        if ( (*(_DWORD *)(this + 628) & 1) != 0 )
        {
LABEL_8:
          rf_ui_gadget_draw_inset_solid_face((_DWORD *)this, *((_DWORD *)v50 + 2), 0);
          goto LABEL_14;
        }
        rf_ui_gadget_draw_raised_face((int *)this, v50, 2);
      }
LABEL_14:
      if ( this + 636 + strlen((const char *)(this + 636)) + 1 != this + 637 )
      {
        rf_font_measure_text_extent(&v47, &v48, (unsigned __int8 *)(this + 636), -1, *(_DWORD *)(this + 908));
        height_select_current = rf_font_get_height_select_current(*(_DWORD *)(this + 908));
        spacing_select_current = rf_font_get_spacing_select_current(*(_DWORD *)(this + 908));
        v48 -= height_select_current - spacing_select_current - 1;
        v4 = rf_ui_gadget_absolute_x((_DWORD *)this, 0);
        v49 = v51 + *(_DWORD *)(this + 20) / 2 + v4 - v47 / 2;
        v5 = rf_ui_gadget_absolute_y((_DWORD *)this, 0);
        v46 = v51 + *(_DWORD *)(this + 24) / 2 + v5 - v48 / 2;
        if ( v50[19] )
        {
          rf_render_color_set_packed_rgba8(v50 + 16);
          rf_font_draw_text_screen(
            v49 + 1,
            v46 + 1,
            (unsigned __int8 *)(this + 636),
            *(_DWORD *)(this + 908),
            dword_182ABBC);
        }
        rf_render_color_set_packed_rgba8(v50 + 12);
        rf_font_draw_text_screen(v49, v46, (unsigned __int8 *)(this + 636), *(_DWORD *)(this + 908), dword_182ABBC);
      }
LABEL_70:
      if ( (*(_DWORD *)(this + 628) & 0x3C0) != 0 )
      {
        rf_render_color_set_packed_rgba8(v50 + 12);
        rf_ui_button_draw_direction_triangle((_DWORD *)this);
      }
      return;
    }
    if ( rf_ui_button_is_pressed_visual((_DWORD *)this) || (char *)this == dword_1CF75D0 )
    {
      v50 = (unsigned __int8 *)(*(_DWORD *)(this + 912) + 20);
      v30 = *(_DWORD *)(this + 24);
      v26 = *(_DWORD *)(this + 20);
      v22 = rf_ui_gadget_absolute_y((_DWORD *)this, 0);
      v6 = rf_ui_gadget_absolute_x((_DWORD *)this, 0);
      if ( rf_ui_state_image_draw((int *)(this + 980), v6, v22, v26, v30, -1, -1) )
      {
        if ( (*(_DWORD *)(this + 628) & 8) != 0 )
          rf_ui_gadget_draw_inset_solid_face((_DWORD *)this, *((_DWORD *)v50 + 2), 0);
        goto LABEL_32;
      }
      if ( (*(_DWORD *)(this + 628) & 4) != 0 )
        goto LABEL_26;
      if ( rf_ui_button_is_pressed_visual((_DWORD *)this) || (*(_DWORD *)(this + 628) & 0x20) != 0 )
      {
        rf_ui_gadget_draw_sunken_face((int *)this, v50, 2);
        v51 = 1;
      }
      else
      {
        if ( (*(_DWORD *)(this + 628) & 1) != 0 )
        {
LABEL_26:
          rf_ui_gadget_draw_inset_solid_face((_DWORD *)this, *((_DWORD *)v50 + 2), 0);
          goto LABEL_32;
        }
        rf_ui_gadget_draw_raised_face((int *)this, v50, 2);
      }
LABEL_32:
      if ( this + 636 + strlen((const char *)(this + 636)) + 1 != this + 637 )
      {
        rf_font_measure_text_extent(&v43, &v44, (unsigned __int8 *)(this + 636), -1, *(_DWORD *)(this + 908));
        v7 = rf_font_get_height_select_current(*(_DWORD *)(this + 908));
        v8 = rf_font_get_spacing_select_current(*(_DWORD *)(this + 908));
        v44 -= v7 - v8 - 1;
        v9 = rf_ui_gadget_absolute_x((_DWORD *)this, 0);
        v45 = v51 + *(_DWORD *)(this + 20) / 2 + v9 - v43 / 2;
        v10 = rf_ui_gadget_absolute_y((_DWORD *)this, 0);
        v42 = v51 + *(_DWORD *)(this + 24) / 2 + v10 - v44 / 2;
        if ( v50[19] )
        {
          rf_render_color_set_packed_rgba8(v50 + 16);
          rf_font_draw_text_screen(
            v45 + 1,
            v42 + 1,
            (unsigned __int8 *)(this + 636),
            *(_DWORD *)(this + 908),
            dword_182ABBC);
        }
        rf_render_color_set_packed_rgba8(v50 + 12);
        rf_font_draw_text_screen(v45, v42, (unsigned __int8 *)(this + 636), *(_DWORD *)(this + 908), dword_182ABBC);
      }
      goto LABEL_70;
    }
    if ( *(_DWORD *)(this + 632) == 5
      || rf_ui_gadget_is_owner_navigation_target((_DWORD *)this)
      && (rf_ui_gadget_is_owner_hover_target((_DWORD *)this) || !rf_mouse_get_button_held_byte(0)) )
    {
      v50 = (unsigned __int8 *)(*(_DWORD *)(this + 912) + 20);
      v31 = *(_DWORD *)(this + 24);
      v27 = *(_DWORD *)(this + 20);
      v23 = rf_ui_gadget_absolute_y((_DWORD *)this, 0);
      v11 = rf_ui_gadget_absolute_x((_DWORD *)this, 0);
      if ( rf_ui_state_image_draw((int *)(this + 948), v11, v23, v27, v31, -1, -1) )
      {
        if ( (*(_DWORD *)(this + 628) & 8) != 0 )
          rf_ui_gadget_draw_inset_solid_face((_DWORD *)this, *((_DWORD *)v50 + 2), 0);
        goto LABEL_51;
      }
      if ( (*(_DWORD *)(this + 628) & 4) != 0 )
        goto LABEL_46;
      if ( (*(_DWORD *)(this + 628) & 0x20) != 0 )
      {
        rf_ui_gadget_draw_sunken_face((int *)this, v50, 2);
        v51 = 1;
      }
      else
      {
        if ( (*(_DWORD *)(this + 628) & 1) != 0 )
        {
LABEL_46:
          rf_ui_gadget_draw_inset_solid_face((_DWORD *)this, *((_DWORD *)v50 + 2), 0);
          goto LABEL_51;
        }
        rf_ui_gadget_draw_raised_face((int *)this, v50, 2);
      }
LABEL_51:
      if ( this + 636 + strlen((const char *)(this + 636)) + 1 != this + 637 )
      {
        rf_font_measure_text_extent(&v39, &v40, (unsigned __int8 *)(this + 636), -1, *(_DWORD *)(this + 908));
        v12 = rf_font_get_height_select_current(*(_DWORD *)(this + 908));
        v13 = rf_font_get_spacing_select_current(*(_DWORD *)(this + 908));
        v40 -= v12 - v13 - 1;
        v14 = rf_ui_gadget_absolute_x((_DWORD *)this, 0);
        v41 = v51 + *(_DWORD *)(this + 20) / 2 + v14 - v39 / 2;
        v15 = rf_ui_gadget_absolute_y((_DWORD *)this, 0);
        v38 = v51 + *(_DWORD *)(this + 24) / 2 + v15 - v40 / 2;
        if ( v50[19] )
        {
          rf_render_color_set_packed_rgba8(v50 + 16);
          rf_font_draw_text_screen(
            v41 + 1,
            v38 + 1,
            (unsigned __int8 *)(this + 636),
            *(_DWORD *)(this + 908),
            dword_182ABBC);
        }
        rf_render_color_set_packed_rgba8(v50 + 12);
        rf_font_draw_text_screen(v41, v38, (unsigned __int8 *)(this + 636), *(_DWORD *)(this + 908), dword_182ABBC);
      }
      goto LABEL_70;
    }
    v50 = *(unsigned __int8 **)(this + 912);
    v32 = *(_DWORD *)(this + 24);
    v28 = *(_DWORD *)(this + 20);
    v24 = rf_ui_gadget_absolute_y((_DWORD *)this, 0);
    v16 = rf_ui_gadget_absolute_x((_DWORD *)this, 0);
    if ( rf_ui_state_image_draw((int *)(this + 916), v16, v24, v28, v32, -1, -1) )
    {
      if ( (*(_DWORD *)(this + 628) & 8) != 0 )
        rf_ui_gadget_draw_inset_solid_face((_DWORD *)this, *((_DWORD *)v50 + 2), 0);
      goto LABEL_66;
    }
    if ( (*(_DWORD *)(this + 628) & 4) != 0 )
      goto LABEL_61;
    if ( (*(_DWORD *)(this + 628) & 0x20) != 0 )
    {
      rf_ui_gadget_draw_sunken_face((int *)this, v50, 2);
      v51 = 1;
    }
    else
    {
      if ( (*(_DWORD *)(this + 628) & 1) != 0 )
      {
LABEL_61:
        rf_ui_gadget_draw_inset_solid_face((_DWORD *)this, *((_DWORD *)v50 + 2), 0);
        goto LABEL_66;
      }
      rf_ui_gadget_draw_raised_face((int *)this, v50, 2);
    }
LABEL_66:
    if ( this + 636 + strlen((const char *)(this + 636)) + 1 != this + 637 )
    {
      rf_font_measure_text_extent(&v35, &v36, (unsigned __int8 *)(this + 636), -1, *(_DWORD *)(this + 908));
      v17 = rf_font_get_height_select_current(*(_DWORD *)(this + 908));
      v18 = rf_font_get_spacing_select_current(*(_DWORD *)(this + 908));
      v36 -= v17 - v18 - 1;
      v19 = rf_ui_gadget_absolute_x((_DWORD *)this, 0);
      v37 = v51 + *(_DWORD *)(this + 20) / 2 + v19 - v35 / 2;
      v20 = rf_ui_gadget_absolute_y((_DWORD *)this, 0);
      v34 = v51 + *(_DWORD *)(this + 24) / 2 + v20 - v36 / 2;
      if ( v50[19] )
      {
        rf_render_color_set_packed_rgba8(v50 + 16);
        rf_font_draw_text_screen(
          v37 + 1,
          v34 + 1,
          (unsigned __int8 *)(this + 636),
          *(_DWORD *)(this + 908),
          dword_182ABBC);
      }
      rf_render_color_set_packed_rgba8(v50 + 12);
      rf_font_draw_text_screen(v37, v34, (unsigned __int8 *)(this + 636), *(_DWORD *)(this + 908), dword_182ABBC);
    }
    goto LABEL_70;
  }
}

