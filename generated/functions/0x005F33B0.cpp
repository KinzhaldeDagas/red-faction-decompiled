// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F33B0 rf_ui_container_draw
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Resets clip,then if label628 empty draws two opposite bevel edge passes only when flags884&1. Nonempty label always draws notched two-color border regardless flags1:label at absoluteX+10,absoluteY-measuredHeight/2+1,font896,optional palette900 shadow+12 alpha15 at+1,+1;foreground+8. Measures label with selected font896. Border spans gadget dimensions,insets0/1;leaves top gap based on measured width plus11/12 andleft segment6/7. Palette edge colors0/4 reversed on paired inner/outer edges. Always calls gadget draw-children-and-event2 helper at end. This function itself has NO hidden/blocked guard before own border/text (children helper may test hidden). No fill,mask rendering or clip restoration;return children helper result.
int __thiscall rf_ui_container_draw(int this)
{
  float v2; // [esp+1Ch] [ebp-B0h]
  float v3; // [esp+20h] [ebp-ACh]
  float v4; // [esp+24h] [ebp-A8h]
  float v5; // [esp+2Ch] [ebp-A0h]
  float v6; // [esp+30h] [ebp-9Ch]
  float v7; // [esp+34h] [ebp-98h]
  float v8; // [esp+38h] [ebp-94h]
  float v9; // [esp+40h] [ebp-8Ch]
  float v10; // [esp+44h] [ebp-88h]
  float v11; // [esp+48h] [ebp-84h]
  float v12; // [esp+4Ch] [ebp-80h]
  float v13; // [esp+50h] [ebp-7Ch]
  float v14; // [esp+58h] [ebp-74h]
  float v15; // [esp+5Ch] [ebp-70h]
  float v16; // [esp+68h] [ebp-64h]
  float v17; // [esp+6Ch] [ebp-60h]
  float v18; // [esp+78h] [ebp-54h]
  float v19; // [esp+80h] [ebp-4Ch]
  float v20; // [esp+84h] [ebp-48h]
  float v21; // [esp+8Ch] [ebp-40h]
  float v22; // [esp+90h] [ebp-3Ch]
  float v24; // [esp+B4h] [ebp-18h]
  int v25; // [esp+B8h] [ebp-14h] BYREF
  int v26; // [esp+BCh] [ebp-10h] BYREF
  float v27; // [esp+C0h] [ebp-Ch]
  float v28; // [esp+C4h] [ebp-8h]
  float v29; // [esp+C8h] [ebp-4h]

  rf_renderer_reset_viewport_full_screen();
  if ( this + 628 + strlen((const char *)(this + 628)) + 1 == this + 629 )
  {
    if ( (*(_DWORD *)(this + 884) & 1) != 0 )
    {
      rf_ui_gadget_draw_bevel_edges(
        (int *)this,
        (unsigned __int8 *)(*(_DWORD *)(this + 900) + 4),
        *(unsigned __int8 **)(this + 900),
        1,
        0);
      rf_ui_gadget_draw_bevel_edges(
        (int *)this,
        *(unsigned __int8 **)(this + 900),
        (unsigned __int8 *)(*(_DWORD *)(this + 900) + 4),
        1,
        1);
    }
  }
  else
  {
    v24 = (float)rf_ui_gadget_absolute_x((_DWORD *)this, 0);
    v27 = (float)rf_ui_gadget_absolute_y((_DWORD *)this, 0);
    rf_font_measure_text_extent(&v25, &v26, (unsigned __int8 *)(this + 628), -1, *(_DWORD *)(this + 896));
    v28 = v24 + 10.0;
    v29 = v27 - (double)(v26 / 2) + 1.0;
    if ( *(_BYTE *)(*(_DWORD *)(this + 900) + 15) )
    {
      rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(_DWORD *)(this + 900) + 12));
      rf_font_draw_text_screen(
        (int)(v28 + 1.0),
        (int)(v29 + 1.0),
        (unsigned __int8 *)(this + 628),
        *(_DWORD *)(this + 896),
        dword_182ABBC);
    }
    rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(_DWORD *)(this + 900) + 8));
    rf_font_draw_text_screen(
      (int)v28,
      (int)v29,
      (unsigned __int8 *)(this + 628),
      *(_DWORD *)(this + 896),
      dword_182ABBC);
    v28 = (double)*(int *)(this + 20) + v24 - 1.0;
    v29 = (double)*(int *)(this + 24) + v27 - 1.0;
    rf_render_color_set_packed_rgba8(*(unsigned __int8 **)(this + 900));
    v22 = v27 + 1.0;
    v21 = v24 + 7.0;
    v20 = v24 + 1.0;
    rf_renderer_draw_screen_line_clipped(v20, v22, v21, v22, dword_187CC5C);
    v19 = v29 - 1.0;
    v18 = v27 + 2.0;
    rf_renderer_draw_screen_line_clipped(v20, v18, v20, v19, dword_187CC5C);
    rf_renderer_draw_screen_line_clipped(v20, v29, v28, v29, dword_187CC5C);
    v17 = v29 - 1.0;
    v16 = v27 + 1.0;
    rf_renderer_draw_screen_line_clipped(v28, v16, v28, v17, dword_187CC5C);
    rf_renderer_draw_screen_line_clipped(v21, v27, v21, v27, dword_187CC5C);
    if ( v28 - 1.0 >= (double)v25 + v24 + 12.0 )
    {
      v15 = v27 + 1.0;
      v14 = v28 - 1.0;
      v13 = (double)v25 + v24 + 12.0;
      rf_renderer_draw_screen_line_clipped(v13, v15, v14, v15, dword_187CC5C);
    }
    rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(_DWORD *)(this + 900) + 4));
    v12 = v24 + 6.0;
    rf_renderer_draw_screen_line_clipped(v24, v27, v12, v27, dword_187CC5C);
    v11 = v27 + 1.0;
    rf_renderer_draw_screen_line_clipped(v24, v11, v24, v29, dword_187CC5C);
    v10 = v29 - 1.0;
    v9 = v28 - 1.0;
    v8 = v24 + 2.0;
    rf_renderer_draw_screen_line_clipped(v8, v10, v9, v10, dword_187CC5C);
    v7 = v29 - 2.0;
    v6 = v28 - 1.0;
    v5 = v27 + 2.0;
    rf_renderer_draw_screen_line_clipped(v6, v5, v6, v7, dword_187CC5C);
    if ( v28 >= (double)v25 + v24 + 11.0 )
    {
      v4 = (double)v25 + v24 + 11.0;
      rf_renderer_draw_screen_line_clipped(v4, v27, v28, v27, dword_187CC5C);
      v3 = v27 + 1.0;
      v2 = (double)v25 + v24 + 11.0;
      rf_renderer_draw_screen_line_clipped(v2, v3, v2, v3, dword_187CC5C);
    }
  }
  return rf_ui_gadget_draw_children_and_notify((_DWORD *)this);
}

