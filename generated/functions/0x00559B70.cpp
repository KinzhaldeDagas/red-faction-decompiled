// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00559B70 rf_point_project_to_plane
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): cdecl(output,point,normal,pointOnPlane). Writes point-normal*(dot(point,normal)-dot(pointOnPlane,normal)); correct orthogonal projection requires unit normal, no divide by normal length squared. Copies point to output before multiplying normal; output aliasing normal can change the calculation. Returns output; no plane validation.
float *__cdecl rf_point_project_to_plane(
        float *output,
        const float *point,
        const float *normal,
        const float *plane_point)
{
  float *v4; // eax
  float scalar; // [esp+0h] [ebp-24h]
  float scaled_result[3]; // [esp+4h] [ebp-20h] BYREF
  float copy_result[3]; // [esp+10h] [ebp-14h] BYREF
  float v9; // [esp+1Ch] [ebp-8h]
  float v10; // [esp+20h] [ebp-4h]

  v9 = -rf_vector_dot((float *)plane_point, (float *)normal);
  v10 = rf_vector_dot((float *)point, (float *)normal) + v9;
  rf_vector_copy(output, copy_result, point);
  scalar = -v10;
  v4 = rf_vector_multiply_scalar(normal, scaled_result, scalar);
  return rf_vector_accumulate(output, v4);
}

