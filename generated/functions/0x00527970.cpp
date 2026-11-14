// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00527970 rf_renderer_light_get_original_position
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): Cdecl handle,outXYZ. Resolve unchecked, copy original record vector12..20 into output, ignoring receiver-space selector18CD388. No serial/list/light mutation or validity check. Existing float* return is vector-copy LOCAL result object on this frame, not stable output address; rely on writtenXYZ.
float *__cdecl rf_renderer_light_get_original_position(int a1, float *destination)
{
  float copy_result[3]; // [esp+0h] [ebp-10h] BYREF
  int *v4; // [esp+Ch] [ebp-4h]

  v4 = rf_renderer_light_resolve_handle(a1);
  return rf_vector_copy(destination, copy_result, (const float *)v4 + 3);
}

