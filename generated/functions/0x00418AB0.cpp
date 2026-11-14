// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00418AB0 rf_geomod_debris_object_create
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): Cdecl(context,backingSolid,mixed descriptor), three DWORD stack slots. Descriptor >=100 bytes: position0,orientation12,linear velocity48,angular velocity60,signed lifetime-ms72,setup scalar bits76,expiry-effect DWORD80,flags DWORD84,creation parameter DWORD88,bounce-event pointer DWORD96; +92 unused here. Constructs then zeros a 152-byte setup, stores solid at+8, -1 at+20, solid radius+96 at setup132 and radius/5 at setup12, copies descriptor scalar76 to setup16, uses setup flags0x8000003F plus0x100 for descriptor flag4, then creates object type3. On creation failure destroys supplied nonnull solid and local setup, returning0; solid+96 was already read, so this is not safe for null solid input. Success sets
// model+128=0,piece index+664=-1,solid+660, arms timer+676 for nonnegative lifetime or disarms otherwise, copies raw flags/effect/event into +668/+672/+688, clears count+680, sets health+52=radius+120*50 and flags+428=0x1000. Does not explicitly write sound slot+684 here. Conditional helper0x4BFCF0 and flags0x10 light-receiver registration precede intrusive tail insertion and count increment. Destroys local setup and returns object. Ownership/side effects after successful creation are not rolled back.
int __cdecl rf_geomod_debris_object_create(int context, int backing_solid, const void *descriptor)
{
  int v4; // [esp+8h] [ebp-DCh]
  float v5[3]; // [esp+18h] [ebp-CCh] BYREF
  float v6[3]; // [esp+24h] [ebp-C0h] BYREF
  float copy_result[3]; // [esp+30h] [ebp-B4h] BYREF
  int v8; // [esp+3Ch] [ebp-A8h]
  void *v9[38]; // [esp+40h] [ebp-A4h] BYREF
  int v10; // [esp+E0h] [ebp-4h]

  rf_object_setup152_construct_members((char *)v9);
  v10 = 0;
  memset(v9, 0, sizeof(v9));
  v9[2] = (void *)backing_solid;
  *(float *)&v9[5] = -1.0;
  rf_vector_copy((float *)&v9[15], copy_result, (const float *)descriptor);
  rf_matrix3_copy((float *)&v9[18], (const float *)descriptor + 3);
  rf_vector_copy((float *)&v9[27], v6, (const float *)descriptor + 12);
  rf_vector_copy((float *)&v9[30], v5, (const float *)descriptor + 15);
  v9[33] = *(void **)(backing_solid + 96);
  *(float *)&v9[3] = *(float *)&v9[33] / 5.0;
  v9[4] = *((void **)descriptor + 19);
  v9[37] = (void *)-2147483585;
  if ( (*((_DWORD *)descriptor + 21) & 4) != 0 )
    v9[37] = (void *)((int)v9[37] | 0x100);
  v8 = rf_object_create(3, -1, context, (int)v9, *((_DWORD *)descriptor + 22), 0);
  if ( v8 )
  {
    *(_DWORD *)(v8 + 128) = 0;
    *(_DWORD *)(v8 + 664) = -1;
    *(_DWORD *)(v8 + 660) = backing_solid;
    if ( *((int *)descriptor + 18) >= 0 )
      rf_replicator_arm_milliseconds((int *)(v8 + 676), *((_DWORD *)descriptor + 18));
    else
      rf_replicator_reset((_DWORD *)(v8 + 676));
    *(_DWORD *)(v8 + 668) = *((_DWORD *)descriptor + 21);
    *(_DWORD *)(v8 + 672) = *((_DWORD *)descriptor + 20);
    *(_DWORD *)(v8 + 680) = 0;
    *(_DWORD *)(v8 + 688) = *((_DWORD *)descriptor + 24);
    *(float *)(v8 + 52) = *(float *)(v8 + 120) * 50.0;
    *(_DWORD *)(v8 + 428) = 4096;
    if ( (*(_DWORD *)(v8 + 424) & 0x20) != 0 && (*(_DWORD *)(v8 + 124) & 0x8000) == 0 )
      rf_collision_register_object_against_active_list(v8);
    if ( (*((_DWORD *)descriptor + 21) & 0x10) != 0 )
      rf_light_additional_receiver_register(*(_DWORD *)(v8 + 660), v8 + 60, v8 + 72);
    *(_DWORD *)(v8 + 656) = rf_physical_debris_list_tail;
    *(_DWORD *)(v8 + 652) = &rf_physical_debris_list_sentinel;
    *(_DWORD *)(rf_physical_debris_list_tail + 652) = v8;
    rf_physical_debris_list_tail = v8;
    ++rf_physical_debris_count;
    v4 = v8;
    v10 = -1;
    rf_object_setup152_destroy_array_backing(v9);
    return v4;
  }
  else
  {
    if ( backing_solid )
      rf_solid_destroy((char *)backing_solid, 1);
    v10 = -1;
    rf_object_setup152_destroy_array_backing(v9);
    return 0;
  }
}

