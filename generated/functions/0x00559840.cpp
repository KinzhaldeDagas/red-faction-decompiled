// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00559840 rf_vector_reject_component_along_normal
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): cdecl(output,input,normal). Computes dot(input,normal), copies input into output, then adds normal*(-dot). Formula input-normal*dot(input,normal); true orthogonal rejection requires unit normal, no division by normal length squared. Output may alias input, but output==normal mutates normal before final multiply and can change result.
float *__cdecl rf_vector_reject_component_along_normal(float *destination, float *source, float *vector)
{
  float *v3; // eax
  float scalar; // [esp+0h] [ebp-20h]
  float scaled_result[3]; // [esp+4h] [ebp-1Ch] BYREF
  float copy_result[3]; // [esp+10h] [ebp-10h] BYREF
  float v8; // [esp+1Ch] [ebp-4h]

  v8 = rf_vector_dot(source, vector);
  rf_vector_copy(destination, copy_result, source);
  scalar = -v8;
  v3 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
  return rf_vector_accumulate(destination, v3);
}

