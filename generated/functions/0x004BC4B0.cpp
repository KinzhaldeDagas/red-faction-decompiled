// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BC4B0 rf_object_attach_store_parent_and_pose
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, object room/attachment ownership, shape-based ground lighting, native dispatcher table and resolver/view distinctions): Thiscall child plus parent pointer stack DWORD,RET4. ORs child common flags124 mask0x04000000; stores parent HANDLE44 into child association512. Offset vector520=child physical position228-parent physical position228, with NO inverse rotation (world-axis difference). Relative matrix532=child physical matrix252 * transpose(parent physical matrix252), following verified argument-times-receiver helper order. Zeros child velocity324 and angular velocity336. Returns pointer to final cleared angular-velocity vector child+336, not child pointer/status. Does not set attachment slot516, immediately change pose/room, test cycles/null pointers or validate orthonormal matrices.
float *__thiscall rf_object_attach_store_parent_and_pose(int this, int a2)
{
  float *v2; // eax
  const float *v3; // eax
  float *v4; // eax
  float v7[9]; // [esp+4h] [ebp-60h] BYREF
  _BYTE v8[36]; // [esp+28h] [ebp-3Ch] BYREF
  float copy_result[3]; // [esp+4Ch] [ebp-18h] BYREF
  float out_vector[3]; // [esp+58h] [ebp-Ch] BYREF

  *(_DWORD *)(this + 124) |= 0x4000000u;
  *(_DWORD *)(this + 512) = *(_DWORD *)(a2 + 44);
  v2 = rf_vector_subtract((const float *)(this + 228), out_vector, (const float *)(a2 + 228));
  rf_vector_copy((float *)(this + 520), copy_result, v2);
  v3 = (const float *)rf_matrix3_transpose_to_output((float *)(a2 + 252), (int)v8);
  v4 = rf_matrix3_argument_times_receiver_to_output(v3, v7, (const float *)(this + 252));
  rf_matrix3_copy((float *)(this + 532), v4);
  rf_vector3_zero_return_destination((float *)(this + 324));
  return rf_vector3_zero_return_destination((float *)(this + 336));
}

