// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D3AE0 rf_renderer_draw_screen_line_backend_102
// UNREALRED VERIFIED [renderer-helpers-20261028]: Four float screen-coordinate inputs are converted to integers before0x5D3C70. Binds packed state,textures-1,flushes,and begins primitive2/divisor2. Chooses RGB/current alpha via bytes0x664A3C/3D else white/255; optional channel-sum color filter0x5D2B90. Writes two40-byte GPUvertices through0x5D3C70 and packed color at+16. Emits indices base/base+1,advances localindexcount and globalvertexcursor by2,immediately flushes. Unlike projected-line helper,no conditional RGB premultiplication in this body. No software line clipping; return flush result.
int __cdecl rf_renderer_draw_screen_line_backend_102(float a1, float a2, float a3, float a4, int a5)
{
  int v6; // [esp+0h] [ebp-1Ch] BYREF
  int v7; // [esp+4h] [ebp-18h] BYREF
  int v8; // [esp+8h] [ebp-14h] BYREF
  float *v9; // [esp+Ch] [ebp-10h]
  float *v10; // [esp+10h] [ebp-Ch]
  int v11; // [esp+14h] [ebp-8h]
  int v12; // [esp+18h] [ebp-4h]

  rf_d3d8_bind_textures_and_apply_state(a5, -1, -1);
  rf_renderer_flush_immediate_buffers();
  rf_renderer_begin_immediate_buffers(2, 2);
  if ( byte_664A3C )
  {
    v6 = rf_render_current_red;
    v7 = rf_render_current_green;
    v8 = rf_render_current_blue;
  }
  else
  {
    v8 = 255;
    v7 = 255;
    v6 = 255;
  }
  if ( byte_664A3D )
    v12 = rf_render_current_alpha;
  else
    v12 = 255;
  if ( byte_187CD04 )
    rf_renderer_filter_rgb_from_channel_sum(&v6, &v7, &v8);
  v11 = (unsigned __int8)v8 | ((unsigned __int8)v7 << 8) | ((unsigned __int8)v6 << 16) | ((unsigned __int8)v12 << 24);
  v10 = (float *)(unk_1DAEDB8 + 40 * unk_1E014E8);
  v9 = v10 + 10;
  rf_renderer_setup_screen_line_endpoints(v10, v10 + 10, (int)a1, (int)a2, (int)a3, (int)a4);
  *((_DWORD *)v10 + 4) = v11;
  *((_DWORD *)v9 + 4) = v11;
  *(_WORD *)(unk_1DAEDBC + 2 * unk_1E014EC) = dword_18CCFBC;
  *(_WORD *)(unk_1DAEDBC + 2 * unk_1E014EC + 2) = dword_18CCFBC + 1;
  unk_1E014EC += 2;
  dword_18CCFBC += 2;
  return rf_renderer_flush_immediate_buffers();
}

