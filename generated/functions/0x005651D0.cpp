// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005651D0 rf_vmesh_compose_prop_world_transform
// UNREALRED VERIFIED [general-gap-20260830]: Composes a VMesh prop/tag local transform with a parent transform: multiplies local orientation by the parent, rotates local position by the parent, and adds the parent position.
float *__cdecl rf_vmesh_compose_prop_world_transform(_DWORD *a1, int a2, float *a3, float *a4, float *a5, float *a6)
{
  float *v6; // eax
  float v8[9]; // [esp+0h] [ebp-24h] BYREF

  rf_model_handle_get_node_transform_adapter(a1, a6, a5, a2);
  v6 = rf_matrix3_argument_times_receiver_to_output(a3, v8, a5);
  rf_matrix3_copy(a5, v6);
  rf_vector_rotate_by_matrix3(a6, a3);
  return rf_vector_accumulate(a6, a4);
}

