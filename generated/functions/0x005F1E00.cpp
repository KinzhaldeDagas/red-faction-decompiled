// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1E00 rf_ui_tooltip_record_draw
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This288-byte tooltip record:owner+8,text+12,font+268,palette+272,offsets276/280,tag284. Measures text with fontID-1 (does not use stored+268 here). Owner kind0 positions relative to gadget absolute coordinates;kind1 uses base raw x/y;other kinds leave coordinates undefined. Initial x/y clamped minimum2,then right/bottom overflow shifts to screenExtent-(textExtent+3)-2 without a second minimum clamp. Draws background textExtent+3 at x,y,paletteRGBA+0;shadow at+2,+2 using palette+8 iff shadow alpha+11;foreground at+1,+1 palette+4. Text draws fontID-1. Returns final text draw result;does not manage lifetime or select tooltip.
int __thiscall rf_ui_tooltip_record_draw(int this)
{
  int v1; // esi
  int v2; // esi
  int v5; // [esp+8h] [ebp-14h] BYREF
  int v6; // [esp+Ch] [ebp-10h] BYREF
  int v7; // [esp+10h] [ebp-Ch] BYREF
  int v8; // [esp+14h] [ebp-8h] BYREF
  int kind; // [esp+18h] [ebp-4h]

  rf_font_measure_text_extent(&v8, &v7, (unsigned __int8 *)(this + 12), -1, -1);
  kind = rf_ui_base_get_kind(*(_DWORD **)(this + 8));
  if ( kind )
  {
    if ( kind == 1 )
    {
      rf_ui_base_get_position(*(_DWORD **)(this + 8), &v5, &v6);
      v5 += *(_DWORD *)(this + 276);
      v6 += *(_DWORD *)(this + 280);
    }
  }
  else
  {
    v5 = *(_DWORD *)(this + 276) + rf_ui_gadget_absolute_x(*(_DWORD **)(this + 8), 0);
    v6 = *(_DWORD *)(this + 280) + rf_ui_gadget_absolute_y(*(_DWORD **)(this + 8), 0);
  }
  if ( v5 < 2 )
    v5 = 2;
  if ( v6 < 2 )
    v6 = 2;
  v1 = v8 + v5;
  if ( v1 > rf_renderer_get_physical_screen_width() - 2 )
    v5 = rf_renderer_get_physical_screen_width() - (v8 + 3) - 2;
  v2 = v7 + v6;
  if ( v2 > rf_renderer_get_physical_screen_height() - 2 )
    v6 = rf_renderer_get_physical_screen_height() - (v7 + 3) - 2;
  rf_render_color_set_packed_rgba8(*(unsigned __int8 **)(this + 272));
  rf_renderer_fill_rectangle_clipped(v5, v6, v8 + 3, v7 + 3, dword_182ABB8);
  if ( *(_BYTE *)(*(_DWORD *)(this + 272) + 11) )
  {
    rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(_DWORD *)(this + 272) + 8));
    rf_font_draw_text_screen(v5 + 2, v6 + 2, (unsigned __int8 *)(this + 12), -1, dword_182ABBC);
  }
  rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(_DWORD *)(this + 272) + 4));
  return rf_font_draw_text_screen(v5 + 1, v6 + 1, (unsigned __int8 *)(this + 12), -1, dword_182ABBC);
}

