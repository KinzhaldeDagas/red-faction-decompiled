// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A2570 rf_character_render_skinned_lod_batches
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, complete skinned draw path, clipping control flow, buffer limits, original x87/integer operations and caller arguments): Complete CPU skinning/clipping/draw path, not merely a morph selector. Cdecl7 stack arguments: LOD-table descriptor,selected LOD mesh,world position,orientation3x3,character instance,LOD index,render context. NULL selected mesh returns immediately. Otherwise conditionally flushes immediate buffers on BYTE1E014E5, sets busy BYTE1E014E6=1, pushes instance transform, and on normal exit commits global vertex/index cursors18CCFBC/18CCFC0, pops transform and clears busy. Texture handles come from context+16 override or mesh+32. Context flags mask1 selects packed global187CD30 and disables lighting/texturing; else mask8 selects packed(0,0,0,2,0,0) and disables lighting/texturing; else packed(1,2,3,3,5,0)
// and lighting enabled. Batch table mesh+8 has56-byte entries,count unsignedWORD mesh+12. Skips negative material index+32,zero face countWORD+42,negative selected texture handle,and failed bind in lit mode; texture-index/handle gates apply even when lighting/texturing is disabled. Only at LOD0,for each eligible batch scans instance record count+4816 with12-byte records at+4820,chooses FIRST whose resolved RFA has morph vertices,calls5A4410 and substitutes shared position scratch18CDA30. No local mix,hold-last,endpoint or record-weight filter; normals remain original batch+8. Positions batch+4,normals+8,UV+12,faces+20,backreferences+24,weights/bones+28,vertex countWORD40,face countWORD42. Positive signed16 backreference reuses vertex j-offset; otherwise skins independently. Each vertex weight record8 contains4 unsigned weight bytes then4 unsigned bone indices; process at most4 and stop at
// first zero weight. Bone affine transform at instance+2400+48*bone applies to BOTH position and normal INCLUDING translation. Weighted sums are multiplied by1/256,not normalized by actual weight sum; normal subsequently normalized only on freshly skinned projected vertices. Positive-reference duplicates copy saved model-space position,outcode,fog byte,projected position and RGB from canonical vertex,but use own UV; nonzero duplicate outcode skips projected-record writes. No backreference/bone/triangle index or scratch-capacity validation. Full clipping enabled unconditionally by global1DAEDA8; otherwise BYTE663F06 plus context flag100h selects full clipping,and BYTE663F06 without100h selects coarse screen rejection. Camera transform uses globals modified by push. Orthographic BYTE663F39==0 replaces camera Z by18CD380 before reciprocal projection. No zero-Z guard. Full clip stores camera
// position/outcode; coarse reject marks vertices on/outside viewport boundaries or negative reciprocal Z. Lighting uses three-light helper5A41D0 unless context flags disabled it; otherwise context RGB12..14. Output vertex40 bytes:XY0/4,scaled inverseZ8,RHW inverseZ*6649F8 at12,BGRA16..19(context alpha8),depth-fade BYTE23,UV24/28; unmentioned fields retained. Reserves original vertex count and3*face count; full clipping adds768 to BOTH capacities. If cursor+reserved exceeds6000 vertices or10000 indices,resets BOTH cursors to0; oversized single batches are not rejected. Locks vertex/index buffers at vtable44 with byte offsets40*vertexCursor and2*indexCursor,chooses global1DAEE04 when vertexCursor0 else1DAEE08,and ignores lock results. Faces are8 bytes:3 signed16 indices and flagsWORD; flag20h bypasses backface test,otherwise model-space cross product and camera-side helper cull. Coarse mode
// drops triangle if ANY outcode nonzero; full mode drops if AND nonzero,direct-emits if OR zero,otherwise invokes48-byte polygon clipping with attribute mask5(UV0+RGB). That wrapper processes planes01..40 only,NOT80. Clipped input positions resolve vertexIndex-minus-signedBackreference; no negative-remap safeguard. Generated vertices get projection,fog,RGB,UV; retained corners reuse original indices. Fan triangles emitted only when resulting count>=3,AND0,usedVertices+polygonCount STRICTLY below reserved vertices,and index end STRICTLY below buffer end. Direct emission in full mode also uses strict3-index end check. Unlocks both buffers at vtable48. Nonempty batch submits triangle-list draw at vtable284 with current vertex base/count,index start and emittedIndexCount/3. In lit mode context texture32>=0 triggers second pass packed(2,1,2,2,1,3),and texture36>=0 triggers third only inside
// that branch; bind return values ignored there. Restores main packed state after extra passes. Advances vertex cursor by actual vertex count even when no faces emitted; index cursor by emitted indices only. Does not restore prior packed state,texture bindings or previous busy byte. Shared global scratch and cursors make this path non-reentrant.
void __cdecl rf_character_render_skinned_lod_batches(int a1, int a2, float *a3, float *a4, int a5, int a6, int a7)
{
  double v7; // st7
  char v8; // al
  char v9; // al
  double v10; // st7
  float *v11; // eax
  double v12; // st7
  char v13; // al
  int *v14; // eax
  float *v15; // [esp+28h] [ebp-424h]
  _BYTE *v16; // [esp+2Ch] [ebp-420h]
  _BYTE *v17; // [esp+30h] [ebp-41Ch]
  _BYTE *v18; // [esp+38h] [ebp-414h]
  int v19; // [esp+3Ch] [ebp-410h]
  bool v20; // [esp+40h] [ebp-40Ch]
  bool v21; // [esp+44h] [ebp-408h]
  int v22; // [esp+48h] [ebp-404h]
  int v23; // [esp+4Ch] [ebp-400h] BYREF
  float v24[3]; // [esp+50h] [ebp-3FCh] BYREF
  float out_vector[3]; // [esp+5Ch] [ebp-3F0h] BYREF
  float v26[3]; // [esp+68h] [ebp-3E4h] BYREF
  float v27[3]; // [esp+74h] [ebp-3D8h] BYREF
  float copy_result[3]; // [esp+80h] [ebp-3CCh] BYREF
  int v29; // [esp+8Ch] [ebp-3C0h] BYREF
  int v30; // [esp+90h] [ebp-3BCh] BYREF
  int v31; // [esp+94h] [ebp-3B8h]
  _BYTE *v32; // [esp+98h] [ebp-3B4h]
  int v33; // [esp+9Ch] [ebp-3B0h]
  _BYTE *v34; // [esp+A0h] [ebp-3ACh]
  int v35; // [esp+A4h] [ebp-3A8h]
  int v36; // [esp+A8h] [ebp-3A4h] BYREF
  _BYTE v37[192]; // [esp+ACh] [ebp-3A0h] BYREF
  char v38[144]; // [esp+16Ch] [ebp-2E0h] BYREF
  _WORD v39[50]; // [esp+1FCh] [ebp-250h]
  _DWORD v40[49]; // [esp+264h] [ebp-1E8h] BYREF
  int k; // [esp+328h] [ebp-124h]
  float *v42; // [esp+32Ch] [ebp-120h]
  int v43; // [esp+330h] [ebp-11Ch]
  float v44[3]; // [esp+334h] [ebp-118h] BYREF
  __int16 *v45; // [esp+340h] [ebp-10Ch]
  float v46; // [esp+344h] [ebp-108h]
  float v47; // [esp+348h] [ebp-104h]
  float v48; // [esp+34Ch] [ebp-100h]
  float v49; // [esp+350h] [ebp-FCh]
  float v50; // [esp+354h] [ebp-F8h]
  float v51; // [esp+358h] [ebp-F4h]
  float v52; // [esp+35Ch] [ebp-F0h]
  float v53; // [esp+360h] [ebp-ECh]
  float v54; // [esp+364h] [ebp-E8h]
  _BYTE *v55; // [esp+368h] [ebp-E4h]
  unsigned __int8 *v56; // [esp+36Ch] [ebp-E0h]
  _BYTE *v57; // [esp+370h] [ebp-DCh]
  _BYTE *v58; // [esp+374h] [ebp-D8h]
  float v59; // [esp+378h] [ebp-D4h]
  _BYTE *v60; // [esp+37Ch] [ebp-D0h]
  _BYTE *v61; // [esp+380h] [ebp-CCh]
  float *v62; // [esp+384h] [ebp-C8h]
  int i; // [esp+388h] [ebp-C4h]
  int v64; // [esp+38Ch] [ebp-C0h]
  float *v65; // [esp+390h] [ebp-BCh]
  float *v66; // [esp+394h] [ebp-B8h]
  float v67; // [esp+398h] [ebp-B4h] BYREF
  float v68; // [esp+39Ch] [ebp-B0h]
  float v69; // [esp+3A0h] [ebp-ACh]
  int v70; // [esp+3A4h] [ebp-A8h]
  float v71; // [esp+3A8h] [ebp-A4h] BYREF
  float v72; // [esp+3ACh] [ebp-A0h]
  float v73; // [esp+3B0h] [ebp-9Ch]
  float *source; // [esp+3B4h] [ebp-98h]
  int v75; // [esp+3B8h] [ebp-94h]
  float *v76; // [esp+3BCh] [ebp-90h]
  int v77; // [esp+3C0h] [ebp-8Ch]
  _WORD *v78; // [esp+3C4h] [ebp-88h]
  unsigned int v79; // [esp+3C8h] [ebp-84h]
  int v80; // [esp+3CCh] [ebp-80h]
  float v81; // [esp+3D0h] [ebp-7Ch]
  int v82; // [esp+3D4h] [ebp-78h]
  __int16 *v83; // [esp+3D8h] [ebp-74h]
  char v84; // [esp+3DCh] [ebp-70h] BYREF
  char v85; // [esp+3DDh] [ebp-6Fh]
  float *v86; // [esp+3E0h] [ebp-6Ch]
  int v87; // [esp+3E4h] [ebp-68h]
  int v88; // [esp+3E8h] [ebp-64h]
  float v89[3]; // [esp+3ECh] [ebp-60h] BYREF
  float v90; // [esp+3F8h] [ebp-54h]
  _BYTE v91[4]; // [esp+3FCh] [ebp-50h] BYREF
  int j; // [esp+400h] [ebp-4Ch]
  char v93; // [esp+407h] [ebp-45h]
  unsigned int v94; // [esp+408h] [ebp-44h] BYREF
  float v95; // [esp+40Ch] [ebp-40h]
  int v96; // [esp+410h] [ebp-3Ch] BYREF
  float v97; // [esp+414h] [ebp-38h]
  float v98; // [esp+418h] [ebp-34h]
  _BYTE v99[4]; // [esp+41Ch] [ebp-30h] BYREF
  int v100; // [esp+420h] [ebp-2Ch]
  _BYTE *v101; // [esp+424h] [ebp-28h]
  int v102; // [esp+428h] [ebp-24h]
  _WORD *v103; // [esp+42Ch] [ebp-20h] BYREF
  float *destination; // [esp+430h] [ebp-1Ch]
  char v105; // [esp+436h] [ebp-16h]
  char v106; // [esp+437h] [ebp-15h]
  int v107; // [esp+438h] [ebp-14h]
  char v108; // [esp+43Eh] [ebp-Eh]
  char v109; // [esp+43Fh] [ebp-Dh]
  int v110; // [esp+440h] [ebp-Ch]
  int v111; // [esp+444h] [ebp-8h]
  bool v112; // [esp+44Bh] [ebp-1h]

  if ( a2 )
  {
    if ( unk_1E014E5 )
      rf_renderer_flush_immediate_buffers();
    unk_1E014E6 = 1;
    v97 = unk_18CD35C;
    v95 = unk_18CD364;
    v98 = unk_18CD358;
    v90 = unk_18CD360;
    v93 = 1;
    if ( *(_DWORD *)(a7 + 16) )
      v22 = *(_DWORD *)(a7 + 16);
    else
      v22 = a2 + 32;
    v111 = v22;
    if ( unk_1DAEDA8 )
    {
      v106 = 1;
      v112 = 0;
    }
    else
    {
      v21 = byte_663F06 && (*(_DWORD *)a7 & 0x100) != 0;
      v106 = v21;
      v20 = byte_663F06 && !v106;
      v112 = v20;
    }
    v105 = 0;
    v109 = 0;
    v108 = 0;
    rf_vector3_copy_return_destination(v89, (float *)(a1 + 28));
    rf_vector_rotate_by_matrix3(v89, a4);
    rf_vector_accumulate(v89, a3);
    rf_renderer_push_instance_transform((int)a3, (int)a4);
    rf_dword_construct_invalid_minus_one(&v94);
    if ( (*(_DWORD *)a7 & 1) != 0 )
    {
      v94 = unk_187CD30;
      v93 = 0;
    }
    else if ( (*(_DWORD *)a7 & 8) != 0 )
    {
      v94 = *rf_render_state_pack(&v30, 0, 0, 0, 2, 0, 0);
      v93 = 0;
    }
    else
    {
      v94 = *rf_render_state_pack(&v29, 1, 2, 3, 3, 5, 0);
    }
    rf_renderer_apply_packed_render_state(v94);
    v102 = unk_18CCFBC;
    v107 = unk_18CCFC0;
    v96 = 0;
    v103 = nullptr;
    v100 = 0;
LABEL_25:
    if ( v100 >= *(unsigned __int16 *)(a2 + 12) )
    {
      unk_18CCFBC = v102;
      unk_18CCFC0 = v107;
      rf_renderer_pop_instance_transform();
      unk_1E014E6 = 0;
      return;
    }
    v75 = *(_DWORD *)(a2 + 8) + 56 * v100;
    if ( *(int *)(v75 + 32) < 0
      || !*(_WORD *)(v75 + 42)
      || *(int *)(v111 + 4 * *(_DWORD *)(v75 + 32)) < 0
      || v93
      && !rf_renderer_bind_texture_handle(0, *(_DWORD *)(v111 + 4 * *(_DWORD *)(v75 + 32)), 0, (int)v99, (int)v91, 1) )
    {
      goto LABEL_24;
    }
    v86 = *(float **)(v75 + 4);
    v76 = *(float **)(v75 + 8);
    v66 = *(float **)(v75 + 12);
    if ( !a6 )
    {
      for ( i = 0; i < *(_DWORD *)(a5 + 4816); ++i )
      {
        v80 = *(_DWORD *)(a5 + 12 * i + 4820);
        if ( rf_rfa_has_morph_vertices(*(void **)(*(_DWORD *)(a5 + 7504) + 4 * v80 + 3932)) )
        {
          rf_character_dispatch_morph_sample(a2, v75, a5, i);
          v86 = (float *)&unk_18CDA30;
          break;
        }
      }
    }
    v64 = *(unsigned __int16 *)(v75 + 40);
    v87 = 3 * *(unsigned __int16 *)(v75 + 42);
    v70 = *(unsigned __int16 *)(v75 + 40);
    if ( v106 )
    {
      v64 += 768;
      v87 += 768;
    }
    if ( v64 + v102 > 6000 || v87 + v107 > 10000 )
    {
      v102 = 0;
      v107 = 0;
    }
    if ( v102 )
      v19 = unk_1DAEE08;
    else
      v19 = unk_1DAEE04;
    v88 = v19;
    (*(void (__stdcall **)(_DWORD *, int, int, int *, int))(*dword_1DAEDB0 + 44))(
      dword_1DAEDB0,
      40 * v102,
      40 * v64,
      &v96,
      v19);
    (*(void (__thiscall **)(_DWORD *, _DWORD *, int, int, _WORD **, int))(*dword_1DAEDB4 + 44))(
      dword_1DAEDB4,
      dword_1DAEDB4,
      2 * v107,
      2 * v87,
      &v103,
      v88);
    rf_vector3_default_construct_noop(&v71);
    rf_vector3_default_construct_noop(&v67);
    source = (float *)&unk_1CC86E0;
    v65 = (float *)&unk_1CDFDE0;
    v83 = *(__int16 **)(v75 + 24);
    v82 = v96;
    v101 = &unk_1C8FC50;
    destination = flt_1CB0FE0;
    j = 0;
    while ( j < *(unsigned __int16 *)(v75 + 40) )
    {
      if ( *v83 <= 0 )
      {
        *source = 0.0;
        source[1] = 0.0;
        source[2] = 0.0;
        *v65 = 0.0;
        v65[1] = 0.0;
        v65[2] = 0.0;
        v57 = (_BYTE *)(*(_DWORD *)(v75 + 28) + 8 * j);
        v56 = (unsigned __int8 *)(*(_DWORD *)(v75 + 28) + 8 * j + 4);
        v110 = 0;
        while ( v110 < 4 && *v57 )
        {
          v81 = (float)(unsigned __int8)*v57;
          v53 = *v86 * *(float *)(a5 + 48 * *v56 + 2400)
              + v86[1] * *(float *)(a5 + 48 * *v56 + 2412)
              + v86[2] * *(float *)(a5 + 48 * *v56 + 2424)
              + *(float *)(a5 + 48 * *v56 + 2436);
          v52 = *v86 * *(float *)(a5 + 48 * *v56 + 2404)
              + v86[1] * *(float *)(a5 + 48 * *v56 + 2416)
              + v86[2] * *(float *)(a5 + 48 * *v56 + 2428)
              + *(float *)(a5 + 48 * *v56 + 2440);
          v54 = *v86 * *(float *)(a5 + 48 * *v56 + 2408)
              + v86[1] * *(float *)(a5 + 48 * *v56 + 2420)
              + v86[2] * *(float *)(a5 + 48 * *v56 + 2432)
              + *(float *)(a5 + 48 * *v56 + 2444);
          v71 = v53;
          v72 = v52;
          v73 = v54;
          v50 = *v76 * *(float *)(a5 + 48 * *v56 + 2400)
              + v76[1] * *(float *)(a5 + 48 * *v56 + 2412)
              + v76[2] * *(float *)(a5 + 48 * *v56 + 2424)
              + *(float *)(a5 + 48 * *v56 + 2436);
          v49 = *v76 * *(float *)(a5 + 48 * *v56 + 2404)
              + v76[1] * *(float *)(a5 + 48 * *v56 + 2416)
              + v76[2] * *(float *)(a5 + 48 * *v56 + 2428)
              + *(float *)(a5 + 48 * *v56 + 2440);
          v51 = *v76 * *(float *)(a5 + 48 * *v56 + 2408)
              + v76[1] * *(float *)(a5 + 48 * *v56 + 2420)
              + v76[2] * *(float *)(a5 + 48 * *v56 + 2432)
              + *(float *)(a5 + 48 * *v56 + 2444);
          v67 = v50;
          v68 = v49;
          v69 = v51;
          *source = v53 * v81 + *source;
          source[1] = v72 * v81 + source[1];
          source[2] = v73 * v81 + source[2];
          *v65 = v67 * v81 + *v65;
          v65[1] = v68 * v81 + v65[1];
          v65[2] = v69 * v81 + v65[2];
          ++v110;
          ++v57;
          ++v56;
        }
        *source = *source * 0.00390625;
        source[1] = source[1] * 0.00390625;
        source[2] = source[2] * 0.00390625;
        *v65 = *v65 * 0.00390625;
        v65[1] = v65[1] * 0.00390625;
        v65[2] = v65[2] * 0.00390625;
        *destination = *source;
        destination[1] = source[1];
        destination[2] = source[2];
        *source = *source - flt_18CD5E8;
        source[1] = source[1] - unk_18CD5EC;
        source[2] = source[2] - unk_18CD5F0;
        v47 = *source * flt_18CD4B4 + source[1] * unk_18CD4B8 + source[2] * unk_18CD4BC;
        v46 = *source * unk_18CD4C0 + source[1] * unk_18CD4C4 + source[2] * unk_18CD4C8;
        v48 = *source * unk_18CD4CC + source[1] * unk_18CD4D0 + source[2] * unk_18CD4D4;
        *source = v47;
        source[1] = v46;
        source[2] = v48;
        if ( !byte_663F39 )
          source[2] = unk_18CD380;
        unk_1C97950[j] = 0;
        if ( v106 )
        {
          v8 = rf_camera_frustum_outcode(source);
          unk_1C97950[j] = v8;
          rf_vector_copy(&flt_1C998E0[3 * j], v27, source);
        }
        v9 = rf_renderer_linear_depth_fade_byte(source[2]);
        *(_BYTE *)(v82 + 23) = v9;
        *v101 = *(_BYTE *)(v82 + 23);
        source[2] = 1.0 / source[2];
        v59 = source[2];
        *source = *source * v59 * v97 + v98;
        source[1] = source[1] * v59 * v95 + v90;
        if ( v112
          && (unk_1DAE884 >= (double)*source
           || unk_1DAE88C <= (double)*source
           || unk_1DAE888 >= (double)source[1]
           || unk_1DAE890 <= (double)source[1]
           || source[2] < 0.0) )
        {
          unk_1C97950[j] = 1;
          goto LABEL_47;
        }
        rf_vector_normalize_reciprocal_sqrt(v65);
        if ( v93 )
          rf_render_evaluate_three_lights_rgb8(a7, &byte_1C91B90[3 * j], v65);
        *(float *)v82 = *source;
        *(float *)(v82 + 4) = source[1];
        v10 = rf_renderer_scale_reciprocal_depth(source[2]);
        *(float *)(v82 + 8) = v10;
        *(float *)(v82 + 12) = source[2] * flt_6649F8;
        if ( v93 )
          v17 = &byte_1C91B90[3 * j];
        else
          v17 = (_BYTE *)(a7 + 12);
        v55 = v17;
        v58 = (_BYTE *)(v82 + 16);
        *(_BYTE *)(v82 + 16) = v17[2];
        v58[1] = v55[1];
        v58[2] = *v55;
        v58[3] = *(_BYTE *)(a7 + 8);
      }
      else
      {
        unk_1C97950[j] = unk_1C97950[j - *v83];
        rf_vector_copy(destination, copy_result, &destination[-3 * *v83]);
        if ( unk_1C97950[j] )
          goto LABEL_47;
        v62 = &source[-3 * *v83];
        *(_BYTE *)(v82 + 23) = v101[-*v83];
        *(float *)v82 = *v62;
        *(float *)(v82 + 4) = v62[1];
        v7 = rf_renderer_scale_reciprocal_depth(v62[2]);
        *(float *)(v82 + 8) = v7;
        *(float *)(v82 + 12) = v62[2] * flt_6649F8;
        if ( v93 )
          v18 = &byte_1C91B90[3 * (j - *v83)];
        else
          v18 = (_BYTE *)(a7 + 12);
        v60 = v18;
        v61 = (_BYTE *)(v82 + 16);
        *(_BYTE *)(v82 + 16) = v18[2];
        v61[1] = v60[1];
        v61[2] = *v60;
        v61[3] = *(_BYTE *)(a7 + 8);
      }
      *(float *)(v82 + 24) = *v66;
      *(float *)(v82 + 28) = v66[1];
LABEL_47:
      ++j;
      ++v83;
      source += 3;
      v65 += 3;
      v86 += 3;
      v76 += 3;
      v82 += 40;
      v66 += 2;
      ++v101;
      destination += 3;
    }
    source = (float *)&unk_1CC86E0;
    v65 = (float *)&unk_1CDFDE0;
    v77 = 0;
    v78 = v103;
    v79 = (unsigned int)&v103[v87];
    for ( j = 0; ; ++j )
    {
      if ( j >= *(unsigned __int16 *)(v75 + 42) )
      {
        (*(void (__stdcall **)(_DWORD *))(*dword_1DAEDB0 + 48))(dword_1DAEDB0);
        (*(void (__stdcall **)(_DWORD *))(*dword_1DAEDB4 + 48))(dword_1DAEDB4);
        if ( v77 )
        {
          (*(void (__thiscall **)(int, int, int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 284))(
            dword_1DAEDC4,
            dword_1DAEDC4,
            4,
            v102,
            v70,
            v107,
            v77 / 3);
          if ( *(int *)(a7 + 32) >= 0 && v93 )
          {
            v14 = rf_render_state_pack(&v23, 2, 1, 2, 2, 1, 3);
            rf_renderer_apply_packed_render_state(*v14);
            rf_renderer_bind_texture_handle(0, *(_DWORD *)(a7 + 32), 0, (int)v99, (int)v91, 1);
            (*(void (__thiscall **)(int, int, int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 284))(
              dword_1DAEDC4,
              dword_1DAEDC4,
              4,
              v102,
              v70,
              v107,
              v77 / 3);
            if ( *(int *)(a7 + 36) >= 0 )
            {
              rf_renderer_bind_texture_handle(0, *(_DWORD *)(a7 + 36), 0, (int)v99, (int)v91, 1);
              (*(void (__thiscall **)(int, int, int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 284))(
                dword_1DAEDC4,
                dword_1DAEDC4,
                4,
                v102,
                v70,
                v107,
                v77 / 3);
            }
            rf_renderer_apply_packed_render_state(v94);
          }
          v102 += v70;
          v107 += v77;
        }
        else
        {
          v102 += v70;
        }
LABEL_24:
        ++v100;
        goto LABEL_25;
      }
      v45 = (__int16 *)(*(_DWORD *)(v75 + 20) + 8 * j);
      if ( v112 )
      {
        if ( unk_1C97950[*v45] || unk_1C97950[v45[1]] || unk_1C97950[v45[2]] )
          continue;
      }
      else if ( v106 )
      {
        v85 = unk_1C97950[v45[2]] & unk_1C97950[v45[1]] & unk_1C97950[*v45];
        if ( v85 )
          continue;
      }
      if ( (v45[3] & 0x20) == 0 )
      {
        v15 = rf_vector_subtract(&flt_1CB0FE0[3 * v45[2]], out_vector, &flt_1CB0FE0[3 * v45[1]]);
        v11 = rf_vector_subtract(&flt_1CB0FE0[3 * v45[1]], v26, &flt_1CB0FE0[3 * *v45]);
        rf_vector_cross(v11, v44, v15);
        if ( !rf_renderer_plane_faces_camera((int)v44, &flt_1CB0FE0[3 * *v45]) )
          continue;
      }
      if ( !v106 )
        goto LABEL_114;
      v84 = unk_1C97950[v45[2]] | unk_1C97950[v45[1]] | unk_1C97950[*v45];
      if ( !v84 )
      {
        if ( (unsigned int)(v78 + 3) >= v79 )
          continue;
LABEL_114:
        *v78 = v102 + *v45;
        v78[1] = v102 + v45[1];
        v78[2] = v102 + v45[2];
        v78 += 3;
        v77 += 3;
        continue;
      }
      rf_vector_construct_no_unwind(v38, 0x30u, 3, rf_vector_prefix_construct_noop);
      rf_clip_vertex48_pool_reset();
      v36 = 3;
      v42 = (float *)v38;
      k = 0;
      while ( k < 3 )
      {
        v40[k] = v42;
        v35 = v45[k];
        v33 = v35 - *(__int16 *)(*(_DWORD *)(v75 + 24) + 2 * v35);
        rf_vector_copy(v42, v24, &flt_1C998E0[3 * v33]);
        *((_BYTE *)v42 + 24) = unk_1C97950[v35];
        *((_BYTE *)v42 + 25) = 0;
        *((_BYTE *)v42 + 26) = k;
        v42[7] = *(float *)(*(_DWORD *)(v75 + 12) + 8 * v35);
        v42[8] = *(float *)(*(_DWORD *)(v75 + 12) + 8 * v35 + 4);
        if ( v93 )
          v16 = &byte_1C91B90[3 * v33];
        else
          v16 = (_BYTE *)(a7 + 12);
        v34 = v16;
        *((_BYTE *)v42 + 44) = *v16;
        *((_BYTE *)v42 + 45) = v34[1];
        *((_BYTE *)v42 + 46) = v34[2];
        ++k;
        v42 += 12;
      }
      v43 = rf_clip_polygon_outcode_planes_48((int)v40, (int)v37, &v36, &v84, 5);
      if ( v36 >= 3 && !v85 && v36 + v70 < v64 && (unsigned int)&v78[3 * v36 - 6] < v79 )
      {
        for ( k = 0; k < v36; ++k )
        {
          if ( (*(_BYTE *)(*(_DWORD *)(v43 + 4 * k) + 25) & 4) != 0 )
          {
            v31 = v96 + 40 * v70;
            v39[k] = v70++;
            v42 = *(float **)(v43 + 4 * k);
            rf_renderer_project_clip_vertex_cached((int)v42);
            *(float *)v31 = v42[3];
            *(float *)(v31 + 4) = v42[4];
            v42[5] = 1.0 / v42[2];
            *(float *)(v31 + 12) = v42[5] * flt_6649F8;
            v12 = rf_renderer_scale_reciprocal_depth(v42[5]);
            *(float *)(v31 + 8) = v12;
            v32 = (_BYTE *)(v31 + 16);
            *(_BYTE *)(v31 + 16) = *((_BYTE *)v42 + 46);
            v32[1] = *((_BYTE *)v42 + 45);
            v32[2] = *((_BYTE *)v42 + 44);
            v32[3] = *(_BYTE *)(a7 + 8);
            *(float *)(v31 + 24) = v42[7];
            *(float *)(v31 + 28) = v42[8];
            v13 = rf_renderer_linear_depth_fade_byte(v42[2]);
            *(_BYTE *)(v31 + 23) = v13;
          }
          else
          {
            v39[k] = v45[*(unsigned __int8 *)(*(_DWORD *)(v43 + 4 * k) + 26)];
          }
        }
        for ( k = 0; k < v36 - 2; ++k )
        {
          *v78 = v102 + v39[0];
          v78[1] = v102 + v39[k + 1];
          v78[2] = v102 + v39[k + 2];
          v78 += 3;
          v77 += 3;
        }
      }
    }
  }
}

