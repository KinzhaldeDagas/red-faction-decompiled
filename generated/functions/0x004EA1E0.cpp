// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EA1E0 rf_player_render_red_scope_overlay
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Render against current viewport W/H, signed arithmetic halves cx/cy. Resolve corner bitmap662FB8 scope_zoom_corner256_red.tga dimensions; F32 scale=cy/bitmapHeight, FTOL scaled width/height. Lazy global render state87FBA4 under guard87FBA8 mask1. Fill red(180,0,0,90) whole viewport, white four mirrored corner quadrants, black side bars. Query alt zoom (can reset player zoom), F32 q=zoom/12, R=FTOL(cy*DOUBLE0.5625), L=FTOL(R*q). Draw black alpha64 two-pixel full crosshair, alpha150 four-pixel outer arms ending at cx/cy +/-R, then two-pixel zoom ticks of lengthL extending inward. Thirteen rectangle calls total, no own finite/dimension/negative-rectangle checks. Unless split-screen BYTE nonzero, draw scope_numbers.vbm
// base662FBC at(FTOL(W*stored .71),cy+4) and scope_light.vbm base662FC0 at(FTOL(W*stored .26),cy-3). No own player/local/alive check, viewport/color restoration or texture-loading failure branch. Returns delegated EAX/byte residue, not uniform status.
int __cdecl rf_player_render_red_scope_overlay(int a1)
{
  int v1; // eax
  int result; // eax
  int v3; // [esp+8h] [ebp-6Ch] BYREF
  int v4; // [esp+Ch] [ebp-68h]
  int v5; // [esp+10h] [ebp-64h] BYREF
  int v6; // [esp+14h] [ebp-60h]
  int v7; // [esp+18h] [ebp-5Ch]
  float v8; // [esp+1Ch] [ebp-58h]
  int viewport_width; // [esp+20h] [ebp-54h]
  int viewport_height; // [esp+24h] [ebp-50h]
  int v11; // [esp+28h] [ebp-4Ch]
  float v12; // [esp+2Ch] [ebp-48h]
  int v13; // [esp+30h] [ebp-44h]
  int v14; // [esp+34h] [ebp-40h]
  int v15; // [esp+38h] [ebp-3Ch]
  int v16; // [esp+3Ch] [ebp-38h]
  int v17; // [esp+40h] [ebp-34h]
  int v18; // [esp+44h] [ebp-30h]
  int v19; // [esp+48h] [ebp-2Ch]
  int v20; // [esp+4Ch] [ebp-28h]
  int v21; // [esp+50h] [ebp-24h]
  int v22[3]; // [esp+54h] [ebp-20h] BYREF
  int v23; // [esp+60h] [ebp-14h]
  int v24; // [esp+64h] [ebp-10h]
  int v25; // [esp+70h] [ebp-4h]

  rf_bitmap_get_resolved_dimensions(dword_662FB8, &v5, v22);
  viewport_width = rf_renderer_get_viewport_width();
  viewport_height = rf_renderer_get_viewport_height();
  v16 = viewport_width >> 1;
  v11 = viewport_height >> 1;
  if ( (dword_87FBA8 & 1) == 0 )
  {
    dword_87FBA8 |= 1u;
    v25 = 0;
    rf_render_state_pack(&dword_87FBA4, 0, 0, 0, 3, 0, 3);
    v25 = -1;
  }
  v8 = (double)v11 / (double)v22[0];
  v4 = (int)((double)v5 * v8);
  v14 = (int)((double)v22[0] * v8);
  v24 = 180;
  v22[2] = 0;
  v19 = 0;
  rf_render_color_set_rgba8(180, 0, 0, 90);
  rf_renderer_fill_rectangle_clipped(0, 0, viewport_width, viewport_height, dword_87FBA4);
  rf_render_color_set_rgba8(255, 255, 255, 255);
  rf_render_state_pack(&v3, 2, 2, 3, 3, 0, 3);
  rf_bitmap_blit_subrectangle_backend_dispatch(dword_662FB8, v16 - v4, 0, v4, v14, 0, 0, v5, v22[0], 0, 0, v3);
  rf_bitmap_blit_subrectangle_backend_dispatch(dword_662FB8, v16, 0, v4, v14, 0, 0, v5, v22[0], 1, 0, v3);
  rf_bitmap_blit_subrectangle_backend_dispatch(dword_662FB8, v16 - v4, v11, v4, v14, 0, 0, v5, v22[0], 0, 1, v3);
  rf_bitmap_blit_subrectangle_backend_dispatch(dword_662FB8, v16, v11, v4, v14, 0, 0, v5, v22[0], 1, 1, v3);
  rf_render_color_set_rgba8(0, 0, 0, 255);
  rf_renderer_fill_rectangle_clipped(0, 0, v16 - v4, viewport_height, dword_87FBA4);
  rf_renderer_fill_rectangle_clipped(v4 + v16, 0, v16 - v4, viewport_height, dword_87FBA4);
  v12 = rf_player_query_alt_zoom_factor(a1) / 12.0;
  v1 = (int)((double)v11 * 0.5625);
  v15 = v1;
  v17 = v16 - v1;
  v13 = v11 - v1;
  v23 = (int)((double)v1 * v12);
  v6 = 0;
  v20 = 150;
  v18 = 0;
  v7 = 150;
  v21 = 64;
  v22[1] = 0;
  rf_render_color_set_rgba8(0, 0, 0, 64);
  rf_renderer_fill_rectangle_clipped(v16 - 1, 0, 2, viewport_height, dword_87FBA4);
  rf_renderer_fill_rectangle_clipped(0, v11 - 1, viewport_width, 2, dword_87FBA4);
  rf_render_color_set_rgba8(v6, 0, 0, v20);
  rf_renderer_fill_rectangle_clipped(v16 - 2, 0, 4, v13, dword_87FBA4);
  rf_renderer_fill_rectangle_clipped(v16 - 2, viewport_height - v13, 4, v13, dword_87FBA4);
  rf_renderer_fill_rectangle_clipped(0, v11 - 2, v17, 4, dword_87FBA4);
  rf_renderer_fill_rectangle_clipped(viewport_width - v17, v11 - 2, v17, 4, dword_87FBA4);
  rf_render_color_set_rgba8(v18, 0, 0, v7);
  rf_renderer_fill_rectangle_clipped(v16 - 1, v13, 2, v23, dword_87FBA4);
  rf_renderer_fill_rectangle_clipped(v16 - 1, v15 + v11 - v23, 2, v23, dword_87FBA4);
  rf_renderer_fill_rectangle_clipped(v17, v11 - 1, v23, 2, dword_87FBA4);
  rf_renderer_fill_rectangle_clipped(v15 + v16 - v23, v11 - 1, v23, 2, dword_87FBA4);
  result = rf_splitscreen_runtime_active;
  if ( !rf_splitscreen_runtime_active )
  {
    rf_render_color_set_rgba8(255, 255, 255, 255);
    rf_bitmap_draw_unscaled_clipped(dword_662FBC, (int)((double)viewport_width * 0.7099999785423279), v11 + 4, v3);
    return rf_bitmap_draw_unscaled_clipped(
             dword_662FC0,
             (int)((double)viewport_width * 0.2599999904632568),
             v11 - 3,
             v3);
  }
  return result;
}

