// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DCDF0 rf_renderer_draw_four_branch_textured_or_line_ribbon
// UNREALRED VERIFIED [renderer-lighting-20261028]: Arguments effectrecord,explicitviewpoint,deterministicbyte. Fourbranchrecords at+112 stride68 have lifetimefloat+0,pathpointer+4,pointcollection+8. Bitmaphandleatroot+96 determines textured vs linepath; rootflags+92 bit4 chooses glowstate,rootpackedRGBA+104. Texturedpath derives common segmentcount from firstcollectioncount+1,then only renders branches lifetime>0. Starts each strip withcollapsededgepair atbranchpathpoint. ColorRGB scaled by0.5 in deterministicmode,else random0.1..1 and optionally byremaininglife/0.1 when rootflag2 andlife<0.1; alpha retained. Width isroot+64*0.75 deterministic,else random0.5..1*rootwidth. Traverses collectionpoints and terminalpath+36,normalizes segmentdirection,uses suppliedviewpoint edgepair0x4C0210,transforms vertices,submits twotriangles persegment,mask1,then copies edges forward. No
// per-branchcollectionlength consistency guard. Negativebitmap uses worldlinesinstead: sets packedcolor,selects custompackedstate(0,0,0,2,4,0) ifflag4 else0x182ABA0,walks all4branches WITHOUT lifetime>0test,including directstart->end when collectionempty. Returns loopartifact4,not renderedsuccess; no state/color restoration.
int *__cdecl rf_renderer_draw_four_branch_textured_or_line_ribbon(int a1, float *a2, char a3)
{
  int *result; // eax
  float **v4; // eax
  float **v5; // eax
  float **v6; // eax
  const float **v7; // eax
  float *v8; // eax
  const float **v9; // eax
  float *v10; // eax
  float *v11; // [esp+0h] [ebp-1B4h]
  float *v12; // [esp+0h] [ebp-1B4h]
  unsigned int v13; // [esp+4h] [ebp-1B0h]
  unsigned int v14; // [esp+4h] [ebp-1B0h]
  float v15; // [esp+8h] [ebp-1ACh]
  float v16; // [esp+10h] [ebp-1A4h]
  float v17; // [esp+18h] [ebp-19Ch]
  float v18[3]; // [esp+20h] [ebp-194h] BYREF
  float v19[3]; // [esp+2Ch] [ebp-188h] BYREF
  float v20[3]; // [esp+38h] [ebp-17Ch] BYREF
  float v21[3]; // [esp+44h] [ebp-170h] BYREF
  float out_vector[3]; // [esp+50h] [ebp-164h] BYREF
  float v23[3]; // [esp+5Ch] [ebp-158h] BYREF
  float v24[3]; // [esp+68h] [ebp-14Ch] BYREF
  float copy_result[3]; // [esp+74h] [ebp-140h] BYREF
  int v26; // [esp+80h] [ebp-134h] BYREF
  float v27; // [esp+84h] [ebp-130h]
  int v28; // [esp+88h] [ebp-12Ch] BYREF
  float lhs[3]; // [esp+8Ch] [ebp-128h] BYREF
  int v30[4]; // [esp+98h] [ebp-11Ch] BYREF
  float v31[12]; // [esp+A8h] [ebp-10Ch] BYREF
  float v32[12]; // [esp+D8h] [ebp-DCh] BYREF
  float destination[3]; // [esp+108h] [ebp-ACh] BYREF
  float v34[12]; // [esp+114h] [ebp-A0h] BYREF
  float v35[12]; // [esp+144h] [ebp-70h] BYREF
  int v36[3]; // [esp+174h] [ebp-40h] BYREF
  float v37[3]; // [esp+180h] [ebp-34h] BYREF
  int v38[3]; // [esp+18Ch] [ebp-28h] BYREF
  int v39[3]; // [esp+198h] [ebp-1Ch] BYREF
  int j; // [esp+1A4h] [ebp-10h]
  unsigned int v41; // [esp+1A8h] [ebp-Ch] BYREF
  int i; // [esp+1ACh] [ebp-8h]
  int first_dword; // [esp+1B0h] [ebp-4h]

  rf_dword_construct_invalid_minus_one(&v41);
  if ( *(int *)(a1 + 96) >= 0 )
  {
    first_dword = rf_receiver_get_first_dword((void *)(a1 + 120)) + 1;
    rf_vector3_default_construct_noop(v38);
    rf_vector3_default_construct_noop(v36);
    rf_vector3_default_construct_noop(destination);
    rf_vector3_default_construct_noop(v37);
    rf_vector3_default_construct_noop(lhs);
    rf_vector_prefix_construct_noop(v34);
    rf_vector_prefix_construct_noop(v32);
    rf_vector_prefix_construct_noop(v31);
    rf_vector_prefix_construct_noop(v35);
    memset(v34, 0, sizeof(v34));
    memset(v32, 0, sizeof(v32));
    memset(v31, 0, sizeof(v31));
    memset(v35, 0, sizeof(v35));
    v34[7] = 0.0;
    v34[8] = 0.0;
    v32[7] = 1.0;
    v32[8] = 0.0;
    v31[7] = 0.0;
    v31[8] = 1.0;
    v35[7] = 1.0;
    v35[8] = 1.0;
    v35[11] = NAN;
    v31[11] = NAN;
    v32[11] = NAN;
    v34[11] = NAN;
    v39[0] = (int)v32;
    v39[1] = (int)v35;
    v39[2] = (int)v31;
    v30[0] = (int)v32;
    v30[1] = (int)v31;
    v30[2] = (int)v34;
    rf_renderer_set_pending_texture_handles(*(_DWORD *)(a1 + 96), -1);
    result = (int *)(*(_DWORD *)(a1 + 92) & 4);
    if ( result )
      v41 = LODWORD(rf_particle_glow_billboard_render_state);
    else
      v41 = rf_particle_standard_billboard_render_state;
    for ( i = 0; i < 4; ++i )
    {
      if ( *(float *)(a1 + 68 * i + 112) > 0.0 )
      {
        rf_vector_copy(destination, copy_result, *(const float **)(a1 + 68 * i + 116));
        rf_renderer_transform_world_point_backend_wrapper((int)v34, destination);
        rf_renderer_transform_world_point_backend_wrapper((int)v32, destination);
        v28 = *(_DWORD *)(a1 + 104);
        v27 = 0.5;
        if ( !a3 )
        {
          v27 = rf_random_float_range(0.1, 1.0);
          if ( (*(_DWORD *)(a1 + 92) & 2) != 0 && *(float *)(a1 + 68 * i + 112) < 0.1000000014901161 )
            v27 = *(float *)(a1 + 68 * i + 112) / 0.1000000014901161 * v27;
        }
        v17 = (double)(unsigned __int8)v28 * v27;
        LOBYTE(v28) = (int)rf_math_ceil_float(v17);
        v16 = (double)BYTE1(v28) * v27;
        BYTE1(v28) = (int)rf_math_ceil_float(v16);
        v15 = (double)BYTE2(v28) * v27;
        BYTE2(v28) = (int)rf_math_ceil_float(v15);
        rf_render_color_set_packed_rgba8((unsigned __int8 *)&v28);
        if ( a3 )
          v27 = *(float *)(a1 + 64) * 0.75;
        else
          v27 = rf_random_float_range(0.5, 1.0) * *(float *)(a1 + 64);
        for ( j = 0; j < first_dword; ++j )
        {
          if ( j == first_dword - 1 )
          {
            rf_vector_copy(lhs, v24, (const float *)(*(_DWORD *)(a1 + 68 * i + 116) + 36));
          }
          else
          {
            v7 = (const float **)sub_552200((_DWORD *)(a1 + 68 * i + 120), j);
            rf_vector_copy(lhs, v23, *v7);
          }
          if ( j )
          {
            v9 = (const float **)sub_552200((_DWORD *)(a1 + 68 * i + 120), j - 1);
            v10 = rf_vector_subtract(lhs, v20, *v9);
            rf_vector_copy(v37, v19, v10);
          }
          else
          {
            v8 = rf_vector_subtract(lhs, out_vector, *(const float **)(a1 + 68 * i + 116));
            rf_vector_copy(v37, v21, v8);
          }
          rf_vector_normalize(v37);
          v30[3] = (int)v37;
          rf_beam_edge_pair_facing_supplied_viewpoint(a2, (float *)v38, (float *)v36, v37, lhs, v27);
          rf_renderer_transform_world_point_backend_wrapper((int)v31, (float *)v38);
          rf_renderer_transform_world_point_backend_wrapper((int)v35, (float *)v36);
          rf_renderer_submit_immediate_polygon(3, (int)v39, 1, v41, 0, 0.0);
          rf_renderer_submit_immediate_polygon(3, (int)v30, 1, v41, 0, 0.0);
          rf_vector_copy(destination, v18, lhs);
          rf_clip_vertex48_copy_return_destination((int)v34, (int)v31);
          rf_clip_vertex48_copy_return_destination((int)v32, (int)v35);
        }
      }
      result = (int *)(i + 1);
    }
  }
  else
  {
    first_dword = rf_receiver_get_first_dword((void *)(a1 + 120));
    rf_render_color_set_packed_rgba8((unsigned __int8 *)(a1 + 104));
    result = (int *)(*(_DWORD *)(a1 + 92) & 4);
    if ( result )
    {
      result = rf_render_state_pack(&v26, 0, 0, 0, 2, 4, 0);
      v41 = *result;
    }
    else
    {
      v41 = dword_182ABA0;
    }
    for ( i = 0; i < 4; ++i )
    {
      for ( j = 0; j < first_dword; ++j )
      {
        v13 = v41;
        if ( j )
        {
          v11 = *(float **)sub_552200((_DWORD *)(a1 + 68 * i + 120), j);
          v5 = (float **)sub_552200((_DWORD *)(a1 + 68 * i + 120), j - 1);
          rf_debug_draw_world_line_backend_dispatch(*v5, v11, v13);
        }
        else
        {
          v4 = (float **)sub_552200((_DWORD *)(a1 + 68 * i + 120), 0);
          rf_debug_draw_world_line_backend_dispatch(*(float **)(a1 + 68 * i + 116), *v4, v13);
        }
      }
      if ( j )
      {
        v14 = v41;
        v12 = (float *)(*(_DWORD *)(a1 + 68 * i + 116) + 36);
        v6 = (float **)sub_552200((_DWORD *)(a1 + 68 * i + 120), first_dword - 1);
        rf_debug_draw_world_line_backend_dispatch(*v6, v12, v14);
      }
      else
      {
        rf_debug_draw_world_line_backend_dispatch(
          *(float **)(a1 + 68 * i + 116),
          (float *)(*(_DWORD *)(a1 + 68 * i + 116) + 36),
          v41);
      }
      result = (int *)(i + 1);
    }
  }
  return result;
}

