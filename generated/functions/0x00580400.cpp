// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580400 rf_glass_shard_render_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Backend102 forwards shard DWORD to verified immediate glass-shard renderer;otherwise no draw and returns backend value. No geometry or lifetime changes in this bridge.
int __cdecl rf_glass_shard_render_backend_wrapper(int a1)
{
  int result; // eax

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_glass_shard_render_immediate(a1);
  return result;
}

