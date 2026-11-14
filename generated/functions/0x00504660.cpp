// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00504660 rf_trigger_runtime_create
// UNREALRED VERIFIED [mission-startup-20261020] Trigger descriptor+0x10 supplies ButtonActiveTime MILLISECONDS to runtime+0x29C, +0x14 supplies full signed activation limit to+0x2A4, +0x68 supplies the numeric NPC policy to+0x2C4, and +0x7C supplies clutter ResetTime seconds to+0x2F0. Serialized input layout must not be inferred from previous UE field labels.
// UNREALRED VERIFIED [trigger-attachment-20261020] Descriptor+0x20 copies to runtime trigger+0x300 as authored attachment UID. This is converted later during level loading to a runtime handle, not used as a persistent per-frame UID reference. Initial pose is overwritten by the resolved common owner during that fixup, with no authored relative offset.
// UNREALRED VERIFIED [trigger-use-20261021] Trigger constructor appends to the runtime list tail at504A0E..504A2F; RFL loader482D10 constructs in serialized order. Therefore ordinary and auto scans preserve source creation order independently of UE scene-component construction order.
float *__cdecl rf_trigger_runtime_create(int a1)
{
  int v2; // [esp+4h] [ebp-E8h]
  float *v3; // [esp+8h] [ebp-E4h]
  float v4[3]; // [esp+10h] [ebp-DCh] BYREF
  float v5[3]; // [esp+1Ch] [ebp-D0h] BYREF
  float v6[3]; // [esp+28h] [ebp-C4h] BYREF
  float copy_result[3]; // [esp+38h] [ebp-B4h] BYREF
  float *v8; // [esp+44h] [ebp-A8h]
  void *v9[38]; // [esp+48h] [ebp-A4h] BYREF
  int v10; // [esp+E8h] [ebp-4h]

  if ( *(int *)(a1 + 12) >= 2 )
    return nullptr;
  rf_object_setup152_construct_members((char *)v9);
  v10 = 0;
  memset(v9, 0, sizeof(v9));
  v9[0] = nullptr;
  v9[2] = nullptr;
  *(float *)&v9[5] = 1.0;
  v9[33] = *(void **)(a1 + 40);
  rf_vector_copy((float *)&v9[15], copy_result, (const float *)(a1 + 44));
  rf_matrix3_copy((float *)&v9[18], (const float *)(a1 + 56));
  v9[37] = (void *)32;
  v8 = rf_object_create(5, -1, -1, (int)v9, 1, nullptr);
  if ( v8 )
  {
    rf_string_assign_from_object((_DWORD *)v8 + 6, a1);
    *((_BYTE *)v8 + 776) = *(_BYTE *)(a1 + 8);
    v8[165] = *(float *)(a1 + 12);
    rf_replicator_arm_milliseconds((int *)v8 + 166, 0);
    v8[167] = *(float *)(a1 + 16);
    v8[168] = 0.0;
    v8[169] = *(float *)(a1 + 20);
    v8[170] = -1.0;
    v8[171] = *(float *)(a1 + 116);
    rf_pointer_array_release_storage((void **)v8 + 181);
    v8[172] = *(float *)(a1 + 24);
    v8[176] = *(float *)(a1 + 28);
    v8[188] = *(float *)(a1 + 124);
    rf_replicator_reset((_DWORD *)v8 + 189);
    rf_replicator_reset((_DWORD *)v8 + 184);
    rf_replicator_reset((_DWORD *)v8 + 186);
    v8[185] = NAN;
    v8[190] = *(float *)(a1 + 128);
    rf_replicator_reset((_DWORD *)v8 + 191);
    v8[192] = *(float *)(a1 + 32);
    v8[193] = *(float *)(a1 + 36);
    v8[177] = *(float *)(a1 + 104);
    v2 = *(_DWORD *)(a1 + 12);
    if ( v2 )
    {
      if ( v2 != 1 )
        rf_fatal_error_show_message_and_exit(
          "D:\\projects\\rf_pc\\gamesrc\\trigger\\trigger.cpp",
          848,
          "Unrecognized trigger type in trigger_create\n");
      rf_vector_copy(v8 + 15, v5, (const float *)(a1 + 44));
      rf_matrix3_copy(v8 + 18, (const float *)(a1 + 56));
      rf_vector_copy(v8 + 178, v4, (const float *)(a1 + 92));
      *((_BYTE *)v8 + 748) = *(_BYTE *)(a1 + 120);
    }
    else
    {
      rf_vector_copy(v8 + 15, v6, (const float *)(a1 + 44));
      v8[30] = *(float *)(a1 + 40);
    }
    if ( ((_DWORD)v8[106] & 0x20) != 0 )
      rf_collision_register_object_against_active_list((int)v8);
    *((_DWORD *)v8 + 164) = unk_90B7A0;
    *((_DWORD *)v8 + 163) = &unk_90B510;
    *(_DWORD *)(unk_90B7A0 + 652) = v8;
    unk_90B7A0 = v8;
    ++unk_90B504;
    v3 = v8;
    v10 = -1;
    rf_object_setup152_destroy_array_backing(v9);
    return v3;
  }
  else
  {
    v10 = -1;
    rf_object_setup152_destroy_array_backing(v9);
    return nullptr;
  }
}

