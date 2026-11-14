// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005817E0 rf_renderer_transform_direction_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, recovered clip/projection routines, original x87 comparisons, stack arguments and PE bytes): Recovered backend bridge,actual TWO stack args:output XYZ pointer,source direction XYZ pointer. Backend187CC9C==102 forwards both to5C5430;unsupported backend does not write output and returns backend value. Active EAX from vector-copy helper,not a uniform status. Does not transform world position,generate outcode or project.
int __cdecl rf_renderer_transform_direction_backend_wrapper(float *a1, const float *a2)
{
  int result; // eax

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_renderer_transform_direction_scaled_camera(a1, a2);
  return result;
}

