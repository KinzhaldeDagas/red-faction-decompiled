// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581FA0 rf_renderer_copy_current_view_transform
// UNREALRED VERIFIED [room-render-20261028]: Actual ABI has TWO stack output pointers. Copies camera position0x18CD4A8 to first via rf_vector_copy,then matrix0x18CD7E0 to second via rf_matrix3_copy, loading each destination into ECX. Current decompiler omits second parameter and some callers misleadingly appear argumentless; disassembly confirms push2/addesp8. No null-output guards; no type mutation applied.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, recovered clip/projection routines, original x87 comparisons, stack arguments and PE bytes): Corrected prototype to TWO mandatory cdecl output pointers:position3f then orientation9f. Copies18CD4A8 to first via vector-copy,18CD7E0 to second via thiscall matrix-copy with ECX=second output. No input transform,allocation,null guards or global writes. Returns EAX from final matrix-copy helper. Previous saved comment already identified the omitted second parameter;signature now corrected so decompiler/callers retain both outputs.
int __cdecl rf_renderer_copy_current_view_transform(float *destination, float *a2)
{
  float copy_result[3]; // [esp+0h] [ebp-Ch] BYREF

  rf_vector_copy(destination, copy_result, unk_18CD4A8);
  return rf_matrix3_copy(a2, &flt_18CD7E0);
}

