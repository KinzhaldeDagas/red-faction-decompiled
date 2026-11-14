// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055A780 rf_matrix3_construct_from_three_rows
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): ECX36-byte destination plus three XYZ row pointers, RET12. Calls no-op default constructors then copies row0 to0,row1 to12,row2 to24. Returns receiver. No orthogonalization/normalization, determinant checks or identity defaults; sequential copies mean overlapping input rows can be overwritten.
int __thiscall rf_matrix3_construct_from_three_rows(int this, float *source, float *a3, float *a4)
{
  float v6[3]; // [esp+4h] [ebp-24h] BYREF
  float v7[3]; // [esp+10h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop((void *)this);
  rf_vector3_default_construct_noop((void *)(this + 12));
  rf_vector3_default_construct_noop((void *)(this + 24));
  rf_vector_copy((float *)this, copy_result, source);
  rf_vector_copy((float *)(this + 12), v7, a3);
  rf_vector_copy((float *)(this + 24), v6, a4);
  return this;
}

