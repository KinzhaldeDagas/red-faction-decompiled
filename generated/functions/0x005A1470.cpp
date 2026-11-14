// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A1470 rf_model_render_unskinned_lod_batches
// UNREALRED VERIFIED [character-pipeline-20261029]: cdecl model,LOD mesh,position,orientation,LOD index,render context. Null mesh returns. Flushes pending immediate buffers if flag0x1E014E5,set active0x1E014E6,enters instance transform0x5C5040. Context flags1/8 select special packed states and suppress normal material state/texture/color setup; otherwise material state and stage0 texture applied. Texture table=context+16 override or mesh+32; precomputed RGB=context+28 optional. Mesh WORD+12 batches at pointer+8,stride56: packed state+0,positions+4,normals+8,UVs+12,face planes+16,triangle records+20,duplicate-offset WORDs+24,texture index+32,vertex count WORD+40,triangle count WORD+42. Skips negative texture index,zero triangles or negative texture handle EVEN on special-state paths. Locks shared VB0x1DAEDB0 at40*vertex cursor and IB0x1DAEDB4 at2*index cursor; HRESULTs ignored. Cursors wrap
// to0 if combined reservation exceeds6000 vertices/10000 indices; oversized batch not rejected. Full clipping reserves extra768 vertices AND768 indices. Source vertices subtract active camera origin,transform by view3x3,optionally replace Z with0x18CD380,compute depth-fade BYTE+23,perspective XY,scaled Z+8,RHW+12,UV+24/+28 and BGR+alpha+16..19. Positive signed duplicate offset reuses preceding projected position/fade/color cache; no index validation. If context RGB absent,computes normal lighting via0x5A41D0. Clip configuration: global0x1DAEDA8 forces full clipping;else byte0x663F06 with context flag0x100 chooses full clip,without flag chooses coarse projected-vertex rejection; disabled means neither. Triangles stride8 contain3 WORD indices and flags WORD+6; bit0x20 bypasses face-view rejection. Full clip rejects common outcodes,uses48-byte polygon clip vertices and
// rf_clip_polygon_outcode_planes_48,appends generated vertices,triangulates fan with strict reservation checks. Local clipped index map50 entries has no explicit count limit here. Both buffers unlocked; nonempty index set draws D3D triangle list. Optional context texture+32 and+36 add up to2 repeat passes ONLY during normal material setup. Advances cursors using actual expanded vertices/emitted indices,advances optional RGB across processed batches. On normal completion stores cursors,pops transform,clears active flag. Does not restore every packed/texture state or clear all40 vertex bytes; no global synchronization.
void __cdecl rf_model_render_unskinned_lod_batches(int a1, int a2, float *a3, float *a4, int a5, int a6)
{
  int *v6; // eax
  double v7; // st7
  char v8; // al
  char v9; // al
  double v10; // st7
  double v11; // st7
  char v12; // al
  int *v13; // eax
  _BYTE *v14; // [esp+2Ch] [ebp-3ACh]
  char *v15; // [esp+30h] [ebp-3A8h]
  char *v16; // [esp+34h] [ebp-3A4h]
  int v17; // [esp+38h] [ebp-3A0h]
  bool v18; // [esp+3Ch] [ebp-39Ch]
  bool v19; // [esp+40h] [ebp-398h]
  int v20; // [esp+44h] [ebp-394h]
  int v21; // [esp+48h] [ebp-390h] BYREF
  float v22[3]; // [esp+4Ch] [ebp-38Ch] BYREF
  float copy_result[3]; // [esp+58h] [ebp-380h] BYREF
  int v24; // [esp+64h] [ebp-374h] BYREF
  int v25; // [esp+68h] [ebp-370h]
  _BYTE *v26; // [esp+6Ch] [ebp-36Ch]
  int v27; // [esp+70h] [ebp-368h]
  _BYTE *v28; // [esp+74h] [ebp-364h]
  int v29; // [esp+78h] [ebp-360h]
  int v30; // [esp+7Ch] [ebp-35Ch] BYREF
  char v31[192]; // [esp+80h] [ebp-358h] BYREF
  char v32[144]; // [esp+140h] [ebp-298h] BYREF
  _WORD v33[50]; // [esp+1D0h] [ebp-208h]
  _DWORD v34[48]; // [esp+238h] [ebp-1A0h] BYREF
  int j; // [esp+2F8h] [ebp-E0h]
  float *destination; // [esp+2FCh] [ebp-DCh]
  int v37; // [esp+300h] [ebp-D8h]
  __int16 *v38; // [esp+304h] [ebp-D4h]
  float *v39; // [esp+308h] [ebp-D0h]
  float v40; // [esp+30Ch] [ebp-CCh]
  float v41; // [esp+310h] [ebp-C8h]
  float v42; // [esp+314h] [ebp-C4h]
  _BYTE *v43; // [esp+318h] [ebp-C0h]
  _BYTE *v44; // [esp+31Ch] [ebp-BCh]
  float v45; // [esp+320h] [ebp-B8h]
  _BYTE *v46; // [esp+324h] [ebp-B4h]
  _BYTE *v47; // [esp+328h] [ebp-B0h]
  float *v48; // [esp+32Ch] [ebp-ACh]
  int v49; // [esp+330h] [ebp-A8h]
  float *v50; // [esp+334h] [ebp-A4h]
  char v51[12]; // [esp+338h] [ebp-A0h] BYREF
  int v52; // [esp+344h] [ebp-94h]
  char v53[12]; // [esp+348h] [ebp-90h] BYREF
  float *source; // [esp+354h] [ebp-84h]
  _DWORD *v55; // [esp+358h] [ebp-80h]
  int v56; // [esp+35Ch] [ebp-7Ch]
  _WORD *v57; // [esp+360h] [ebp-78h]
  _WORD *v58; // [esp+364h] [ebp-74h]
  int v59; // [esp+368h] [ebp-70h]
  __int16 *v60; // [esp+36Ch] [ebp-6Ch]
  char v61; // [esp+370h] [ebp-68h] BYREF
  char v62; // [esp+371h] [ebp-67h]
  float *v63; // [esp+374h] [ebp-64h]
  int v64; // [esp+378h] [ebp-60h]
  int v65; // [esp+37Ch] [ebp-5Ch]
  int v66; // [esp+380h] [ebp-58h]
  float v67[3]; // [esp+384h] [ebp-54h] BYREF
  float v68; // [esp+390h] [ebp-48h]
  char v69[4]; // [esp+394h] [ebp-44h] BYREF
  int i; // [esp+398h] [ebp-40h]
  char v71; // [esp+39Fh] [ebp-39h]
  float v72; // [esp+3A0h] [ebp-38h]
  int v73; // [esp+3A4h] [ebp-34h] BYREF
  float v74; // [esp+3A8h] [ebp-30h]
  float v75; // [esp+3ACh] [ebp-2Ch]
  char v76[4]; // [esp+3B0h] [ebp-28h] BYREF
  int v77; // [esp+3B4h] [ebp-24h]
  _BYTE *v78; // [esp+3B8h] [ebp-20h]
  int v79; // [esp+3BCh] [ebp-1Ch]
  _WORD *v80; // [esp+3C0h] [ebp-18h] BYREF
  char v81; // [esp+3C6h] [ebp-12h]
  char v82; // [esp+3C7h] [ebp-11h]
  int v83; // [esp+3C8h] [ebp-10h]
  char v84; // [esp+3CEh] [ebp-Ah]
  char v85; // [esp+3CFh] [ebp-9h]
  int v86; // [esp+3D0h] [ebp-8h]
  bool v87; // [esp+3D7h] [ebp-1h]

  if ( a2 )
  {
    v74 = unk_18CD35C;
    v72 = unk_18CD364;
    v75 = unk_18CD358;
    v68 = unk_18CD360;
    if ( unk_1E014E5 )
      rf_renderer_flush_immediate_buffers();
    unk_1E014E6 = 1;
    v71 = 1;
    v66 = *(_DWORD *)(a6 + 28);
    if ( *(_DWORD *)(a6 + 16) )
      v20 = *(_DWORD *)(a6 + 16);
    else
      v20 = a2 + 32;
    v86 = v20;
    if ( unk_1DAEDA8 )
    {
      v82 = 1;
      v87 = 0;
    }
    else
    {
      v19 = byte_663F06 && (*(_DWORD *)a6 & 0x100) != 0;
      v82 = v19;
      v18 = byte_663F06 && !v82;
      v87 = v18;
    }
    v81 = 0;
    v85 = 0;
    v84 = 0;
    rf_vector3_copy_return_destination(v67, (float *)(a1 + 28));
    rf_vector_rotate_by_matrix3(v67, a4);
    rf_vector_accumulate(v67, a3);
    rf_renderer_push_instance_transform((int)a3, (int)a4);
    if ( (*(_DWORD *)a6 & 1) != 0 )
    {
      rf_renderer_apply_packed_render_state(unk_187CD30);
      v71 = 0;
    }
    else if ( (*(_DWORD *)a6 & 8) != 0 )
    {
      v6 = rf_render_state_pack(&v24, 0, 0, 0, 2, 0, 0);
      rf_renderer_apply_packed_render_state(*v6);
      v71 = 0;
    }
    v79 = unk_18CCFBC;
    v83 = unk_18CCFC0;
    v73 = 0;
    v80 = nullptr;
    v77 = 0;
LABEL_24:
    if ( v77 >= *(unsigned __int16 *)(a2 + 12) )
    {
      unk_18CCFBC = v79;
      unk_18CCFC0 = v83;
      rf_renderer_pop_instance_transform();
      unk_1E014E6 = 0;
      return;
    }
    v55 = (_DWORD *)(*(_DWORD *)(a2 + 8) + 56 * v77);
    if ( (int)v55[8] < 0 || !*((_WORD *)v55 + 21) || *(int *)(v86 + 4 * v55[8]) < 0 )
      goto LABEL_23;
    if ( v71 )
    {
      if ( !rf_packed_state_word_equal(v55, &dword_1E014FC) )
        rf_renderer_apply_packed_render_state(*v55);
      rf_renderer_bind_texture_handle(0, *(_DWORD *)(v86 + 4 * v55[8]), 0, (int)v76, (int)v69, 1);
    }
    v63 = (float *)v55[1];
    v50 = (float *)v55[3];
    v49 = *((unsigned __int16 *)v55 + 20);
    v64 = 3 * *((unsigned __int16 *)v55 + 21);
    v52 = *((unsigned __int16 *)v55 + 20);
    if ( v82 )
    {
      v49 += 768;
      v64 += 768;
    }
    if ( v49 + v79 > 6000 || v64 + v83 > 10000 )
    {
      v79 = 0;
      v83 = 0;
    }
    if ( v79 )
      v17 = unk_1DAEE08;
    else
      v17 = unk_1DAEE04;
    v65 = v17;
    (*(void (__thiscall **)(_DWORD *, _DWORD *, int, int, int *, int))(*dword_1DAEDB0 + 44))(
      dword_1DAEDB0,
      dword_1DAEDB0,
      40 * v79,
      40 * v49,
      &v73,
      v17);
    (*(void (__stdcall **)(_DWORD *, int, int, _WORD **, int))(*dword_1DAEDB4 + 44))(
      dword_1DAEDB4,
      2 * v83,
      2 * v64,
      &v80,
      v65);
    rf_vector3_default_construct_noop(v53);
    rf_vector3_default_construct_noop(v51);
    source = (float *)&unk_1CC86E0;
    v59 = v73;
    v78 = &unk_1C8FC50;
    v60 = (__int16 *)v55[6];
    i = 0;
    while ( i < *((unsigned __int16 *)v55 + 20) )
    {
      if ( *v60 <= 0 )
      {
        *source = *v63 - flt_18CD5E8;
        source[1] = v63[1] - unk_18CD5EC;
        source[2] = v63[2] - unk_18CD5F0;
        v41 = *source * flt_18CD4B4 + source[1] * unk_18CD4B8 + source[2] * unk_18CD4BC;
        v40 = *source * unk_18CD4C0 + source[1] * unk_18CD4C4 + source[2] * unk_18CD4C8;
        v42 = *source * unk_18CD4CC + source[1] * unk_18CD4D0 + source[2] * unk_18CD4D4;
        *source = v41;
        source[1] = v40;
        source[2] = v42;
        if ( !byte_663F39 )
          source[2] = unk_18CD380;
        unk_1C97950[i] = 0;
        if ( v82 )
        {
          v8 = rf_camera_frustum_outcode(source);
          unk_1C97950[i] = v8;
          rf_vector_copy(&flt_1C998E0[3 * i], copy_result, source);
        }
        v9 = rf_renderer_linear_depth_fade_byte(source[2]);
        *(_BYTE *)(v59 + 23) = v9;
        *v78 = *(_BYTE *)(v59 + 23);
        source[2] = 1.0 / source[2];
        v45 = source[2];
        *source = *source * v45 * v74 + v75;
        source[1] = source[1] * v45 * v72 + v68;
        if ( v87
          && (unk_1DAE884 >= (double)*source
           || unk_1DAE88C <= (double)*source
           || unk_1DAE888 >= (double)source[1]
           || unk_1DAE890 <= (double)source[1]
           || source[2] < 0.0) )
        {
          unk_1C97950[i] = 1;
          goto LABEL_42;
        }
        if ( v71 && !*(_DWORD *)(a6 + 28) )
          rf_render_evaluate_three_lights_rgb8(a6, &byte_1C91B90[3 * i], (float *)(v55[2] + 12 * i));
        *(float *)v59 = *source;
        *(float *)(v59 + 4) = source[1];
        v10 = rf_renderer_scale_reciprocal_depth(v45);
        *(float *)(v59 + 8) = v10;
        *(float *)(v59 + 12) = v45 * flt_6649F8;
        if ( v66 )
          v15 = (char *)(v66 + 3 * i);
        else
          v15 = &byte_1C91B90[3 * i];
        v43 = v15;
        v44 = (_BYTE *)(v59 + 16);
        *(_BYTE *)(v59 + 16) = v15[2];
        v44[1] = v43[1];
        v44[2] = *v43;
        v44[3] = *(_BYTE *)(a6 + 8);
      }
      else
      {
        unk_1C97950[i] = unk_1C97950[i - *v60];
        if ( unk_1C97950[i] )
          goto LABEL_42;
        v48 = &source[-3 * *v60];
        *(_BYTE *)(v59 + 23) = v78[-*v60];
        *(float *)v59 = *v48;
        *(float *)(v59 + 4) = v48[1];
        v7 = rf_renderer_scale_reciprocal_depth(v48[2]);
        *(float *)(v59 + 8) = v7;
        *(float *)(v59 + 12) = v48[2] * flt_6649F8;
        if ( v66 )
          v16 = (char *)(v66 + 3 * i);
        else
          v16 = &byte_1C91B90[3 * (i - *v60)];
        v46 = v16;
        v47 = (_BYTE *)(v59 + 16);
        *(_BYTE *)(v59 + 16) = v16[2];
        v47[1] = v46[1];
        v47[2] = *v46;
        v47[3] = *(_BYTE *)(a6 + 8);
      }
      *(float *)(v59 + 24) = *v50;
      *(float *)(v59 + 28) = v50[1];
LABEL_42:
      ++i;
      ++v60;
      source += 3;
      v63 += 3;
      v59 += 40;
      v50 += 2;
      ++v78;
    }
    v56 = 0;
    v57 = v80;
    v58 = &v80[v64];
    for ( i = 0; ; ++i )
    {
      if ( i >= *((unsigned __int16 *)v55 + 21) )
      {
        (*(void (__stdcall **)(_DWORD *))(*dword_1DAEDB0 + 48))(dword_1DAEDB0);
        (*(void (__stdcall **)(_DWORD *))(*dword_1DAEDB4 + 48))(dword_1DAEDB4);
        if ( v66 )
          v66 += 3 * *((unsigned __int16 *)v55 + 20);
        if ( v56 )
        {
          (*(void (__thiscall **)(int, int, int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 284))(
            dword_1DAEDC4,
            dword_1DAEDC4,
            4,
            v79,
            v52,
            v83,
            v56 / 3);
          if ( *(int *)(a6 + 32) >= 0 )
          {
            if ( v71 )
            {
              v13 = rf_render_state_pack(&v21, 2, 1, 2, 2, 1, 3);
              rf_renderer_apply_packed_render_state(*v13);
              rf_renderer_bind_texture_handle(0, *(_DWORD *)(a6 + 32), 0, (int)v76, (int)v69, 1);
              (*(void (__thiscall **)(int, int, int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 284))(
                dword_1DAEDC4,
                dword_1DAEDC4,
                4,
                v79,
                v52,
                v83,
                v56 / 3);
              if ( *(int *)(a6 + 36) >= 0 )
              {
                rf_renderer_bind_texture_handle(0, *(_DWORD *)(a6 + 36), 0, (int)v76, (int)v69, 1);
                (*(void (__thiscall **)(int, int, int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 284))(
                  dword_1DAEDC4,
                  dword_1DAEDC4,
                  4,
                  v79,
                  v52,
                  v83,
                  v56 / 3);
              }
            }
          }
          v79 += v52;
          v83 += v56;
        }
        else
        {
          v79 += v52;
        }
LABEL_23:
        ++v77;
        goto LABEL_24;
      }
      v38 = (__int16 *)(v55[5] + 8 * i);
      v39 = (float *)(v55[4] + 16 * i);
      if ( v87 )
      {
        if ( unk_1C97950[*v38] || unk_1C97950[v38[1]] || unk_1C97950[v38[2]] )
          continue;
      }
      else if ( v82 )
      {
        v62 = unk_1C97950[v38[2]] & unk_1C97950[v38[1]] & unk_1C97950[*v38];
        if ( v62 )
          continue;
      }
      if ( (v38[3] & 0x20) != 0 || rf_renderer_face_view_test_backend_102(v39) )
      {
        if ( !v82 )
          goto LABEL_106;
        v61 = unk_1C97950[v38[2]] | unk_1C97950[v38[1]] | unk_1C97950[*v38];
        if ( !v61 )
        {
          if ( v57 + 3 >= v58 )
            continue;
LABEL_106:
          *v57 = v79 + *v38;
          v57[1] = v79 + v38[1];
          v57[2] = v79 + v38[2];
          v57 += 3;
          v56 += 3;
          continue;
        }
        rf_vector_construct_no_unwind(v32, 0x30u, 3, rf_vector_prefix_construct_noop);
        rf_clip_vertex48_pool_reset();
        v30 = 3;
        destination = (float *)v32;
        j = 0;
        while ( j < 3 )
        {
          v34[j] = destination;
          v29 = v38[j];
          v27 = v29 - *(__int16 *)(v55[6] + 2 * v29);
          rf_vector_copy(destination, v22, &flt_1C998E0[3 * v27]);
          *((_BYTE *)destination + 24) = unk_1C97950[v29];
          *((_BYTE *)destination + 25) = 0;
          *((_BYTE *)destination + 26) = j;
          destination[7] = *(float *)(v55[3] + 8 * v29);
          destination[8] = *(float *)(v55[3] + 8 * v29 + 4);
          if ( v66 )
            v14 = (_BYTE *)(v66 + 3 * v29);
          else
            v14 = &byte_1C91B90[3 * v27];
          v28 = v14;
          *((_BYTE *)destination + 44) = *v14;
          *((_BYTE *)destination + 45) = v28[1];
          *((_BYTE *)destination + 46) = v28[2];
          ++j;
          destination += 12;
        }
        v37 = rf_clip_polygon_outcode_planes_48((int)v34, (int)v31, &v30, &v61, 5);
        if ( v30 >= 3 && !v62 && v30 + v52 < v49 && &v57[3 * v30 - 6] < v58 )
        {
          for ( j = 0; j < v30; ++j )
          {
            if ( (*(_BYTE *)(*(_DWORD *)(v37 + 4 * j) + 25) & 4) != 0 )
            {
              v25 = v73 + 40 * v52;
              v33[j] = v52++;
              destination = *(float **)(v37 + 4 * j);
              rf_renderer_project_clip_vertex_cached((int)destination);
              *(float *)v25 = destination[3];
              *(float *)(v25 + 4) = destination[4];
              destination[5] = 1.0 / destination[2];
              *(float *)(v25 + 12) = destination[5] * flt_6649F8;
              v11 = rf_renderer_scale_reciprocal_depth(destination[5]);
              *(float *)(v25 + 8) = v11;
              v26 = (_BYTE *)(v25 + 16);
              *(_BYTE *)(v25 + 16) = *((_BYTE *)destination + 46);
              v26[1] = *((_BYTE *)destination + 45);
              v26[2] = *((_BYTE *)destination + 44);
              v26[3] = *(_BYTE *)(a6 + 8);
              *(float *)(v25 + 24) = destination[7];
              *(float *)(v25 + 28) = destination[8];
              v12 = rf_renderer_linear_depth_fade_byte(destination[2]);
              *(_BYTE *)(v25 + 23) = v12;
            }
            else
            {
              v33[j] = v38[*(unsigned __int8 *)(*(_DWORD *)(v37 + 4 * j) + 26)];
            }
          }
          for ( j = 0; j < v30 - 2; ++j )
          {
            *v57 = v79 + v33[0];
            v57[1] = v79 + v33[j + 1];
            v57[2] = v79 + v33[j + 2];
            v57 += 3;
            v56 += 3;
          }
        }
      }
    }
  }
}

