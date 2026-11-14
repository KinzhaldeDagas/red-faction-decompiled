// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00465AC0 rf_browser_animate_and_draw
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Noarg. Reset viewport/draw Mars. Integrate titleX6F51B4 +=speed6F52B8*delta,roundfloat;ordered strict<661E64 or>6F29C4 clamps/stops;equal retains speed,NaN
// bypasses. Write truncated titleX to titlebar+12,draw title/label. MainX6F5194 integrates speed6F52BC;ordered strict<661E58 clamps/stops,ordered>=6F29C8 INCLUDING equality
// clamps/stops;NaN bypasses. Fill black alpha128 panel backing at trunc((mainX+10)*scaleX),scaled(panelY+10,width,height-20),then set panelX/truncate/draw. Status
// priority:trackerActive->querying tracker text;else busy6F51A0->pinging text/progress;else pendingIP->Joining plus server RFString704EC0;else empty. All localized formats use
// unbounded sprintf to stack Buffer. Busy path clamps completed6F5190 only when signed>liveCount (no lower clamp);singleQuery6F52D8 displays0/1 while bar still uses global counts.
// Outer bar logical105x11 at(mainX+295,panelY+21);inner width if liveCount>0 is trunc(scaleX*103/liveCount*completed),otherwise outerWidth-2;fill green then black remainder,with
// integer-pixel1/2 insets and no lower/finiteness clamp. Draw visible rows i0..<visibleRows while signed i+scroll<visibleCount (no negative-scroll guard). Every draw-list control
// virtual0 uses ECXthis/NO stack args;then exactly6 header widgets,selected sort arrow centered via signed truncTowardZero(width-arrowWidth)/2. Finish overlays;no active/input
// gate,network send or color restore.
int rf_browser_animate_and_draw()
{
  const char *v0; // eax
  _DWORD *v1; // eax
  char *v3; // [esp+4h] [ebp-90h]
  int v4; // [esp+10h] [ebp-84h]
  int v5; // [esp+28h] [ebp-6Ch]
  int v6; // [esp+28h] [ebp-6Ch]
  int v7; // [esp+2Ch] [ebp-68h]
  int v8; // [esp+2Ch] [ebp-68h]
  int v9; // [esp+30h] [ebp-64h]
  int v10; // [esp+30h] [ebp-64h]
  int v11; // [esp+34h] [ebp-60h]
  int v12; // [esp+34h] [ebp-60h]
  int i; // [esp+38h] [ebp-5Ch]
  int j; // [esp+38h] [ebp-5Ch]
  int k; // [esp+38h] [ebp-5Ch]
  char Buffer[68]; // [esp+3Ch] [ebp-58h] BYREF
  int v17; // [esp+84h] [ebp-10h]
  int v18; // [esp+88h] [ebp-Ch]
  int v19; // [esp+8Ch] [ebp-8h]
  int v20; // [esp+90h] [ebp-4h]

  rf_renderer_reset_viewport_full_screen();
  rf_ui_draw_scrolling_mars_background();
  unk_6F51B4 = unk_6F52B8 * rf_frame_delta_seconds + unk_6F51B4;
  if ( unk_6F51B4 >= (double)dword_661E64 )
  {
    if ( unk_6F51B4 > (double)unk_6F29C4 )
    {
      unk_6F52B8 = 0.0;
      unk_6F51B4 = (float)unk_6F29C4;
    }
  }
  else
  {
    unk_6F52B8 = 0.0;
    unk_6F51B4 = (float)dword_661E64;
  }
  unk_6F53D0 = (int)unk_6F51B4;
  rf_ui_panel_render_bitmap(dword_6F53C4);
  rf_ui_label_render((int)dword_6F5CE8);
  unk_6F5194 = unk_6F52BC * rf_frame_delta_seconds + unk_6F5194;
  if ( unk_6F5194 >= (double)dword_661E58 )
  {
    if ( unk_6F5194 >= (double)unk_6F29C8 )
    {
      unk_6F52BC = 0.0;
      unk_6F5194 = (float)unk_6F29C8;
    }
  }
  else
  {
    unk_6F52BC = 0.0;
    unk_6F5194 = (float)dword_661E58;
  }
  rf_render_color_set_rgba8(0, 0, 0, 128);
  v17 = (int)((unk_6F5194 + 10.0) * rf_ui_scale_x);
  v18 = (int)((double)(unk_6F548C + 10) * rf_ui_scale_y);
  v20 = (int)((double)unk_6F5490 * rf_ui_scale_x);
  v19 = (int)((double)(unk_6F5494 - 20) * rf_ui_scale_y);
  rf_renderer_fill_rectangle_clipped(v17, v18, v20, v19, dword_182ABB8);
  unk_6F5488 = (int)unk_6F5194;
  rf_ui_panel_render_bitmap(dword_6F547C);
  if ( unk_6F51A2 )
  {
    sprintf(Buffer, unk_88E244);
    rf_ui_modal_text_surface_initialize(dword_6F5A20, Buffer, unk_6F29AC);
  }
  else if ( unk_6F51A0 )
  {
    if ( dword_6F5190 > dword_6F51A8 )
      dword_6F5190 = dword_6F51A8;
    if ( unk_6F52D8 )
    {
      sprintf(Buffer, unk_88E248, 0, 1);
    }
    else
    {
      if ( dword_6F5190 >= dword_6F51A8 )
        v4 = dword_6F51A8;
      else
        v4 = dword_6F5190;
      sprintf(Buffer, unk_88E248, v4, dword_6F51A8 < 0 ? 0 : dword_6F51A8);
    }
    rf_ui_modal_text_surface_initialize(dword_6F5A20, Buffer, unk_6F29AC);
    rf_render_color_set_rgba8(128, 128, 128, 255);
    v5 = (int)((unk_6F5194 + 295.0) * rf_ui_scale_x);
    v7 = (int)((double)(unk_6F548C + 21) * rf_ui_scale_y);
    v11 = (int)(rf_ui_scale_x * 105.0);
    v9 = (int)(rf_ui_scale_y * 11.0);
    rf_renderer_fill_rectangle_clipped(v5, v7, v11, v9, dword_182ABB8);
    v6 = v5 + 1;
    v8 = v7 + 1;
    v12 = v11 - 2;
    v10 = v9 - 2;
    if ( dword_6F51A8 > 0 )
      v12 = (int)(rf_ui_scale_x * 103.0 / (double)dword_6F51A8 * (double)dword_6F5190);
    rf_render_color_set_rgba8(23, 140, 0, 255);
    rf_renderer_fill_rectangle_clipped(v6, v8, v12, v10, dword_182ABB8);
    rf_render_color_set_rgba8(0, 0, 0, 255);
    rf_renderer_fill_rectangle_clipped(v12 + v6, v8, (int)(rf_ui_scale_x * 105.0 - 2.0) - v12, v10, dword_182ABB8);
  }
  else if ( rf_join_pending_ipv4_is_set() )
  {
    v3 = (char *)unk_88E24C;
    v0 = rf_string_object_c_str_or_empty(unk_704EC0);
    sprintf(Buffer, v3, v0);
    rf_ui_modal_text_surface_initialize(dword_6F5A20, Buffer, unk_6F29AC);
  }
  else
  {
    rf_ui_modal_text_surface_initialize(dword_6F5A20, (const char *)&unk_636856, unk_6F29AC);
  }
  rf_ui_label_render((int)dword_6F5A20);
  for ( i = 0; i < unk_6F508C && i + dword_6F52E4 < (int)MEMORY[0x6F5088]; ++i )
    rf_browser_draw_server_row(i + dword_6F52E4, i);
  for ( j = 0; j < rf_receiver_get_first_dword(unk_6F5B90); ++j )
  {
    v1 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F5B90, j);
    (**(void (__thiscall ***)(_DWORD, _DWORD))*v1)(*v1, *v1);
  }
  for ( k = 0; k < 6; ++k )
  {
    rf_ui_label_render((int)&dword_6F55F0[16 * k]);
    if ( k == dword_661FE0 )
    {
      unk_6F5C24 = unk_6F55FC[16 * k] + (unk_6F5604[16 * k] - unk_6F5C2C) / 2;
      rf_ui_image_button_draw((int)&dword_6F5C18);
    }
  }
  return rf_ui_draw_side_bars_and_overlays();
}

