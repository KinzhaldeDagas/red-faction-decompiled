// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00514BB0 rf_mesh_decal_request80_copy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projected mesh decal pools,shadow records,x87 unordered filters and recovered no-op constructors,original ECX/stack flow and PE bytes): Thiscalldestination80,source80*,RET4,returndestination. Copy rawDWORD0/4,F32radius8,two3f vectors12/24,matrix3f36..71,rawDWORDflags72 andselector76. Shallow owner-pointer/handle copy,no normalization,allocation,referencecount or sourcevalidation. Includes selector even when sourceconstructor left it untouched;use gated byflag4. Exact self-copy works;partial overlap not protected by full80-byte snapshot. Payload stored atquery+96 by514780.
float *__thiscall rf_mesh_decal_request80_copy(float *this, float *a2)
{
  float v4[3]; // [esp+4h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+10h] [ebp-Ch] BYREF

  *this = *a2;
  *(this + 1) = a2[1];
  *(this + 2) = a2[2];
  rf_vector_copy(this + 3, copy_result, a2 + 3);
  rf_vector_copy(this + 6, v4, a2 + 6);
  rf_matrix3_copy(this + 9, a2 + 9);
  *(this + 18) = a2[18];
  *(this + 19) = a2[19];
  return this;
}

