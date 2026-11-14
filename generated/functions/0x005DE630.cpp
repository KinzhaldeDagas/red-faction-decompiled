// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DE630 rf_renderer_draw_camera_plane_beam_quad_padded
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, unowned renderer entry recovery, camera-plane beam geometry and original PE bytes): Cdecl(endpointA,endpointB,width,packedState). If squared endpoint separation<0.001,draws aspect billboard atA,rotation0,width,state;otherwise no general billboard fallback. Uses globals camera position18CD5E8 and direction18CD4CC to compute endpoint signed depths. Both depths<0.16 =>no draw. Behind endpoint replaced using fraction(0.16-depthBehind)/(ABS(depthA)+ABS(depthB)) along original delta,then STORED depth set0.16. This is NOT standard difference-denominator clipping:depths0.1/0.2 give fraction0.2 and actual new depth0.12 while stored depth becomes0.16. Chooses endpoint with smaller stored depth as near. Builds plane through near endpoint with normal=-global direction;intersects UNBOUNDED line from far endpoint along
// normalize(far-camera) with that plane,allowing negative parameter. Normalizes axis=intersection-near;side=cross(-direction,axis). Corners near-halfWidth*axis +/-halfWidth*side and intersection+halfWidth*axis +/-halfWidth*side create padded rectangle in near-endpoint camera plane. UVs(0,0),(1,0),(1,1),(0,1);submits textured world quad using pending bitmap187CCE8,caller state and current RGBA. Failed line-plane intersection draws nothing. No zero-width,finite,unit-camera-direction,projected-axis degeneracy or texture validation. Width not abs/clamped;input endpoint arrays not mutated.
void __cdecl rf_renderer_draw_camera_plane_beam_quad_padded(float *rhs, float *lhs, float a3, int a4)
{
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *v14; // eax
  float *v15; // eax
  float *v16; // eax
  float *v17; // eax
  float *v18; // eax
  float *v19; // eax
  float v20; // [esp+Ch] [ebp-2C8h]
  float v21; // [esp+10h] [ebp-2C4h]
  float v22; // [esp+14h] [ebp-2C0h]
  float v23; // [esp+18h] [ebp-2BCh]
  float v24[3]; // [esp+1Ch] [ebp-2B8h] BYREF
  float v25[3]; // [esp+28h] [ebp-2ACh] BYREF
  float v26[3]; // [esp+34h] [ebp-2A0h] BYREF
  float v27[3]; // [esp+40h] [ebp-294h] BYREF
  float v28[3]; // [esp+4Ch] [ebp-288h] BYREF
  float v29[3]; // [esp+58h] [ebp-27Ch] BYREF
  float v30[3]; // [esp+64h] [ebp-270h] BYREF
  float v31[3]; // [esp+70h] [ebp-264h] BYREF
  float v32[3]; // [esp+7Ch] [ebp-258h] BYREF
  float v33[3]; // [esp+88h] [ebp-24Ch] BYREF
  float v34[3]; // [esp+94h] [ebp-240h] BYREF
  float v35[3]; // [esp+A0h] [ebp-234h] BYREF
  float v36[3]; // [esp+ACh] [ebp-228h] BYREF
  float v37[3]; // [esp+B8h] [ebp-21Ch] BYREF
  float v38[3]; // [esp+C4h] [ebp-210h] BYREF
  float v39[3]; // [esp+D0h] [ebp-204h] BYREF
  float v40[3]; // [esp+DCh] [ebp-1F8h] BYREF
  float v41[3]; // [esp+E8h] [ebp-1ECh] BYREF
  float v42[3]; // [esp+F4h] [ebp-1E0h] BYREF
  float v43[3]; // [esp+100h] [ebp-1D4h] BYREF
  float v44[3]; // [esp+10Ch] [ebp-1C8h] BYREF
  float v45[3]; // [esp+118h] [ebp-1BCh] BYREF
  float v46[3]; // [esp+124h] [ebp-1B0h] BYREF
  float v47[3]; // [esp+130h] [ebp-1A4h] BYREF
  int v48[3]; // [esp+13Ch] [ebp-198h] BYREF
  float v49[3]; // [esp+148h] [ebp-18Ch] BYREF
  float copy_result[3]; // [esp+154h] [ebp-180h] BYREF
  float sum_result[3]; // [esp+160h] [ebp-174h] BYREF
  int v52[3]; // [esp+16Ch] [ebp-168h] BYREF
  float v53[8]; // [esp+178h] [ebp-15Ch] BYREF
  float scaled_result[3]; // [esp+198h] [ebp-13Ch] BYREF
  float scalar; // [esp+1A4h] [ebp-130h]
  float v56[3]; // [esp+1A8h] [ebp-12Ch] BYREF
  float v57[12]; // [esp+1B4h] [ebp-120h] BYREF
  float v58; // [esp+1E4h] [ebp-F0h]
  float v59; // [esp+1E8h] [ebp-ECh]
  float v60; // [esp+1ECh] [ebp-E8h]
  float v61; // [esp+1F0h] [ebp-E4h]
  float v62; // [esp+1F4h] [ebp-E0h]
  float v63; // [esp+1F8h] [ebp-DCh]
  float v64[3]; // [esp+1FCh] [ebp-D8h] BYREF
  float vector[3]; // [esp+208h] [ebp-CCh] BYREF
  float v66[3]; // [esp+214h] [ebp-C0h] BYREF
  float v67[3]; // [esp+220h] [ebp-B4h] BYREF
  float out_vector[3]; // [esp+22Ch] [ebp-A8h] BYREF
  float v69[3]; // [esp+238h] [ebp-9Ch] BYREF
  float v70[3]; // [esp+244h] [ebp-90h] BYREF
  float v71; // [esp+250h] [ebp-84h]
  float v72[3]; // [esp+254h] [ebp-80h] BYREF
  float v73[3]; // [esp+260h] [ebp-74h] BYREF
  float v75[3]; // [esp+270h] [ebp-64h] BYREF
  float v76[3]; // [esp+27Ch] [ebp-58h] BYREF
  float destination[3]; // [esp+288h] [ebp-4Ch] BYREF
  float v78; // [esp+294h] [ebp-40h]
  float *source; // [esp+298h] [ebp-3Ch]
  float v80[3]; // [esp+29Ch] [ebp-38h] BYREF
  float v81[3]; // [esp+2A8h] [ebp-2Ch] BYREF
  float *v82; // [esp+2B4h] [ebp-20h]
  float v83[3]; // [esp+2B8h] [ebp-1Ch] BYREF
  float v84[4]; // [esp+2C4h] [ebp-10h] BYREF

  rf_vector_subtract(lhs, out_vector, rhs);
  if ( rf_vector_length_squared(out_vector) >= 0.001 )
  {
    rf_vector_subtract(rhs, v81, &flt_18CD5E8);
    rf_vector_subtract(lhs, v70, &flt_18CD5E8);
    v78 = rf_vector_dot(v81, &flt_18CD4CC);
    v71 = rf_vector_dot(v70, &flt_18CD4CC);
    rf_vector3_default_construct_noop(destination);
    rf_vector3_default_construct_noop(v75);
    if ( v78 >= 0.1599999964237213 || v71 >= 0.1599999964237213 )
    {
      if ( v78 >= 0.1599999964237213 )
      {
        rf_vector_copy(destination, v49, rhs);
      }
      else
      {
        v23 = fabs(v78);
        v22 = fabs(v71);
        v63 = v23 + v22;
        v61 = 0.1599999964237213 - v78;
        v62 = v61 / v63;
        v4 = rf_vector_scale((float *)v52, v62, out_vector);
        v5 = rf_vector_add(rhs, sum_result, v4);
        rf_vector_copy(destination, copy_result, v5);
        v78 = 0.16;
      }
      if ( v71 >= 0.1599999964237213 )
      {
        rf_vector_copy(v75, v45, lhs);
      }
      else
      {
        v21 = fabs(v78);
        v20 = fabs(v71);
        v60 = v21 + v20;
        v58 = 0.1599999964237213 - v71;
        v59 = v58 / v60;
        v6 = rf_vector_scale((float *)v48, v59, out_vector);
        v7 = rf_vector_subtract(lhs, v47, v6);
        rf_vector_copy(v75, v46, v7);
        v71 = 0.16;
      }
      if ( v71 <= (double)v78 )
      {
        v82 = v75;
        source = destination;
      }
      else
      {
        v82 = destination;
        source = v75;
      }
      rf_matrix3_construct((char *)v64);
      v8 = rf_vector_negate(&flt_18CD4CC, v44);
      rf_vector_copy(v66, v43, v8);
      rf_vector3_default_construct_noop(v69);
      rf_vector3_default_construct_noop(v76);
      rf_vector3_default_construct_noop(v83);
      rf_vector3_default_construct_noop(v67);
      rf_vector3_default_construct_noop(v80);
      rf_vector_prefix_construct_noop(v84);
      rf_force_sample44_construct_vectors_noop((char *)v72);
      rf_plane4_construct_normal_point(v84, v66, v82);
      rf_vector_copy(v72, v42, source);
      v9 = rf_vector_subtract(source, v41, &flt_18CD5E8);
      rf_vector_copy(v73, v40, v9);
      rf_vector_normalize_reciprocal_sqrt(v73);
      if ( rf_line_plane_intersection_unbounded(v72, v84, v80) )
      {
        v10 = rf_vector_subtract(v80, v39, v82);
        rf_vector_copy(v64, v38, v10);
        rf_vector_normalize(v64);
        v11 = rf_vector_cross(v66, v37, v64);
        rf_vector_copy(vector, v36, v11);
        scalar = a3 * 0.5;
        rf_vector_multiply_scalar(vector, scaled_result, scalar);
        rf_vector_multiply_scalar(v64, v56, scalar);
        v12 = rf_vector_subtract(v82, v35, v56);
        v13 = rf_vector_subtract(v12, v34, scaled_result);
        rf_vector_copy(v69, v33, v13);
        v14 = rf_vector_subtract(v82, v32, v56);
        v15 = rf_vector_add(v14, v31, scaled_result);
        rf_vector_copy(v76, v30, v15);
        v16 = rf_vector_add(v80, v29, v56);
        v17 = rf_vector_add(v16, v28, scaled_result);
        rf_vector_copy(v83, v27, v17);
        v18 = rf_vector_add(v80, v26, v56);
        v19 = rf_vector_subtract(v18, v25, scaled_result);
        rf_vector_copy(v67, v24, v19);
        rf_vector_construct_no_unwind((char *)v57, 0xCu, 4, rf_vector3_default_construct_noop);
        rf_vector_construct_no_unwind((char *)v53, 8u, 4, rf_vector3_default_construct_noop);
        v57[0] = v69[0];
        v57[1] = v69[1];
        v57[2] = v69[2];
        v57[3] = v76[0];
        v57[4] = v76[1];
        v57[5] = v76[2];
        v57[6] = v83[0];
        v57[7] = v83[1];
        v57[8] = v83[2];
        v57[9] = v67[0];
        v57[10] = v67[1];
        v57[11] = v67[2];
        v53[0] = 0.0;
        v53[1] = 0.0;
        v53[2] = 1.0;
        v53[3] = 0.0;
        v53[4] = 1.0;
        v53[5] = 1.0;
        v53[6] = 0.0;
        v53[7] = 1.0;
        rf_renderer_submit_textured_world_polygon_rgba(
          dword_187CCE8,
          4,
          (int)v57,
          (int)v53,
          a4,
          rf_render_current_red,
          rf_render_current_green,
          rf_render_current_blue,
          rf_render_current_alpha);
      }
    }
  }
  else
  {
    rf_renderer_world_billboard_aspect_backend_dispatch(rhs, 0.0, a3, a4);
  }
}

