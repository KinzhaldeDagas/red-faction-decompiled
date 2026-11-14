// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B22C0 rf_scene_unpack_signed_vertex
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, SFXO/CHNE model wire layout, signed vertex unpacking, vector-return ABI, shared pools and key/geometry conversions): CDECL flattened vector-return helper: stack args output float[3],const signed int16[3],origin X/Y/Z by value,scale X/Y/Z by value; returns output pointer EAX, plain RET/caller cleans32 bytes. MOVSX loads all three signed words, multiplies each by supplied float scale and stores float-rounded products to local vec3, then adds supplied origin through the verified rf_vector_accumulate helper and copies exactly12 bytes to output. No fixed division by32767/65535, normalization, clamp or input mutation. Local products/copy make source components consumed before final output writes. Corrected origin Y/Z from wrongly inferred ints to floats; they are contiguous float args passed by address to vector accumulate.
// In CHNE used before subtract-origin/radius calculation.
float *__cdecl rf_scene_unpack_signed_vertex(
        float *out_vertex,
        const __int16 *packed,
        float origin_x,
        float origin_y,
        float origin_z,
        float scale_x,
        float scale_y,
        float scale_z)
{
  float v9[3]; // [esp+Ch] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(v9);
  v9[0] = (double)*packed * scale_x;
  v9[1] = (double)packed[1] * scale_y;
  v9[2] = (double)packed[2] * scale_z;
  rf_vector_accumulate(v9, &origin_x);
  rf_vector3_copy_return_destination(out_vertex, v9);
  return out_vertex;
}

