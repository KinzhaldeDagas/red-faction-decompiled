// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C5430 rf_renderer_transform_direction_scaled_camera
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric states, stack ABI and callers): Multiplies supplied direction by rows of the current scaled camera matrix18CD4B4 and copies XYZ into output. Does not subtract camera origin, override depth, generate outcodes or project. Supports distinct or aliased input/output through local intermediate. Returns the vector-copy helper EAX.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, recovered clip/projection routines, original x87 comparisons, stack arguments and PE bytes): Corrected saved one-argument prototype to cdecl outputXYZ,sourceDirectionXYZ. Applies scaled camera matrix rows18CD4B4 to source into local vector,then copies XYZ to destination. Returns vector-copy helper EAX. No camera-origin subtraction,orthographic Z override,outcode generation or screen projection;local intermediate supports exact input/output alias. Existing verified behavior retained;both actual stack parameters now explicit.
int __cdecl rf_renderer_transform_direction_scaled_camera(float *destination, const float *a2)
{
  float *v2; // eax
  float copy_result[3]; // [esp+0h] [ebp-18h] BYREF
  float v5[3]; // [esp+Ch] [ebp-Ch] BYREF

  v2 = rf_vector3_transform_by_matrix_rows((float *)a2, v5, &flt_18CD4B4);
  return (int)rf_vector_copy(destination, copy_result, v2);
}

