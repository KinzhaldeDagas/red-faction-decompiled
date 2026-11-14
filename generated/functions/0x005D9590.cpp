// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D9590 rf_renderer_draw_instance_glow_billboard
// UNREALRED VERIFIED [renderer-overlays-20261028]: Copies instance localposition+4,rotates by matrix+92,adds instance translation+80 and globaloffset0xA5A0EC. Sets pendingtexture from definition(*instance)+272,texture1=-1; draws aspectworldbillboard0x5DA290 angle0,size from definition+160,state rf_particle_glow_billboard_render_state. Does not set currentcolor/alpha or restore texture.
char __cdecl rf_renderer_draw_instance_glow_billboard(float *a1)
{
  float *v1; // eax
  float sum_result[3]; // [esp+Ch] [ebp-18h] BYREF
  int v4[3]; // [esp+18h] [ebp-Ch] BYREF

  rf_vector3_copy_return_destination((float *)v4, a1 + 1);
  rf_vector_rotate_by_matrix3((float *)v4, a1 + 23);
  v1 = rf_vector_add(a1 + 20, sum_result, &flt_A5A0EC);
  rf_vector_accumulate((float *)v4, v1);
  rf_renderer_set_pending_texture_handles(*(_DWORD *)(*(_DWORD *)a1 + 272), -1);
  return rf_renderer_draw_world_billboard_aspect(
           (float *)v4,
           0.0,
           *(float *)(*(_DWORD *)a1 + 160),
           SLODWORD(rf_particle_glow_billboard_render_state));
}

