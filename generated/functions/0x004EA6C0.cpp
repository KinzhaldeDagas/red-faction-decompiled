// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EA6C0 rf_player_render_green_scope_overlay
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Current viewport W/H,cx=W>>1,cy=H>>1. Resolve ass2_scope_circle.tga bitmap662FB4; F32 cy/bitmapHeight scale then FTOL scaled dimensions. Lazy87FBAC render state under87FBB0 guard. Fill green(0,180,0,90), green(0,255,0,255) four mirrored quadrants, black side bars. Thirteen rectangle calls include alpha128 thin vertical .70H/horizontal .20W crosshair, four1px descending ticks widths13/11/9/7 at cy+H*(.01/.02/.03/.04), opaque thick bars and15x3 anchor at(cx-7,FTOL(.67H)). Save viewport rectangle, temporarily set x0,y=savedY+FTOL(H*stored .67-20),widthW,height40. Resolve ass2_scope_numbers.tga662FC4; F32 scroll=(bitmapHeight-40)*(RAW player F32+3992-1)/11; white draw at(FTOL(W*stored .52),FTOL(-scroll)), then restore saved
// viewport rectangle and return its helper EAX. Does not call zoom query/clamp, validate player/bitmap dimensions, or restore render color/projection; no split-screen exclusion for number strip.
int __cdecl rf_player_render_green_scope_overlay(int a1)
{
  int v2; // [esp+8h] [ebp-64h] BYREF
  int v3; // [esp+Ch] [ebp-60h]
  int v4; // [esp+10h] [ebp-5Ch] BYREF
  int v5; // [esp+14h] [ebp-58h] BYREF
  int v6; // [esp+18h] [ebp-54h] BYREF
  float v7; // [esp+1Ch] [ebp-50h]
  int v8; // [esp+20h] [ebp-4Ch]
  int viewport_width; // [esp+24h] [ebp-48h]
  int viewport_height; // [esp+28h] [ebp-44h]
  int v11; // [esp+2Ch] [ebp-40h]
  int v12; // [esp+30h] [ebp-3Ch] BYREF
  int v13; // [esp+34h] [ebp-38h]
  int v14; // [esp+38h] [ebp-34h]
  float v15; // [esp+3Ch] [ebp-30h]
  int v16; // [esp+40h] [ebp-2Ch] BYREF
  int v17[2]; // [esp+44h] [ebp-28h] BYREF
  int v18[3]; // [esp+4Ch] [ebp-20h] BYREF
  int v19[2]; // [esp+58h] [ebp-14h] BYREF
  int v20; // [esp+68h] [ebp-4h]

  rf_bitmap_get_resolved_dimensions(dword_662FB4, &v4, v18);
  viewport_width = rf_renderer_get_viewport_width();
  viewport_height = rf_renderer_get_viewport_height();
  v14 = viewport_width >> 1;
  v11 = viewport_height >> 1;
  if ( (dword_87FBB0 & 1) == 0 )
  {
    dword_87FBB0 |= 1u;
    v20 = 0;
    rf_render_state_pack(&dword_87FBAC, 0, 0, 0, 3, 0, 3);
    v20 = -1;
  }
  v7 = (double)v11 / (double)v18[0];
  v3 = (int)((double)v4 * v7);
  v13 = (int)((double)v18[0] * v7);
  v18[2] = 0;
  v18[1] = 180;
  v17[1] = 0;
  rf_render_color_set_rgba8(0, 180, 0, 90);
  rf_renderer_fill_rectangle_clipped(0, 0, viewport_width, viewport_height, dword_87FBAC);
  rf_render_color_set_rgba8(0, 255, 0, 255);
  rf_render_state_pack(&v2, 2, 2, 3, 3, 0, 3);
  rf_bitmap_blit_subrectangle_backend_dispatch(dword_662FB4, v14 - v3, 0, v3, v13, 0, 0, v4, v18[0], 0, 0, v2);
  rf_bitmap_blit_subrectangle_backend_dispatch(dword_662FB4, v14, 0, v3, v13, 0, 0, v4, v18[0], 1, 0, v2);
  rf_bitmap_blit_subrectangle_backend_dispatch(dword_662FB4, v14 - v3, v11, v3, v13, 0, 0, v4, v18[0], 0, 1, v2);
  rf_bitmap_blit_subrectangle_backend_dispatch(dword_662FB4, v14, v11, v3, v13, 0, 0, v4, v18[0], 1, 1, v2);
  rf_render_color_set_rgba8(0, 0, 0, 255);
  rf_renderer_fill_rectangle_clipped(0, 0, v14 - v3, viewport_height, dword_87FBAC);
  rf_renderer_fill_rectangle_clipped(v3 + v14, 0, v14 - v3, viewport_height, dword_87FBAC);
  v8 = 128;
  rf_render_color_set_rgba8(0, 0, 0, 128);
  rf_renderer_fill_rectangle_clipped(
    v14,
    (int)((double)v11 - (double)viewport_height * 0.3499999940395355),
    1,
    (int)((double)viewport_height * 0.699999988079071),
    dword_87FBAC);
  rf_renderer_fill_rectangle_clipped(
    (int)((double)v14 - (double)viewport_width * 0.1000000014901161),
    v11,
    (int)((double)viewport_width * 0.2000000029802322),
    1,
    dword_87FBAC);
  rf_renderer_fill_rectangle_clipped(
    v14 - 6,
    (int)((double)v11 + (double)viewport_height * 0.009999999776482582),
    13,
    1,
    dword_87FBAC);
  rf_renderer_fill_rectangle_clipped(
    v14 - 5,
    (int)((double)v11 + (double)viewport_height * 0.01999999955296516),
    11,
    1,
    dword_87FBAC);
  rf_renderer_fill_rectangle_clipped(
    v14 - 4,
    (int)((double)v11 + (double)viewport_height * 0.02999999932944775),
    9,
    1,
    dword_87FBAC);
  rf_renderer_fill_rectangle_clipped(
    v14 - 3,
    (int)((double)v11 + (double)viewport_height * 0.03999999910593033),
    7,
    1,
    dword_87FBAC);
  rf_render_color_set_rgba8(0, 0, 0, 255);
  rf_renderer_fill_rectangle_clipped(
    v14 - 1,
    (int)((double)v11 + (double)viewport_height * 0.05000000074505806),
    3,
    (int)((double)viewport_height * 0.300000011920929),
    dword_87FBAC);
  rf_renderer_fill_rectangle_clipped(
    (int)((double)v14 - (double)viewport_width * 0.1000000014901161),
    v11 - 1,
    (int)((double)viewport_width * 0.07000000029802322),
    3,
    dword_87FBAC);
  rf_renderer_fill_rectangle_clipped(
    (int)((double)v14 + (double)viewport_width * 0.02999999932944775),
    v11 - 1,
    (int)((double)viewport_width * 0.07000000029802322),
    3,
    dword_87FBAC);
  rf_renderer_fill_rectangle_clipped(v14 - 7, (int)((double)viewport_height * 0.6700000166893005), 15, 3, dword_87FBAC);
  rf_renderer_get_viewport_rectangle(&v12, v19, &v16, &v5);
  rf_renderer_set_viewport_and_relative_clip(
    0,
    v19[0] + (int)((double)viewport_height * 0.6700000166893005 - 20.0),
    viewport_width,
    40);
  rf_bitmap_get_resolved_dimensions(dword_662FC4, &v6, v17);
  v19[1] = v17[0] - 40;
  v15 = (double)(v17[0] - 40) * (*(float *)(a1 + 3992) - 1.0) / 11.0;
  rf_render_color_set_rgba8(255, 255, 255, 255);
  rf_bitmap_draw_unscaled_clipped(dword_662FC4, (int)((double)viewport_width * 0.5199999809265137), (int)-v15, v2);
  return rf_renderer_set_viewport_and_relative_clip(v12, v19[0], v16, v5);
}

