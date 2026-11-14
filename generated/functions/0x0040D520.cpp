// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D520 rf_matrix3_copy
// UNREALRED VERIFIED [trigger-attachment-20261020] Attachment caller504635 sets ECX=trigger+0x48 before calling with owner+0x48. Preserve this implicit destination when interpreting current decompiler output: three copied vector rows update trigger orientation, not merely stack temporaries. Existing database prototype is left unchanged in this pass.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, recovered clip/projection routines, original x87 comparisons, stack arguments and PE bytes): Corrected shared thiscall ABI:ECX is writable destination matrix3,one stack pointer is source9floats. Copies three12-byte rows at offsets0,12,24 through vector-copy helper. Returns final row-copy EAX;no normalization,allocation or transpose. Exact self-copy works;arbitrary partial overlap not protected by full9-float snapshot. Previous saved annotation already identified implicit receiver;prototype now explicitly preserves receiver and source so camera snapshot and other callers decompile with both matrices.
int __thiscall rf_matrix3_copy(float *this, const float *a2)
{
  float v4[3]; // [esp+4h] [ebp-24h] BYREF
  float v5[3]; // [esp+10h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-Ch] BYREF

  rf_vector_copy(this, copy_result, a2);
  rf_vector_copy(this + 3, v5, a2 + 3);
  return (int)rf_vector_copy(this + 6, v4, a2 + 6);
}

