// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1490 rf_ui_draw_beveled_rect_edges
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Cdecl args x,y,w,h,topLeftRGBA,bottomRightRGBA,thickness,inset. Starts left=x+inset,top=y+inset,right=x+w-inset-1,bottom=y+h-inset-1. For each nonzero thickness postdecrement,draws bottom and right in second color,then top and left in first color;advances left/top by1 and right/bottom by-1. Uses line render flag0x187CC5C;does not fill rectangle,clamp geometry,restore color or reject negative thickness (which keeps looping through integer wrap). Return is incidental coordinate value,not success.
int __cdecl rf_ui_draw_beveled_rect_edges(
        int a1,
        int a2,
        int a3,
        int a4,
        unsigned __int8 *a5,
        unsigned __int8 *a6,
        int a7,
        int a8)
{
  int result; // eax
  float v10; // [esp+0h] [ebp-24h]
  float v11; // [esp+0h] [ebp-24h]
  float v12; // [esp+4h] [ebp-20h]
  float v13; // [esp+4h] [ebp-20h]
  float v14; // [esp+8h] [ebp-1Ch]
  float v15; // [esp+8h] [ebp-1Ch]
  float v16; // [esp+8h] [ebp-1Ch]
  float v17; // [esp+8h] [ebp-1Ch]
  float v18; // [esp+Ch] [ebp-18h]
  float v19; // [esp+Ch] [ebp-18h]
  float v20; // [esp+Ch] [ebp-18h]
  float v21; // [esp+Ch] [ebp-18h]
  int v22; // [esp+2Ch] [ebp+8h]
  int i; // [esp+30h] [ebp+Ch]
  int v24; // [esp+34h] [ebp+10h]
  int v25; // [esp+38h] [ebp+14h]

  v24 = a3 + a1 - a8 - 1;
  v25 = a4 + a2 - a8 - 1;
  v22 = a8 + a1;
  result = a8 + a2;
  for ( i = a8 + a2; a7--; ++i )
  {
    rf_render_color_set_packed_rgba8(a6);
    v18 = (float)v25;
    v14 = (float)v24;
    v10 = (float)(v22 + 1);
    rf_renderer_draw_screen_line_clipped(v10, v18, v14, v18, dword_187CC5C);
    v19 = (float)(v25 - 1);
    v15 = (float)v24;
    v12 = (float)(i + 1);
    rf_renderer_draw_screen_line_clipped(v15, v12, v15, v19, dword_187CC5C);
    rf_render_color_set_packed_rgba8(a5);
    v20 = (float)i;
    v16 = (float)v24;
    v11 = (float)v22;
    rf_renderer_draw_screen_line_clipped(v11, v20, v16, v20, dword_187CC5C);
    v21 = (float)v25;
    v17 = (float)v22;
    v13 = (float)(i + 1);
    rf_renderer_draw_screen_line_clipped(v17, v13, v17, v21, dword_187CC5C);
    ++v22;
    result = --v24;
    --v25;
  }
  return result;
}

