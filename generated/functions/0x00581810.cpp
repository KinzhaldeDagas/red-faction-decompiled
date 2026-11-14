// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581810 rf_renderer_transform_points48_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, recovered clip/projection routines, original x87 comparisons, stack arguments and PE bytes): Recovered cdecl output clip48-record pointer,input contiguous XYZ pointer,count. Backend102 forwards all3 arguments to5C5310;otherwise no output writes,returns backend integer. Callee transforms without screen projection and inherits unsafe negative-count loop. No allocation/capacity validation here.
int __cdecl rf_renderer_transform_points48_backend_wrapper(void *a1, const float *a2, int a3)
{
  int result; // eax

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_renderer_transform_world_points_to_clip48((int)a1, (int)a2, a3);
  return result;
}

