// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00559A30 rf_triangle_cross_from_three_points
// UNREALRED VERIFIED [renderer-helpers-20261028]: Actual four stack arguments: output vector,p0,p1,p2. Computes cross(p1-p0,p2-p1),copies three-float result to output. Equivalent oriented unnormalized triangle normal; no normalization or degeneracy check. Does not modify input positions. Return follows vector-copy helper,not normal magnitude.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): Corrected stale saved signature from3 toFOUR cdecl stack arguments(output,p0,p1,p2). Computes cross(p1-p0,p2-p1), equivalent oriented unnormalized triangle normal, writes XYZ output and returns its pointer bits. Inputs staged through temporaries, no normalization or area/degeneracy checks. This correction restores missing p2 in polygon area/normal callers.
float *__cdecl rf_triangle_cross_from_three_points(
        float *destination,
        const float *a2,
        const float *a3,
        const float *a4)
{
  float *v4; // eax
  float *v5; // eax
  float *v7; // [esp-4h] [ebp-34h]
  float copy_result[3]; // [esp+0h] [ebp-30h] BYREF
  float v9[3]; // [esp+Ch] [ebp-24h] BYREF
  float out_vector[3]; // [esp+18h] [ebp-18h] BYREF
  float v11[3]; // [esp+24h] [ebp-Ch] BYREF

  v7 = rf_vector_subtract(a4, out_vector, a3);
  v4 = rf_vector_subtract(a3, v11, a2);
  v5 = rf_vector_cross(v4, v9, v7);
  return rf_vector_copy(destination, copy_result, v5);
}

