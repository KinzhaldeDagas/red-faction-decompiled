// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DD550 rf_renderer_draw_impact_chunk_backend_102
// UNREALRED VERIFIED [impact-callbacks-20261028]: Packs render state(1,2,3,3,4,0), sets pending texture=chunk+68 and secondhandle-1, sets white color with caller alpha. Constructs8 local48-byte projected vertices; copies eight local-space vec3 corners at chunk+124+12*i, transforms through0x55A4A0 using chunk+8/+20, projects each through0x5817B0. For12 triangles at chunk+220+36*i, each of3 entries stores UV floats and pointer to original corner; maps pointer delta/12 to projected vertex, assigns UV+28/+32, submits immediate3-vertex polygon. No index/pointer validation, dedup/clipping precheck or state restoration here.
void __cdecl rf_renderer_draw_impact_chunk_backend_102(int a1, int a2)
{
  int v2; // [esp+4h] [ebp-1A8h]
  float v3[3]; // [esp+8h] [ebp-1A4h] BYREF
  int v4; // [esp+14h] [ebp-198h] BYREF
  int j; // [esp+18h] [ebp-194h]
  char v6[384]; // [esp+1Ch] [ebp-190h] BYREF
  int v7[3]; // [esp+19Ch] [ebp-10h] BYREF
  int i; // [esp+1A8h] [ebp-4h]

  rf_render_state_pack(&v4, 1, 2, 3, 3, 4, 0);
  rf_renderer_set_pending_texture_handles(*(_DWORD *)(a1 + 68), -1);
  rf_render_color_set_rgba8(255, 255, 255, a2);
  rf_vector_construct_no_unwind(v6, 0x30u, 8, rf_vector_prefix_construct_noop);
  for ( i = 0; i < 8; ++i )
  {
    rf_vector3_copy_return_destination(v3, (float *)(a1 + 12 * i + 124));
    rf_vector_rotate_translate_in_place(v3, (float *)(a1 + 8), (float *)(a1 + 20));
    rf_renderer_transform_world_point_backend_wrapper((int)&v6[48 * i], v3);
  }
  for ( i = 0; i < 12; ++i )
  {
    v2 = a1 + 36 * i + 220;
    for ( j = 0; j < 3; ++j )
    {
      v7[j] = (int)&v6[48 * ((*(_DWORD *)(v2 + 12 * j + 8) - (a1 + 124)) / 12)];
      *(float *)(v7[j] + 28) = *(float *)(v2 + 12 * j);
      *(float *)(v7[j] + 32) = *(float *)(v2 + 12 * j + 4);
    }
    rf_renderer_submit_immediate_polygon(3, (int)v7, 1, v4, 0, 0.0);
  }
}

