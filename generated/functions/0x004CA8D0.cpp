// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CA8D0 rf_particle_render_billboard
// UNREALRED VERIFIED [combat-particle-vbm-20261104]: Ordinary nonloop/nonhold bitmap frame isfloor(age/life*frameCount+0.5), clamped0..N-1. DirectVBM uses this path withlife=N/FPS, stationaryworldorigin, randomrotation, whitecolor. Billboard renderpass follows57E990/5DA290 to5D9790, whoseaspectexpansion andhalfextent contract alsoapplyordinarynon-stretchedemitterparticles.
char __cdecl rf_particle_render_billboard(int a1)
{
  char result; // al
  float *v2; // eax
  float v3; // [esp+Ch] [ebp-40h]
  float v4; // [esp+14h] [ebp-38h]
  float value; // [esp+1Ch] [ebp-30h]
  float scaled_result[3]; // [esp+28h] [ebp-24h] BYREF
  float sum_result[3]; // [esp+34h] [ebp-18h] BYREF
  int v8; // [esp+40h] [ebp-Ch] BYREF
  int v9; // [esp+44h] [ebp-8h]
  unsigned int v10; // [esp+48h] [ebp-4h] BYREF

  ++unk_8377F0;
  rf_dword_construct_invalid_minus_one(&v10);
  v9 = *(_DWORD *)(a1 + 72);
  if ( *(__int16 *)(a1 + 76) > 1 )
  {
    if ( (*(_DWORD *)(a1 + 88) & 0x100) != 0 )
    {
      value = (*(float *)(a1 + 36) - (double)(int)rf_floor_float(*(float *)(a1 + 36)))
            * 15.0
            / (double)*(__int16 *)(a1 + 76)
            + 0.5;
      v8 = (int)rf_floor_float(value);
    }
    else if ( (*(_WORD *)(a1 + 78) & 4) != 0 )
    {
      v4 = *(float *)(a1 + 36) / (*(float *)(a1 + 52) * *(float *)(a1 + 92)) * (double)*(__int16 *)(a1 + 76) + 0.5;
      v8 = (int)rf_floor_float(v4);
      if ( v8 >= *(__int16 *)(a1 + 76) )
        v8 = *(__int16 *)(a1 + 76) - 1;
    }
    else
    {
      v3 = *(float *)(a1 + 36) / *(float *)(a1 + 52) * (double)*(__int16 *)(a1 + 76) + 0.5;
      v8 = (int)rf_floor_float(v3);
    }
    rf_integer_clamp_in_place(&v8, 0, *(__int16 *)(a1 + 76) - 1);
    v9 += v8;
  }
  if ( (*(_DWORD *)(a1 + 88) & 2) != 0 )
    v10 = rf_particle_glow_billboard_render_state;
  else
    v10 = rf_particle_standard_billboard_render_state;
  if ( (*(_DWORD *)(a1 + 88) & 0x2000) != 0 )
    rf_render_state_set_bits20_24((int *)&v10, 0);
  rf_renderer_set_pending_texture_handles(v9, -1);
  rf_render_color_set_packed_rgba8((unsigned __int8 *)(a1 + 48));
  if ( (*(_DWORD *)(a1 + 88) & 0x4000) != 0 )
    rf_renderer_stretched_diamond_backend_wrapper(a1 + 12, a1 + 108, *(float *)(a1 + 56), v10);
  else
    rf_renderer_world_billboard_aspect_backend_dispatch(a1 + 12, *(float *)(a1 + 84), *(float *)(a1 + 56), v10);
  result = unk_8377DD;
  if ( unk_8377DD )
  {
    v2 = rf_vector_multiply_scalar((const float *)(a1 + 24), scaled_result, rf_frame_delta_seconds);
    rf_vector_add((const float *)(a1 + 12), sum_result, v2);
    return rf_debug_draw_world_line_backend_dispatch(a1 + 12, (int)sum_result, dword_182ABA0);
  }
  return result;
}

