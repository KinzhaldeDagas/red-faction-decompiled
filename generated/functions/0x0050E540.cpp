// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050E540 rf_projectile_render_model_bitmap_or_tracer
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile pre/post physics,homing/expiry/render branches,two-argument cone ABI andx87unordered flow,original ECX/stack flow and PE bytes): Render dispatch precedence: nonzero object model+128 always renders model at position+60/matrix+72 using default options561B70; model kind3 first updates VFX(model,frameDelta,1,pos,matrix,1). If info bitmap handle+148>=0, additionally binds(bitmap,-1), sets opaque white and draws zero-angle head-radius+156 billboard using glow render state; model branch ignores bitmap length/random/cycle flags. With no model and valid bitmap, flags+612 mask04000000 (+Length source) draws tapered segment: head=position, tail=position-forward+96*info length+164, head/tail radii+156/+160, state182ABC0, final0; no color setter precedes segment, so current color is inherited. Lazily caches glow01.tga
// in663ACC only when -1 (failed -1 retries); binds glow, sets RGBA255,50,50,100 and draws midpoint billboard radiusF32(headRadius*DOUBLE1.5), same state. Other valid-bitmap case defaults angle0/alpha255; second flags+616 bit2 random_bmp_orient draws angle random0..F32(2pi) each call; bit4 cycle_alpha uses F32 frequency=DOUBLE6.283185482025146/F32(0.2), F32 phase=frequency*global time6FC42C, alpha=FTOL(sin_float(phase)*DOUBLE64+DOUBLE64)+127. Sets white RGB with that alpha, draws radius+156 billboard. With no model AND bitmap<0, only projectile flags+680 bit4 enables tracer path. Nonempty info RFString+1344 requires shared cached model+1352 nonzero: updates VFX(shared,dt,0,NULL,NULL,1), constructs options, writes flags=2 and color+12 opaque white, renders at projectile transform. Empty tracer string instead draws tetrahedron vertices P+U*r, P+R*r-U*r, P-R*r-U*r
// (R=matrix+72,U=+84,r=collision radius+172). Fourth vertex is P-forward*3 when remaining+668 >= info lifetime+176-DOUBLE0.05000000074505806 OR UNORDERED; only ordered less uses prior position+108. No model/bitmap/tracer fallback after a higher-precedence branch, render-state restoration, capacity/finite guards, or reliable AL success return. Default options constructor leaves some color bytes uninitialized; no blanket white initialization of model options here.
char __cdecl rf_projectile_render_model_bitmap_or_tracer(int a1)
{
  char result; // al
  float *v2; // eax
  float *v3; // eax
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
  float *scalar; // [esp+10h] [ebp-1F0h]
  float *scalara; // [esp+10h] [ebp-1F0h]
  float v16; // [esp+14h] [ebp-1ECh]
  float v17; // [esp+18h] [ebp-1E8h]
  float v18[3]; // [esp+1Ch] [ebp-1E4h] BYREF
  float v19[3]; // [esp+28h] [ebp-1D8h] BYREF
  float v20[3]; // [esp+34h] [ebp-1CCh] BYREF
  float v21[3]; // [esp+40h] [ebp-1C0h] BYREF
  float v22[3]; // [esp+4Ch] [ebp-1B4h] BYREF
  float v23[3]; // [esp+58h] [ebp-1A8h] BYREF
  float v24[3]; // [esp+64h] [ebp-19Ch] BYREF
  float v25[3]; // [esp+70h] [ebp-190h] BYREF
  float v26[3]; // [esp+7Ch] [ebp-184h] BYREF
  float v27[3]; // [esp+88h] [ebp-178h] BYREF
  float v28[3]; // [esp+94h] [ebp-16Ch] BYREF
  float v29[3]; // [esp+A0h] [ebp-160h] BYREF
  float v30[3]; // [esp+ACh] [ebp-154h] BYREF
  float v31[3]; // [esp+B8h] [ebp-148h] BYREF
  float copy_result[3]; // [esp+C4h] [ebp-13Ch] BYREF
  float v33[3]; // [esp+D0h] [ebp-130h] BYREF
  float v34[3]; // [esp+DCh] [ebp-124h] BYREF
  float sum_result[3]; // [esp+E8h] [ebp-118h] BYREF
  float scaled_result[3]; // [esp+F4h] [ebp-10Ch] BYREF
  float v37[3]; // [esp+100h] [ebp-100h] BYREF
  float destination[3]; // [esp+10Ch] [ebp-F4h] BYREF
  float v39[3]; // [esp+118h] [ebp-E8h] BYREF
  float v40[3]; // [esp+124h] [ebp-DCh] BYREF
  char v41[12]; // [esp+130h] [ebp-D0h] BYREF
  _BYTE v42[68]; // [esp+13Ch] [ebp-C4h] BYREF
  float v43; // [esp+180h] [ebp-80h]
  float v44; // [esp+184h] [ebp-7Ch]
  float v45; // [esp+188h] [ebp-78h]
  int v46; // [esp+18Ch] [ebp-74h]
  float v47[3]; // [esp+190h] [ebp-70h] BYREF
  float out_vector[3]; // [esp+19Ch] [ebp-64h] BYREF
  char v49[84]; // [esp+1A8h] [ebp-58h] BYREF
  int v50; // [esp+1FCh] [ebp-4h]

  v50 = *(_DWORD *)(a1 + 128);
  if ( v50 )
  {
    if ( rf_model_descriptor_get_kind(v50) == 3 )
      rf_vfx_update_instance((int *)v50, rf_frame_delta_seconds, 1, a1 + 60, a1 + 72, 1);
    rf_model_render_options_construct(v49);
    result = rf_model_handle_render_all_adapter(v50, a1 + 60, a1 + 72, (int)v49);
    if ( *(int *)(*(_DWORD *)(a1 + 660) + 148) >= 0 )
    {
      rf_renderer_set_pending_texture_handles(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 148), -1);
      rf_render_color_set_rgba8(255, 255, 255, 255);
      return rf_renderer_world_billboard_aspect_backend_dispatch(
               a1 + 60,
               0.0,
               *(float *)(*(_DWORD *)(a1 + 660) + 156),
               SLODWORD(rf_particle_glow_billboard_render_state));
    }
  }
  else if ( *(int *)(*(_DWORD *)(a1 + 660) + 148) < 0 )
  {
    result = a1;
    if ( (*(_DWORD *)(a1 + 680) & 4) != 0 )
    {
      if ( rf_string_is_empty((int *)(*(_DWORD *)(a1 + 660) + 1344)) )
      {
        rf_vector3_default_construct_noop(destination);
        rf_vector3_default_construct_noop(v39);
        rf_vector3_default_construct_noop(v37);
        rf_vector3_default_construct_noop(v40);
        v4 = rf_vector_multiply_scalar((const float *)(a1 + 84), v34, *(float *)(*(_DWORD *)(a1 + 660) + 172));
        v5 = rf_vector_add((const float *)(a1 + 60), v33, v4);
        rf_vector_copy(destination, copy_result, v5);
        scalar = rf_vector_multiply_scalar((const float *)(a1 + 84), v29, *(float *)(*(_DWORD *)(a1 + 660) + 172));
        v6 = rf_vector_multiply_scalar((const float *)(a1 + 72), v31, *(float *)(*(_DWORD *)(a1 + 660) + 172));
        v7 = rf_vector_add((const float *)(a1 + 60), v30, v6);
        v8 = rf_vector_subtract(v7, v28, scalar);
        rf_vector_copy(v39, v27, v8);
        scalara = rf_vector_multiply_scalar((const float *)(a1 + 84), v24, *(float *)(*(_DWORD *)(a1 + 660) + 172));
        v9 = rf_vector_multiply_scalar((const float *)(a1 + 72), v26, *(float *)(*(_DWORD *)(a1 + 660) + 172));
        v10 = rf_vector_subtract((const float *)(a1 + 60), v25, v9);
        v11 = rf_vector_subtract(v10, v23, scalara);
        rf_vector_copy(v37, v22, v11);
        if ( *(float *)(a1 + 668) >= *(float *)(*(_DWORD *)(a1 + 660) + 176) - 0.05000000074505806 )
        {
          v12 = rf_vector_multiply_scalar((const float *)(a1 + 96), v20, 3.0);
          v13 = rf_vector_subtract((const float *)(a1 + 60), v19, v12);
          rf_vector_copy(v40, v18, v13);
        }
        else
        {
          rf_vector_copy(v40, v21, (const float *)(a1 + 108));
        }
        return rf_renderer_debug_tetrahedron_backend_wrapper((int)destination, (int)v39, (int)v37, (int)v40);
      }
      else
      {
        result = a1;
        if ( *(_DWORD *)(*(_DWORD *)(a1 + 660) + 1352) )
        {
          rf_vfx_update_instance(*(int **)(*(_DWORD *)(a1 + 660) + 1352), rf_frame_delta_seconds, 0, 0, 0, 1);
          rf_model_render_options_construct(v41);
          *(_DWORD *)v41 = 2;
          rf_color4_set_bytes_return_destination(v42, 255, 255, 255, 255);
          return rf_model_handle_render_all_adapter(
                   *(_DWORD *)(*(_DWORD *)(a1 + 660) + 1352),
                   a1 + 60,
                   a1 + 72,
                   (int)v41);
        }
      }
    }
  }
  else if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 612) & 0x4000000) != 0 )
  {
    rf_renderer_set_pending_texture_handles(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 148), -1);
    v2 = rf_vector_multiply_scalar((const float *)(a1 + 96), scaled_result, *(float *)(*(_DWORD *)(a1 + 660) + 164));
    rf_vector_subtract((const float *)(a1 + 60), out_vector, v2);
    rf_renderer_tapered_segment_backend_wrapper(
      (const float *)(a1 + 60),
      *(float *)(*(_DWORD *)(a1 + 660) + 156),
      out_vector,
      *(float *)(*(_DWORD *)(a1 + 660) + 160),
      dword_182ABC0,
      0.0);
    if ( dword_663ACC == -1 )
      dword_663ACC = rf_bitmap_load_with_optional_mipmap_generation("glow01.tga", (void *)0xFFFFFFFF, 1);
    rf_renderer_set_pending_texture_handles(dword_663ACC, -1);
    rf_render_color_set_rgba8(255, 50, 50, 100);
    v3 = rf_vector_add((const float *)(a1 + 60), sum_result, out_vector);
    rf_vector_multiply_scalar(v3, v47, 0.5);
    v17 = *(float *)(*(_DWORD *)(a1 + 660) + 156) * 1.5;
    return rf_renderer_world_billboard_aspect_backend_dispatch((int)v47, 0.0, v17, dword_182ABC0);
  }
  else
  {
    rf_renderer_set_pending_texture_handles(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 148), -1);
    v46 = 255;
    v45 = 0.0;
    if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 616) & 2) != 0 )
      v45 = rf_random_float_range(0.0, 6.2831855);
    if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 616) & 4) != 0 )
    {
      v44 = 0.2;
      v43 = 6.283185482025146 / (float)0.2;
      v16 = v43 * unk_6FC42C;
      v46 = (int)(rf_sin_float(v16) * 64.0 + 64.0) + 127;
    }
    rf_render_color_set_rgba8(255, 255, 255, v46);
    return rf_renderer_world_billboard_aspect_backend_dispatch(
             a1 + 60,
             v45,
             *(float *)(*(_DWORD *)(a1 + 660) + 156),
             SLODWORD(rf_particle_glow_billboard_render_state));
  }
  return result;
}

