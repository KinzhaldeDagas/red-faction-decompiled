// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D3D90 rf_renderer_draw_projected_line_backend_102
// UNREALRED VERIFIED [renderer-helpers-20261028]: Actual inputs two projected48-byte vertex pointers and packed render state; apparent incoming x87 argument in pseudocode is a decompiler artifact. Binds state with both textures-1,flushes prior immediate batch,begins primitive2/divisor2. Selects current RGB if byte0x664A3C else white; current alpha if0x664A3D else255. If global0x1DAE8A0&0xC clear,premultiplies RGB by alpha/255 and packs output alpha255; otherwise retains alpha. Optional0x5D2B90 color filter follows. Writes two40-byte screen vertices: x/y from source+12/+16,reciprocal-depth+12 from source+20,and depth+8 from x87 result of0x5DF790(source). Writes packed color+16,indices base/base+1,adds2 to local indexcount0x1E014EC and globalvertexcursor0x18CCFBC,then flushes. Does not advance localvertexcursor0x1E014E8 because batch immediately ends. No projection/clipping here; returns
// flush result.
int __usercall rf_renderer_draw_projected_line_backend_102@<eax>(double a1@<st0>, float *a2, float *a3, int a4)
{
  int v5; // [esp+0h] [ebp-1Ch] BYREF
  int v6; // [esp+4h] [ebp-18h]
  int v7; // [esp+8h] [ebp-14h] BYREF
  int v8; // [esp+Ch] [ebp-10h] BYREF
  int v9; // [esp+10h] [ebp-Ch]
  int v10; // [esp+14h] [ebp-8h]
  unsigned int v11; // [esp+18h] [ebp-4h]

  rf_d3d8_bind_textures_and_apply_state(a4, -1, -1);
  rf_renderer_flush_immediate_buffers();
  rf_renderer_begin_immediate_buffers(2, 2);
  if ( byte_664A3C )
  {
    v5 = rf_render_current_red;
    v7 = rf_render_current_green;
    v8 = rf_render_current_blue;
  }
  else
  {
    v8 = 255;
    v7 = 255;
    v5 = 255;
  }
  if ( byte_664A3D )
    v10 = rf_render_current_alpha;
  else
    v10 = 255;
  if ( (unk_1DAE8A0 & 0xC) != 0 )
  {
    if ( byte_187CD04 )
      rf_renderer_filter_rgb_from_channel_sum(&v5, &v7, &v8);
    v11 = (unsigned __int8)v8 | ((unsigned __int8)v7 << 8) | ((unsigned __int8)v5 << 16) | ((unsigned __int8)v10 << 24);
  }
  else
  {
    v5 = v10 * v5 / 255;
    v7 = v10 * v7 / 255;
    v8 = v10 * v8 / 255;
    if ( byte_187CD04 )
      rf_renderer_filter_rgb_from_channel_sum(&v5, &v7, &v8);
    v11 = (unsigned __int8)v8 | ((unsigned __int8)v7 << 8) | ((unsigned __int8)v5 << 16) | 0xFF000000;
  }
  v9 = unk_1DAEDB8 + 40 * unk_1E014E8;
  v6 = v9 + 40;
  rf_renderer_depth_from_vertex_reciprocal((int)a2);
  *(float *)(v9 + 8) = a1;
  rf_renderer_depth_from_vertex_reciprocal((int)a3);
  *(float *)(v6 + 8) = a1;
  *(float *)(v9 + 12) = a2[5];
  *(float *)(v6 + 12) = a3[5];
  *(float *)v9 = a2[3];
  *(float *)(v9 + 4) = a2[4];
  *(float *)v6 = a3[3];
  *(float *)(v6 + 4) = a3[4];
  *(_DWORD *)(v9 + 16) = v11;
  *(_DWORD *)(v6 + 16) = v11;
  *(_WORD *)(unk_1DAEDBC + 2 * unk_1E014EC) = dword_18CCFBC;
  *(_WORD *)(unk_1DAEDBC + 2 * unk_1E014EC + 2) = dword_18CCFBC + 1;
  unk_1E014EC += 2;
  dword_18CCFBC += 2;
  return rf_renderer_flush_immediate_buffers();
}

