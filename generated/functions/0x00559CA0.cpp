// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00559CA0 rf_vector_interpolate_directions_normalized_inputs
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): cdecl(output,from,to,fraction). Normalizes each input via guarded normalized-copy558F90, using unitX on zero/NaN length, then delegates559D10. Does not preserve original input magnitudes. Parallel/antiparallel normalized vectors still feed unchecked cross-axis normalization in delegate; no fallback interpolation or fraction clamp.
float *__cdecl rf_vector_interpolate_directions_normalized_inputs(
        float *a1,
        const float *a2,
        const float *a3,
        float a4)
{
  float *v4; // eax
  float *v5; // eax
  float v7[3]; // [esp+4h] [ebp-48h] BYREF
  float v8[3]; // [esp+10h] [ebp-3Ch] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-30h] BYREF
  float v10[3]; // [esp+28h] [ebp-24h] BYREF
  float destination[3]; // [esp+34h] [ebp-18h] BYREF
  float v12[3]; // [esp+40h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(v12);
  v4 = rf_vector3_normalized_copy_or_unit_x((float *)a2, v10);
  rf_vector_copy(destination, copy_result, v4);
  v5 = rf_vector3_normalized_copy_or_unit_x((float *)a3, v8);
  rf_vector_copy(v12, v7, v5);
  return rf_vector_interpolate_directions_unit_inputs(a1, destination, v12, a4);
}

