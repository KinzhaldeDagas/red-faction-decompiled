// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C8800 rf_glass_shard_vertex_copy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, full rectangular/general quad tessellation, ordered edge selection and stale loop indices, native UV/grid coordinates, pool freshness and delayed launch semantics): 
// Cdecl(destination,source), copies20B vertex in order vec3XYZ through40CDF0,then FPU FLD/FSTP source+12 ->dest+12 (U),source+16 ->dest+16(V). Returns SOURCE pointer in EAX (last
// live register), not destination. No bounds/alias/finite validation or whole-record snapshot; overlapping storage follows sequential helper/UV stores. Floating assignments can quiet
// signaling NaNs; not raw memcpy.
float *__cdecl rf_glass_shard_vertex_copy(float *destination, float *source)
{
  float copy_result[3]; // [esp+0h] [ebp-Ch] BYREF

  rf_vector_copy(destination, copy_result, source);
  destination[3] = source[3];
  destination[4] = source[4];
  return source;
}

