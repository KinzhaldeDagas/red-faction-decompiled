// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D4BA0 rf_physics_state_rebuild_rotated_tensor
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion integration, selected-row transforms, angular/tensor updates, contact velocity response and x87 gates): Cdecl physics-state P (object+136), NOT object base. With row-major R=P116 and tensorB=P20, computes P56=transpose(R)*B*R using native multiply argument-times-receiver ordering: first B*R,then transpose(R)*(B*R). Transpose is NOT general inverse; no determinant or orthonormality check. All intermediates local3x3; writes only destination nine floatsP56..88;returns matrix-copy EAX bits. Used after orientation changes and by contact point-velocity helper. No pointer/finite validation.
int __cdecl rf_physics_state_rebuild_rotated_tensor(int a1)
{
  float *v1; // eax
  float *v2; // eax
  const float *v4; // [esp-4h] [ebp-70h]
  float v5[9]; // [esp+0h] [ebp-6Ch] BYREF
  _BYTE v6[36]; // [esp+24h] [ebp-48h] BYREF
  float v7[9]; // [esp+48h] [ebp-24h] BYREF

  v4 = (const float *)rf_matrix3_transpose_to_output((float *)(a1 + 116), (int)v6);
  v1 = rf_matrix3_argument_times_receiver_to_output((const float *)(a1 + 116), v7, (const float *)(a1 + 20));
  v2 = rf_matrix3_argument_times_receiver_to_output(v1, v5, v4);
  return rf_matrix3_copy((float *)(a1 + 56), v2);
}

