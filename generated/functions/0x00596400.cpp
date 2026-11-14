// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00596400 rf_scene_point_pool_allocate_type0_zero_channel64
// UNREALRED VERIFIED [transfer-scene-20261028]: Wrapper taking position and5 floats. Calls0x5962A0(position,arg2,0.0,arg3,arg4,arg5,arg6), so record scalar+64 is zero. Returns allocated index or-1. No additional validation or initialization.
int __cdecl rf_scene_point_pool_allocate_type0_zero_channel64(
        float *a1,
        float a2,
        float a3,
        float a4,
        float a5,
        float a6)
{
  return rf_scene_point_pool_allocate_type0(a1, a2, 0.0, a3, a4, a5, a6);
}

