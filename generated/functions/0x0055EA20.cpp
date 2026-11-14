// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055EA20 rf_packed3x4_scale_to_output
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): cdecl(output48,sx,sy,sz). Copies packed identity local then writes diagonal elements(0,0),(1,1),(2,2) with16byte stride; copies48bytes to output and returns output. Offdiagonal/fourth-column remain0. Negative/zero/nonfinite scales unchecked; no translation writes.
float *__cdecl rf_packed3x4_scale_to_output(float *a1, float a2, float a3, float a4)
{
  _BYTE v5[48]; // [esp+8h] [ebp-30h] BYREF

  rf_matrix48_copy_raw_return_self(v5, &unk_6407A8);
  *rf_packed_matrix_element_at_row16_column4_unchecked(v5, 0, 0) = a2;
  *rf_packed_matrix_element_at_row16_column4_unchecked(v5, 1, 1) = a3;
  *rf_packed_matrix_element_at_row16_column4_unchecked(v5, 2, 2) = a4;
  qmemcpy(a1, v5, 0x30u);
  return a1;
}

