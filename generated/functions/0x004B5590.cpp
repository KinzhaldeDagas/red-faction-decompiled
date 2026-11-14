// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B5590 rf_network_bandwidth_draw_stacked_bar
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, packet registry/function recovery, kill/download routing, native CRC/UI/startup and original geometry
// constants and native signed/x87/stack/callback ABI): cdecl(x,y,width,height,fractionA FLOAT,fractionB FLOAT,outlineColor,fillAColor,fillBColor), nine stack arguments. Sets fillA
// packed color, fills(x,y,trunc(signed width*fractionA),height,style182ABB8). Recomputes SAME truncation to determine second X=x+trunc(width*fractionA); sets fillB, fills second
// width trunc(width*fractionB). Sets outline color and draws outline(x,y,original width,height,style182ABB8), native outline has FIVE arguments despite older decompiler omitting
// style. No fraction clamp, normalization/remainder fill, finite/negative-size check, scaling or color restore; existing integer return incidental.
void __cdecl rf_network_bandwidth_draw_stacked_bar(
        int a1,
        int a2,
        int a3,
        int a4,
        float a5,
        float a6,
        unsigned __int8 *a7,
        unsigned __int8 *a8,
        unsigned __int8 *a9)
{
  rf_render_color_set_packed_rgba8(a8);
  rf_renderer_fill_rectangle_clipped(a1, a2, (int)((double)a3 * a5), a4, dword_182ABB8);
  rf_render_color_set_packed_rgba8(a9);
  rf_renderer_fill_rectangle_clipped(a1 + (int)((double)a3 * a5), a2, (int)((double)a3 * a6), a4, dword_182ABB8);
  rf_render_color_set_packed_rgba8(a7);
  rf_renderer_draw_rectangle_outline_clipped(a1, a2, a3, a4);
}

