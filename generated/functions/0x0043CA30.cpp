// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043CA30 rf_collision_hit40_assign
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Thiscall ECX destination40-byte record, one stack source pointer, RET4, EAX original destination. Sequential
// operations: copy DWORD0 verbatim; copy FLOAT4 via x87; vector assignment at+8, then+20 using distinct LOCAL hidden-copy-result vectors; copy DWORD32 thenDWORD36 verbatim. Covers
// exactly40 bytes with mixed integer/float/vector transfers, not a raw memcpy or whole-record snapshot. Source+destination exact alias supported by sequence; arbitrary partial
// overlap can observe earlier writes. No allocation, constructor/defaulting, NULL/length/field validity/finite check, normalized result or extra write beyond record.
float *__thiscall rf_collision_hit40_assign(float *this, float *a2)
{
  float v4[3]; // [esp+4h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+10h] [ebp-Ch] BYREF

  *this = *a2;
  *(this + 1) = a2[1];
  rf_vector_copy(this + 2, copy_result, a2 + 2);
  rf_vector_copy(this + 5, v4, a2 + 5);
  *(this + 8) = a2[8];
  *(this + 9) = a2[9];
  return this;
}

