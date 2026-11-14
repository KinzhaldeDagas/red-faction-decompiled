// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057F630 rf_renderer_draw_world_aabb_wire_edges
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Builds8 AABB corners then submits12 world lines:four lowerY ring edges,four upperY ring edges,four connecting edges. Uses thirdDWORD packed state and current global color. Always returns byte1 regardless backend visibility/draw results. No box validity,finite or degenerate checks;no fill/caps or color save/restore.
char __cdecl rf_renderer_draw_world_aabb_wire_edges(float *a1, float *a2, int a3)
{
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float v12[3]; // [esp+Ch] [ebp-120h] BYREF
  float v13[3]; // [esp+18h] [ebp-114h] BYREF
  float v14[3]; // [esp+24h] [ebp-108h] BYREF
  float v15[3]; // [esp+30h] [ebp-FCh] BYREF
  float v16[3]; // [esp+3Ch] [ebp-F0h] BYREF
  float v17[3]; // [esp+48h] [ebp-E4h] BYREF
  float v18[3]; // [esp+54h] [ebp-D8h] BYREF
  float v19[3]; // [esp+60h] [ebp-CCh] BYREF
  float v20[3]; // [esp+6Ch] [ebp-C0h] BYREF
  float v21[3]; // [esp+78h] [ebp-B4h] BYREF
  float v22[3]; // [esp+84h] [ebp-A8h] BYREF
  float v23[3]; // [esp+90h] [ebp-9Ch] BYREF
  float v24[3]; // [esp+9Ch] [ebp-90h] BYREF
  float v25[3]; // [esp+A8h] [ebp-84h] BYREF
  float copy_result[3]; // [esp+B4h] [ebp-78h] BYREF
  float v27[3]; // [esp+C0h] [ebp-6Ch] BYREF
  float destination[3]; // [esp+CCh] [ebp-60h] BYREF
  float v29[3]; // [esp+D8h] [ebp-54h] BYREF
  float v30[3]; // [esp+E4h] [ebp-48h] BYREF
  float v31[3]; // [esp+F0h] [ebp-3Ch] BYREF
  float v32[3]; // [esp+FCh] [ebp-30h] BYREF
  float v33[3]; // [esp+108h] [ebp-24h] BYREF
  float v34[3]; // [esp+114h] [ebp-18h] BYREF
  float v35[3]; // [esp+120h] [ebp-Ch] BYREF

  rf_vector_construct_no_unwind((char *)destination, 0xCu, 8, rf_vector3_default_construct_noop);
  v3 = rf_vector3_set_components_return_destination(v27, *a1, a1[1], a1[2]);
  rf_vector_copy(destination, copy_result, v3);
  v4 = rf_vector3_set_components_return_destination(v25, *a2, a1[1], a1[2]);
  rf_vector_copy(v29, v24, v4);
  v5 = rf_vector3_set_components_return_destination(v23, *a2, a1[1], a2[2]);
  rf_vector_copy(v30, v22, v5);
  v6 = rf_vector3_set_components_return_destination(v21, *a1, a1[1], a2[2]);
  rf_vector_copy(v31, v20, v6);
  v7 = rf_vector3_set_components_return_destination(v19, *a1, a2[1], a1[2]);
  rf_vector_copy(v32, v18, v7);
  v8 = rf_vector3_set_components_return_destination(v17, *a2, a2[1], a1[2]);
  rf_vector_copy(v33, v16, v8);
  v9 = rf_vector3_set_components_return_destination(v15, *a2, a2[1], a2[2]);
  rf_vector_copy(v34, v14, v9);
  v10 = rf_vector3_set_components_return_destination(v13, *a1, a2[1], a2[2]);
  rf_vector_copy(v35, v12, v10);
  rf_debug_draw_world_line_backend_dispatch(destination, v29, a3);
  rf_debug_draw_world_line_backend_dispatch(v29, v30, a3);
  rf_debug_draw_world_line_backend_dispatch(v30, v31, a3);
  rf_debug_draw_world_line_backend_dispatch(v31, destination, a3);
  rf_debug_draw_world_line_backend_dispatch(v32, v33, a3);
  rf_debug_draw_world_line_backend_dispatch(v33, v34, a3);
  rf_debug_draw_world_line_backend_dispatch(v34, v35, a3);
  rf_debug_draw_world_line_backend_dispatch(v35, v32, a3);
  rf_debug_draw_world_line_backend_dispatch(destination, v32, a3);
  rf_debug_draw_world_line_backend_dispatch(v29, v33, a3);
  rf_debug_draw_world_line_backend_dispatch(v30, v34, a3);
  rf_debug_draw_world_line_backend_dispatch(v31, v35, a3);
  return 1;
}

