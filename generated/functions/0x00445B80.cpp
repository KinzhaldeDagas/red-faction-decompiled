// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00445B80 rf_entity_rotate_then_filter_view_offset_axes
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion dispatch, buffered pose consumers, contact effects, selector filtering and x87 unordered branches): Cdecl(outVector,entity,inputVector),THREE stackargs,caller pops12,returns outVectorEAX. Corrects saved two-argument integer prototype. Rotates input by matrix rows of current entity252 through5590A0 (outXYZ are dot products with current matrix rows0/1/2),stages local vector,then delegates445BC0 to retain only axes whose current descriptor20/24/28 equals1. No normalization,angle clamp or tensor update;input and output may alias because transform staged. No own NULL/descriptor/finite checks.
float *__cdecl rf_entity_rotate_then_filter_view_offset_axes(float *out_vector, int entity, const float *input_vector)
{
  float v4[3]; // [esp+0h] [ebp-Ch] BYREF

  rf_vector3_transform_by_matrix_rows((float *)input_vector, v4, (float *)(entity + 252));
  rf_entity_filter_rotation_axes_for_view_offset(out_vector, entity, v4);
  return out_vector;
}

