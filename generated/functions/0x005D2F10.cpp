// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D2F10 rf_renderer_blit_bitmap_subrectangle_backend_102
// UNREALRED VERIFIED [renderer-polygons-20261028]: Twelve arguments: bitmap,dstX,dstY,dstW,dstH,srcX,srcY,srcW,srcH,two UV-direction bytes,packedstate. Rejects destination dimensions<1. Queries resolved bitmapdimensions0x576450 and signed tilecount0x5E3880. Trims source right/bottom extents to bitmap bounds,rejecting only when an adjusted extent<=0; no general initialpositive-source or lower-bound clamp. Chooses current RGB/alpha through0x664A3C/3D; if statecache0x1DAE8A0&0xC clear,premultiplies RGB and forces packedalpha255; optional channel-sum filter applies. Single tile binds requestedstate,bitmap and pendingtexture1; checks headroom4vertices/6indices,beginning immediate trianglelist4/divisor3 on overflow. UVs use source region,texture scale0x1E014DC/D0,offsets0x1DAEDD0/D4 and halftexel inset when source/destination extent differs. UV-direction byte1 chooses decreasingU,byte0
// increasingU; V byte1 chooses decreasingV,byte0 increasingV. Destination vertices use viewportoffsets and-0.5 pixelbias,depth0.99,rhw1,color,and duplicateUV into both channels. Emits quadindices(0,1,2)(0,2,3),advances global/localvertexcounts4 and localindexcount6. Multiple tiles instead forces texturemode2,reserves worstcase4*tiles/6*tiles,binds each tile,gets source rectangle0x5E38B0,intersects source region and maps cropped fraction to destination. This branch ignores UV-direction bytes,writes only first UVpair,and uses destination coordinates without viewportoffset/-0.5. Only tests resulting left/top below screenwidth/height0x187CC94/98; no full screen clipping or zero-area rejection. Leaves batch pending; no finalflush. No tilecount,resolverfailure or lock-result validation.
void __cdecl rf_renderer_blit_bitmap_subrectangle_backend_102(
        unsigned int a1,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        char a10,
        char a11,
        int a12)
{
  float v12; // [esp+28h] [ebp-E0h]
  float v13; // [esp+30h] [ebp-D8h]
  float v14; // [esp+34h] [ebp-D4h]
  float v15; // [esp+3Ch] [ebp-CCh]
  float v16; // [esp+40h] [ebp-C8h]
  float v17; // [esp+48h] [ebp-C0h]
  float v18; // [esp+4Ch] [ebp-BCh]
  float v19; // [esp+54h] [ebp-B4h]
  float v20; // [esp+58h] [ebp-B0h]
  float v21; // [esp+5Ch] [ebp-ACh]
  int v22; // [esp+60h] [ebp-A8h]
  float v23; // [esp+64h] [ebp-A4h]
  int v24; // [esp+68h] [ebp-A0h]
  int v25; // [esp+6Ch] [ebp-9Ch] BYREF
  float v26; // [esp+70h] [ebp-98h]
  float v27; // [esp+74h] [ebp-94h]
  int v28; // [esp+78h] [ebp-90h]
  float v29; // [esp+7Ch] [ebp-8Ch]
  int v30; // [esp+80h] [ebp-88h] BYREF
  _DWORD v31[2]; // [esp+84h] [ebp-84h] BYREF
  _WORD *v32; // [esp+8Ch] [ebp-7Ch]
  int v33; // [esp+90h] [ebp-78h] BYREF
  float v34; // [esp+94h] [ebp-74h]
  float v35; // [esp+98h] [ebp-70h]
  int v36; // [esp+9Ch] [ebp-6Ch]
  float v37; // [esp+A0h] [ebp-68h]
  int v38; // [esp+A4h] [ebp-64h]
  float v39; // [esp+A8h] [ebp-60h]
  float v40; // [esp+ACh] [ebp-5Ch]
  float v41; // [esp+B0h] [ebp-58h]
  int i; // [esp+B4h] [ebp-54h]
  _WORD *v43; // [esp+B8h] [ebp-50h]
  float v44; // [esp+BCh] [ebp-4Ch]
  float v45; // [esp+C0h] [ebp-48h]
  int v46; // [esp+C4h] [ebp-44h] BYREF
  int v47; // [esp+C8h] [ebp-40h] BYREF
  float v48; // [esp+CCh] [ebp-3Ch]
  int texture_tile_count; // [esp+D0h] [ebp-38h]
  int v50; // [esp+D4h] [ebp-34h] BYREF
  int v51; // [esp+D8h] [ebp-30h] BYREF
  int v52; // [esp+DCh] [ebp-2Ch]
  float v53; // [esp+E0h] [ebp-28h]
  float v54; // [esp+E4h] [ebp-24h]
  float v55; // [esp+E8h] [ebp-20h]
  float v56; // [esp+ECh] [ebp-1Ch]
  float v57; // [esp+F0h] [ebp-18h]
  float v58; // [esp+F4h] [ebp-14h]
  float v59; // [esp+F8h] [ebp-10h]
  int v60; // [esp+FCh] [ebp-Ch] BYREF
  int v61; // [esp+100h] [ebp-8h]
  unsigned int v62; // [esp+104h] [ebp-4h]

  if ( a4 >= 1 && a5 >= 1 )
  {
    rf_bitmap_get_resolved_dimensions(a1, &v46, &v60);
    texture_tile_count = rf_renderer_bitmap_get_texture_tile_count(a1);
    if ( a8 + a6 <= v46 || (a8 = v46 - a6, v46 - a6 > 0) )
    {
      if ( a9 + a7 <= v60 || (a9 = v60 - a7, v60 - a7 > 0) )
      {
        if ( byte_664A3C )
        {
          v47 = rf_render_current_red;
          v50 = rf_render_current_green;
          v51 = rf_render_current_blue;
        }
        else
        {
          v51 = 255;
          v50 = 255;
          v47 = 255;
        }
        if ( byte_664A3D )
          v61 = rf_render_current_alpha;
        else
          v61 = 255;
        if ( (unk_1DAE8A0 & 0xC) != 0 )
        {
          if ( byte_187CD04 )
            rf_renderer_filter_rgb_from_channel_sum(&v47, &v50, &v51);
          v62 = (unsigned __int8)v51
              | ((unsigned __int8)v50 << 8)
              | ((unsigned __int8)v47 << 16)
              | ((unsigned __int8)v61 << 24);
        }
        else
        {
          v47 = v61 * v47 / 255;
          v50 = v61 * v50 / 255;
          v51 = v61 * v51 / 255;
          if ( byte_187CD04 )
            rf_renderer_filter_rgb_from_channel_sum(&v47, &v50, &v51);
          v62 = (unsigned __int8)v51 | ((unsigned __int8)v50 << 8) | ((unsigned __int8)v47 << 16) | 0xFF000000;
        }
        v53 = 0.0;
        v57 = 0.0;
        if ( texture_tile_count == 1 )
        {
          rf_d3d8_bind_textures_and_apply_state(a12, a1, unk_187CCEC);
          if ( dword_18CCFBC + 4 > 6000 || unk_18CCFC0 + unk_1E014EC + 6 > 10000 )
            rf_renderer_begin_immediate_buffers(4, 3);
          if ( a8 != a4 )
            v53 = 0.5 / (double)v46;
          if ( a9 != a5 )
            v57 = 0.5 / (double)v60;
          if ( a10 )
          {
            v19 = (double)a6 + unk_1DAEDD0;
            v44 = v19 * flt_1E014DC / (double)v46;
            v18 = (double)(a8 + a6) + unk_1DAEDD4;
            v55 = v18 * flt_1E014DC / (double)v46;
          }
          else
          {
            v17 = (double)a6 + unk_1DAEDD0;
            v55 = v17 * flt_1E014DC / (double)v46;
            v16 = (double)(a8 + a6) + unk_1DAEDD4;
            v44 = v16 * flt_1E014DC / (double)v46;
          }
          if ( a11 )
          {
            v15 = (double)a7 + unk_1DAEDD0;
            v56 = v15 * flt_1E014D0 / (double)v60;
            v14 = (double)(a9 + a7) + unk_1DAEDD4;
            v45 = v14 * flt_1E014D0 / (double)v60;
          }
          else
          {
            v13 = (double)a7 + unk_1DAEDD0;
            v45 = v13 * flt_1E014D0 / (double)v60;
            v12 = (double)(a9 + a7) + unk_1DAEDD4;
            v56 = v12 * flt_1E014D0 / (double)v60;
          }
          v55 = v55 + v53;
          v44 = v44 - v53;
          v45 = v45 + v57;
          v56 = v56 - v57;
          v48 = (double)(unk_187CCBC + a2) - 0.5;
          v54 = (double)(unk_187CCC0 + a3) - 0.5;
          v58 = (double)(unk_187CCBC + a4 + a2) - 0.5;
          v59 = (double)(unk_187CCC0 + a5 + a3) - 0.5;
          v52 = unk_1DAEDB8 + 40 * unk_1E014E8;
          *(float *)(v52 + 8) = 0.99000001;
          *(float *)(v52 + 12) = 1.0;
          *(_DWORD *)(v52 + 16) = v62;
          *(float *)v52 = v48;
          *(float *)(v52 + 4) = v54;
          *(float *)(v52 + 24) = v55;
          *(float *)(v52 + 28) = v45;
          *(float *)(v52 + 32) = v55;
          *(float *)(v52 + 36) = v45;
          v52 += 40;
          *(float *)(v52 + 8) = 0.99000001;
          *(float *)(v52 + 12) = 1.0;
          *(_DWORD *)(v52 + 16) = v62;
          *(float *)v52 = v58;
          *(float *)(v52 + 4) = v54;
          *(float *)(v52 + 24) = v44;
          *(float *)(v52 + 28) = v45;
          *(float *)(v52 + 32) = v44;
          *(float *)(v52 + 36) = v45;
          v52 += 40;
          *(float *)(v52 + 8) = 0.99000001;
          *(float *)(v52 + 12) = 1.0;
          *(_DWORD *)(v52 + 16) = v62;
          *(float *)v52 = v58;
          *(float *)(v52 + 4) = v59;
          *(float *)(v52 + 24) = v44;
          *(float *)(v52 + 28) = v56;
          *(float *)(v52 + 32) = v44;
          *(float *)(v52 + 36) = v56;
          v52 += 40;
          *(float *)(v52 + 8) = 0.99000001;
          *(float *)(v52 + 12) = 1.0;
          *(_DWORD *)(v52 + 16) = v62;
          *(float *)v52 = v48;
          *(float *)(v52 + 4) = v59;
          *(float *)(v52 + 24) = v55;
          *(float *)(v52 + 28) = v56;
          *(float *)(v52 + 32) = v55;
          *(float *)(v52 + 36) = v56;
          v43 = (_WORD *)(unk_1DAEDBC + 2 * unk_1E014EC);
          *v43 = dword_18CCFBC;
          v43[1] = dword_18CCFBC + 1;
          v43[2] = dword_18CCFBC + 2;
          v43[3] = dword_18CCFBC;
          v43[4] = dword_18CCFBC + 2;
          v43[5] = dword_18CCFBC + 3;
          dword_18CCFBC += 4;
          unk_1E014E8 += 4;
          unk_1E014EC += 6;
        }
        else
        {
          rf_render_state_set_texture_mode(&a12, 2);
          rf_d3d8_bind_textures_and_apply_state(a12, a1, unk_187CCEC);
          if ( dword_18CCFBC + 4 * texture_tile_count > 6000
            || 6 * texture_tile_count + unk_1E014EC + unk_18CCFC0 > 10000 )
          {
            rf_renderer_begin_immediate_buffers(4, 3);
          }
          for ( i = 0; i < texture_tile_count; ++i )
          {
            rf_renderer_bind_texture_handle(0, a1, i, (int)&flt_1E014DC, (int)&flt_1E014D0, 1);
            rf_renderer_bitmap_get_texture_tile_rectangle(a1, i, &v30, &v25, &v33, v31);
            if ( v33 + v30 >= a6 && v30 < a8 + a6 && v31[0] + v25 >= a7 && v25 < a9 + a7 )
            {
              if ( a8 != a4 )
                v53 = 0.5 / (double)v33;
              if ( a9 != a5 )
                v57 = 0.5 / (double)v31[0];
              if ( v30 >= a6 )
              {
                v28 = 0;
                v22 = v33;
              }
              else
              {
                v28 = a6 - v30;
                v22 = v33 - (a6 - v30);
              }
              if ( v33 + v30 > a8 + a6 )
                v22 -= v33 + v30 - (a8 + a6);
              if ( v25 >= a7 )
              {
                v24 = 0;
                v36 = v31[0];
              }
              else
              {
                v24 = a7 - v25;
                v36 = v31[0] - (a7 - v25);
              }
              if ( v31[0] + v25 > a9 + a7 )
                v36 -= v31[0] + v25 - (a9 + a7);
              v23 = (double)v28 / (double)v33 * flt_1E014DC + v53;
              v37 = (double)(v22 + v28) / (double)v33 * flt_1E014DC - v53;
              v20 = (double)v24 / (double)v31[0] * flt_1E014D0 + v57;
              v34 = (double)(v36 + v24) / (double)v31[0] * flt_1E014D0 - v57;
              v38 = v30 + v28;
              v31[1] = v25 + v24;
              v21 = (double)(v30 + v28 - a6) / (double)a8;
              v39 = (double)(v25 + v24 - a7) / (double)a9;
              v29 = (double)(v22 + v30 + v28 - a6) / (double)a8;
              v26 = (double)(v36 + v25 + v24 - a7) / (double)a9;
              v27 = (double)a2 + (double)a4 * v21;
              v35 = (double)a3 + (double)a5 * v39;
              v40 = (double)a2 + (double)a4 * v29;
              v41 = (double)a3 + (double)a5 * v26;
              if ( v27 < (double)dword_187CC94 && v35 < (double)dword_187CC98 )
              {
                v52 = unk_1DAEDB8 + 40 * unk_1E014E8;
                *(float *)(v52 + 8) = 0.99000001;
                *(float *)(v52 + 12) = 1.0;
                *(_DWORD *)(v52 + 16) = v62;
                *(float *)v52 = v27;
                *(float *)(v52 + 4) = v35;
                *(float *)(v52 + 24) = v23;
                *(float *)(v52 + 28) = v20;
                v52 += 40;
                *(float *)(v52 + 8) = 0.99000001;
                *(float *)(v52 + 12) = 1.0;
                *(_DWORD *)(v52 + 16) = v62;
                *(float *)v52 = v40;
                *(float *)(v52 + 4) = v35;
                *(float *)(v52 + 24) = v37;
                *(float *)(v52 + 28) = v20;
                v52 += 40;
                *(float *)(v52 + 8) = 0.99000001;
                *(float *)(v52 + 12) = 1.0;
                *(_DWORD *)(v52 + 16) = v62;
                *(float *)v52 = v40;
                *(float *)(v52 + 4) = v41;
                *(float *)(v52 + 24) = v37;
                *(float *)(v52 + 28) = v34;
                v52 += 40;
                *(float *)(v52 + 8) = 0.99000001;
                *(float *)(v52 + 12) = 1.0;
                *(_DWORD *)(v52 + 16) = v62;
                *(float *)v52 = v27;
                *(float *)(v52 + 4) = v41;
                *(float *)(v52 + 24) = v23;
                *(float *)(v52 + 28) = v34;
                v32 = (_WORD *)(unk_1DAEDBC + 2 * unk_1E014EC);
                *v32 = dword_18CCFBC;
                v32[1] = dword_18CCFBC + 1;
                v32[2] = dword_18CCFBC + 2;
                v32[3] = dword_18CCFBC;
                v32[4] = dword_18CCFBC + 2;
                v32[5] = dword_18CCFBC + 3;
                dword_18CCFBC += 4;
                unk_1E014E8 += 4;
                unk_1E014EC += 6;
              }
            }
          }
        }
      }
    }
  }
}

