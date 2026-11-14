// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DD720 rf_glass_shard_render_immediate
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, input remapping,text wrapping,Bink playback/default records,archive metadata,projection/aperture/classification and glass submission): Cdecl shard pointer. Packs state(1,2,3,3,4,0),sets pending texture to shard DWORD60 with second handle-1,and RGBA from unsigned bytes56..59. Constructs4 no-op vector-prefix48-byte scratch records. For each of4 shard20-byte records at116+20*i,copies position,applies matrix shard+20 then translation shard+8 through55A4A0,transforms world point into clip vertex via backend wrapper,and writes UV from shard128/132+20*i to vertex28/32. Submits polygon(count4,pointer array,option1,packed state,extra0,float0) and returns submission AL. No normal/lighting input,visibility/lifetime/texture-handle validation,matrix normalization or renderer-state restoration here; lower submit/transform helpers
// own clipping/projection behavior. Earlier repeatable impact-glass summary retained.
char __cdecl rf_glass_shard_render_immediate(int a1)
{
  float v2[3]; // [esp+4h] [ebp-E8h] BYREF
  int v3; // [esp+10h] [ebp-DCh] BYREF
  char v4[196]; // [esp+14h] [ebp-D8h] BYREF
  int v5[4]; // [esp+D8h] [ebp-14h] BYREF
  int i; // [esp+E8h] [ebp-4h]

  rf_render_state_pack(&v3, 1, 2, 3, 3, 4, 0);
  rf_renderer_set_pending_texture_handles(*(_DWORD *)(a1 + 60), -1);
  rf_render_color_set_rgba8(
    *(unsigned __int8 *)(a1 + 56),
    *(unsigned __int8 *)(a1 + 57),
    *(unsigned __int8 *)(a1 + 58),
    *(unsigned __int8 *)(a1 + 59));
  rf_vector_construct_no_unwind(v4, 0x30u, 4, rf_vector_prefix_construct_noop);
  for ( i = 0; i < 4; ++i )
  {
    rf_vector3_copy_return_destination(v2, (float *)(a1 + 20 * i + 116));
    rf_vector_rotate_translate_in_place(v2, (float *)(a1 + 8), (float *)(a1 + 20));
    rf_renderer_transform_world_point_backend_wrapper((int)&v4[48 * i], v2);
    v5[i] = (int)&v4[48 * i];
    *(float *)(v5[i] + 28) = *(float *)(a1 + 20 * i + 128);
    *(float *)(v5[i] + 32) = *(float *)(a1 + 20 * i + 132);
  }
  return rf_renderer_submit_immediate_polygon(4, (int)v5, 1, v3, 0, 0.0);
}

