// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D3FF0 rf_d3d8_draw_immediate_polygon
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, immediate vertex conversion, face-list lighting, bump-stage calls and original PE bytes): Cdecl count,array of RF48-byte vertex pointers,low-byte flags,packed state. First binds pending stage0 handle187CCE8 and stage1=-1 through5D2C70;negative second handle does not automatically unbind prior stage1. Only converts/appends when immediate-active1E014E5 nonzero. Capacity check: count+globalVertexCursor18CCFBC>6000 OR3*(count-2)+localIndexCount1E014EC+globalIndexCursor18CCFC0>10000 calls begin(4,3);does NOT recheck after fixed-headroom restart or validate one polygon fits. Output vertices40 bytes at mapped1DAEDB8+40*localVertexCount1E014E8:screen x/y from input+12/+16;z=global6649F4*input float+20 roundedfloat;rhw=input+20*6649F8;diffuseARGB+16;specular+20=(depth fade(input cameraZ+8)<<24). Diffuse payload gates664A3C/3D
// set by packed dispatcher:RGB enabled uses gamma-LUT(vertex RGB bytes+44..46) for flag4 else current RGB globals;disabled forces white. Alpha enabled uses vertex byte+47 for flag8 else current alpha;disabled forces255. Optional global187CD04 filters RGB from original channel sum and weights,not alpha;ARGB packs low8bits. Flag1 writes UV0 from input+28/+32 multiplied bound texture scales1E014DC/1E014D0;without it UV0 untouched. Output UV1+32/+36 is ALWAYS untouched in this function. Then triangle-fan appender advances counters;no draw flush here. No count>=3,vertex pointer,lock/HRESULT or oversized-polygon validation. Return AL is apply-state result on inactive path or low byte of new index count on active path,not draw success.
char __cdecl rf_d3d8_draw_immediate_polygon(int a1, const void *const *a2, unsigned __int8 a3, unsigned int a4)
{
  char result; // al
  double v5; // st7
  int v6; // eax
  int v7; // [esp+4h] [ebp-20h] BYREF
  int v8; // [esp+8h] [ebp-1Ch] BYREF
  int v9; // [esp+Ch] [ebp-18h] BYREF
  float *v10; // [esp+10h] [ebp-14h]
  float v11; // [esp+14h] [ebp-10h]
  int v12; // [esp+18h] [ebp-Ch]
  int v13; // [esp+1Ch] [ebp-8h]
  int i; // [esp+20h] [ebp-4h]

  result = rf_d3d8_bind_textures_and_apply_state(a4, unk_187CCE8, -1);
  if ( unk_1E014E5 )
  {
    if ( a1 + dword_18CCFBC > 6000 || 3 * (a1 - 2) + unk_1E014EC + unk_18CCFC0 > 10000 )
      rf_renderer_begin_immediate_buffers(4, 3);
    v13 = unk_1DAEDB8 + 40 * unk_1E014E8;
    for ( i = 0; i < a1; ++i )
    {
      v10 = (float *)a2[i];
      v11 = v10[5];
      v5 = rf_renderer_scale_reciprocal_depth(v10[5]);
      *(float *)(v13 + 8) = v5;
      if ( byte_664A3D )
      {
        if ( (a3 & 8) != 0 )
          v12 = *((unsigned __int8 *)a2[i] + 47);
        else
          v12 = rf_render_current_alpha;
      }
      else
      {
        v12 = 255;
      }
      if ( byte_664A3C )
      {
        if ( (a3 & 4) != 0 )
        {
          v7 = rf_graphics_gamma_lut_u32[*((unsigned __int8 *)a2[i] + 44)];
          v8 = rf_graphics_gamma_lut_u32[*((unsigned __int8 *)a2[i] + 45)];
          v9 = rf_graphics_gamma_lut_u32[*((unsigned __int8 *)a2[i] + 46)];
        }
        else
        {
          v7 = rf_render_current_red;
          v8 = rf_render_current_green;
          v9 = rf_render_current_blue;
        }
      }
      else
      {
        v9 = 255;
        v8 = 255;
        v7 = 255;
      }
      if ( byte_187CD04 )
        rf_renderer_filter_rgb_from_channel_sum(&v7, &v8, &v9);
      *(_DWORD *)(v13 + 16) = (unsigned __int8)v9
                            | ((unsigned __int8)v8 << 8)
                            | ((unsigned __int8)v7 << 16)
                            | ((unsigned __int8)v12 << 24);
      v6 = rf_renderer_linear_depth_fade_byte(v10[2]);
      *(_DWORD *)(v13 + 20) = v6 << 24;
      *(float *)v13 = v10[3];
      *(float *)(v13 + 4) = v10[4];
      *(float *)(v13 + 12) = v11 * flt_6649F8;
      if ( (a3 & 1) != 0 )
      {
        *(float *)(v13 + 24) = v10[7] * flt_1E014DC;
        *(float *)(v13 + 28) = v10[8] * flt_1E014D0;
      }
      v13 += 40;
    }
    return rf_renderer_append_immediate_triangle_fan_indices(a1);
  }
  return result;
}

