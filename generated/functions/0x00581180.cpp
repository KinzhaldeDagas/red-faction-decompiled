// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581180 rf_renderer_rebuild_world_clip_planes_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): If global renderer backend187CC9C==102,calls verified world-clip-plane rebuild5C4540;otherwise no call. Existing int return is not reliable status:callee returns void and active path leaves incidental EAX;inactive path returns backend value. Does not forward fog state. Preserves prior correction comment.
int rf_renderer_rebuild_world_clip_planes_backend_wrapper()
{
  int result; // eax

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_renderer_rebuild_world_clip_planes();
  return result;
}

