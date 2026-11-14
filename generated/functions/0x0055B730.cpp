// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055B730 rf_matrix3_inverse_to_output
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): ECX source plus destination, RET4. Copies matrix to local, invokes55BC30 in-place cofactor inverse, then copies local to output. If determinant exactly0, inverse helper leaves local unchanged, so this returns an unchanged COPY of singular matrix without failure indication. Source/output alias safe; EAX destination bits.
int __thiscall rf_matrix3_inverse_to_output(const void *this, int a2)
{
  float v3[9]; // [esp+4h] [ebp-24h] BYREF

  rf_matrix3_copy_construct((int)v3, this);
  rf_matrix3_inverse_in_place_if_nonsingular(v3);
  rf_matrix3_copy_construct(a2, v3);
  return a2;
}

