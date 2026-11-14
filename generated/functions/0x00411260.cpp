// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00411260 rf_camera_initialize_two_slots_and_sample_arrays
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): No stack arguments. Fixed SIGNED loop i=0,1 clears ONLY owner-player DWORD at666AA4+12*i; does not destroy/reset existing camera
// pointers666AA0 or slot states666AA8. Dedicated-process BYTE704E83==EXACT1 clears selected-camera666A9C and skips allocation AND atexit registration. Every other byte value
// calls4113F0(global local-FPGun player87C318); SIGNED result>-1 copies camera pointer from that slot to selected-camera666A9C, otherwise selected-camera is retained. Registers411350
// with atexit regardless of allocator result, ignores registration result. Then releases vector-array header666AD0 and matrix-array header666AB8 backing storage (count/capacity/base
// cleared, no element destruction), constructs ZERO vector and IDENTITY matrix, appends each BY VALUE using12/36 stack bytes, and writes shared sample index666A98=0. Final EAX is
// matrix append old index, normally0 after successful reset/seeding; not a true-success byte. No allocation/append-result checks, camera rollback or idempotent destruction before
// owner-slot clearing. The two resets/appends are sequential, so failure can leave partial array state.
int rf_camera_initialize_two_slots_and_sample_arrays()
{
  int result; // eax
  char v1; // [esp-24h] [ebp-64h] BYREF
  int v2; // [esp-20h] [ebp-60h]
  int v3; // [esp-1Ch] [ebp-5Ch]
  int v4; // [esp-18h] [ebp-58h]
  int v5; // [esp-14h] [ebp-54h]
  int v6; // [esp-10h] [ebp-50h]
  int v7; // [esp-Ch] [ebp-4Ch] BYREF
  int v8; // [esp-8h] [ebp-48h]
  int v9; // [esp-4h] [ebp-44h]
  int player_slot; // [esp+8h] [ebp-38h]
  float v11[3]; // [esp+Ch] [ebp-34h] BYREF
  float v12[9]; // [esp+18h] [ebp-28h] BYREF
  int i; // [esp+3Ch] [ebp-4h]

  for ( i = 0; i < 2; ++i )
    unk_666AA4[3 * i] = 0;
  if ( byte_704E83 == 1 )
  {
    unk_666A9C = 0;
  }
  else
  {
    player_slot = rf_camera_allocate_player_slot(rf_local_fpgun_player);
    if ( player_slot > -1 )
      unk_666A9C = unk_666AA0[3 * player_slot];
    atexit(rf_camera_cleanup_two_slots_and_sample_arrays);
  }
  rf_pointer_array_release_storage((void **)&unk_666AD0);
  rf_pointer_array_release_storage((void **)&unk_666AB8);
  rf_vector3_default_construct_noop(v11);
  rf_vector3_zero_return_destination(v11);
  rf_matrix3_construct((char *)v12);
  rf_identity_orientation_matrix(v12);
  rf_vector3_copy_return_destination((float *)&v7, v11);
  rf_vector_array12_append_by_value(&unk_666AD0, *(float *)&v7, v8, v9);
  rf_matrix3_copy_construct((int)&v1, v12);
  result = rf_matrix_array36_append_by_value((int *)&unk_666AB8, v1, v2, v3, v4, v5, v6, v7, v8, v9);
  unk_666A98 = 0;
  return result;
}

