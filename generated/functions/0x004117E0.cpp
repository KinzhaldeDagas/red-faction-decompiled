// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004117E0 rf_camera_reset_sample_arrays
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): No arguments. Releases vector-array header666AD0 then matrix-array header666AB8 backing storage, clearing count/capacity/base
// without element destruction. Constructs zero float[3] and row-major identity float[9]; copies them into outgoing stack aggregate objects, appends vector BY VALUE12bytes then matrix
// BY VALUE36bytes. No source-pointer argument to either append. Stores shared sample index666A98=0 AFTER both calls. EAX forwards final matrix append old index, normally0 on
// successful fresh seed; not a Boolean success result. No camera-slot or selected-camera mutation and no append/allocation failure checks/rollback; array operations can fail after
// earlier state changes.
int rf_camera_reset_sample_arrays()
{
  int result; // eax
  char v1; // [esp-24h] [ebp-5Ch] BYREF
  int v2; // [esp-20h] [ebp-58h]
  int v3; // [esp-1Ch] [ebp-54h]
  int v4; // [esp-18h] [ebp-50h]
  int v5; // [esp-14h] [ebp-4Ch]
  int v6; // [esp-10h] [ebp-48h]
  int v7; // [esp-Ch] [ebp-44h] BYREF
  int v8; // [esp-8h] [ebp-40h]
  int v9; // [esp-4h] [ebp-3Ch]
  float v10[3]; // [esp+8h] [ebp-30h] BYREF
  float v11[9]; // [esp+14h] [ebp-24h] BYREF

  rf_pointer_array_release_storage((void **)&unk_666AD0);
  rf_pointer_array_release_storage((void **)&unk_666AB8);
  rf_vector3_default_construct_noop(v10);
  rf_vector3_zero_return_destination(v10);
  rf_matrix3_construct((char *)v11);
  rf_identity_orientation_matrix(v11);
  rf_vector3_copy_return_destination((float *)&v7, v10);
  rf_vector_array12_append_by_value(&unk_666AD0, *(float *)&v7, v8, v9);
  rf_matrix3_copy_construct((int)&v1, v11);
  result = rf_matrix_array36_append_by_value((int *)&unk_666AB8, v1, v2, v3, v4, v5, v6, v7, v8, v9);
  unk_666A98 = 0;
  return result;
}

