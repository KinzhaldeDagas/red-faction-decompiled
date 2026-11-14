// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004187B0 rf_physical_debris_piece_create
// UNREALRED VERIFIED [weapon-shell-ejection-20261008] Third float argument is copied to object setup +0x14 and reaches physics-state mass +0x10 via 0x4D7A00. Shell caller passes0.1; reload-clip caller passes0.3. These are physical mass values, not visual mesh scales. Lifetime comes from spawn-config +72 milliseconds and sound id from +96.
// UNREALRED VERIFIED [reload-clip-physics-20261013] Reload caller0x4216EB supplies mass0.3; copied to setup+0x14. Config+48/+60 feed linear/angular velocity; +72 owns lifetime and +96 is retained at debris+0x2B0 for custom contact sound. This does not implement an immediate ejection Foley event or mesh scaling.
int __cdecl rf_physical_debris_piece_create(int a1, void *a2, void *a3, float *source, int a5, void *a6)
{
  int v7; // [esp+4h] [ebp-D4h]
  float v8[3]; // [esp+Ch] [ebp-CCh] BYREF
  float v9[3]; // [esp+18h] [ebp-C0h] BYREF
  float copy_result[3]; // [esp+24h] [ebp-B4h] BYREF
  int v11; // [esp+30h] [ebp-A8h]
  void *v12[38]; // [esp+34h] [ebp-A4h] BYREF
  int v13; // [esp+D4h] [ebp-4h]

  rf_object_setup152_construct_members((char *)v12);
  v13 = 0;
  memset(v12, 0, sizeof(v12));
  v12[0] = a2;
  v12[1] = (void *)1;
  v12[33] = a6;
  v12[5] = a3;
  rf_vector_copy((float *)&v12[15], copy_result, source);
  rf_matrix3_copy((float *)&v12[18], source + 3);
  rf_vector_copy((float *)&v12[27], v9, source + 12);
  rf_vector_copy((float *)&v12[30], v8, source + 15);
  v12[4] = *((void **)source + 19);
  v12[37] = (void *)-2147483631;
  if ( ((_DWORD)source[21] & 4) != 0 )
    v12[37] = (void *)((int)v12[37] | 0x100);
  v11 = rf_object_create(3, -1, a1, (int)v12, *((_DWORD *)source + 22), *((_DWORD *)source + 23));
  if ( v11 )
  {
    *(_DWORD *)(v11 + 660) = 0;
    *(_DWORD *)(v11 + 664) = a5;
    if ( *((int *)source + 18) >= 0 )
      rf_replicator_arm_milliseconds((int *)(v11 + 676), *((_DWORD *)source + 18));
    else
      rf_replicator_reset((_DWORD *)(v11 + 676));
    *(float *)(v11 + 668) = source[21];
    *(float *)(v11 + 672) = source[20];
    *(_DWORD *)(v11 + 680) = 0;
    *(_DWORD *)(v11 + 684) = -1;
    *(float *)(v11 + 688) = source[24];
    *(float *)(v11 + 52) = *(float *)(v11 + 120) * 50.0;
    *(_DWORD *)(v11 + 428) = 4096;
    if ( (*(_DWORD *)(v11 + 424) & 0x20) != 0 && (*(_DWORD *)(v11 + 124) & 0x8000) == 0 )
      rf_collision_register_object_against_active_list(v11);
    if ( ((_DWORD)source[21] & 0x10) != 0 )
      rf_light_additional_receiver_register(*(_DWORD *)(v11 + 660), v11 + 60, v11 + 72);
    *(_DWORD *)(v11 + 656) = rf_physical_debris_list_tail;
    *(_DWORD *)(v11 + 652) = &rf_physical_debris_list_sentinel;
    *(_DWORD *)(rf_physical_debris_list_tail + 652) = v11;
    rf_physical_debris_list_tail = v11;
    ++rf_physical_debris_count;
    v7 = v11;
    v13 = -1;
    rf_object_setup152_destroy_array_backing(v12);
    return v7;
  }
  else
  {
    v13 = -1;
    rf_object_setup152_destroy_array_backing(v12);
    return 0;
  }
}

