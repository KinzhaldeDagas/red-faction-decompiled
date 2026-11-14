// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055E9C0 rf_packed3x4_translation_builder_stack_overwrite
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): cdecl(output48,x,y,z). Copies identity into local at EBP-0x30, then calls accessor55EE60 with(row3,col0/1/2). Actual address formula base+16*row+4*col yields EBP,EBP+4,EBP+8: writes x over SAVED EBP, y over RETURN ADDRESS, z over FIRST OUTPUT POINTER ARGUMENT. None of these stores lies inside48byte local. Subsequent rep movsd reads corrupted output pointer (float z bits) and copies UNCHANGED identity local; epilogue uses overwritten frame/return words if reached. Verified static instructions55E9D5..55EA1D and accessor, not inferred intended translation behavior. No executable patch applied.
float *__cdecl rf_packed3x4_translation_builder_stack_overwrite(float *a1, float a2, float a3, float a4)
{
  _BYTE v5[48]; // [esp+8h] [ebp-30h] BYREF

  rf_matrix48_copy_raw_return_self(v5, &unk_6407A8);
  *rf_packed_matrix_element_at_row16_column4_unchecked(v5, 3, 0) = a2;
  *rf_packed_matrix_element_at_row16_column4_unchecked(v5, 3, 1) = a3;
  *rf_packed_matrix_element_at_row16_column4_unchecked(v5, 3, 2) = a4;
  qmemcpy(a1, v5, 0x30u);
  return a1;
}

