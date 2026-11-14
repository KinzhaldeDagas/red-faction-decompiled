// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B7E00 rf_object_create
// UNREALRED VERIFIED [mission-when-dead-20261013] At the final common-object initialization branch ORs flag 0x00400000 except for common types 5,6,8,9,10. This is the flag read by the When_Dead blocking predicate 0x4BDC20. Scan of executable instruction references to 0x400000 / clear mask 0xFFBFFFFF identifies this as the common+0x7C constructor write; same-number bits at Entity+0x1A8/+0x810 have unrelated ownership.
// UNREALRED VERIFIED [mission-when-dead-targets-20261013] Allocates a new free slot and generation-bearing handle at +0x2C independently of a3. Stores a3 at +0x30 as parent/owner and uses its resolved object to inherit common attributes. Distinguish source-handle retirement from new corpse clutter creation; a3 does not rebind an old handle.
// UNREALRED VERIFIED [trigger-airlock-20261022] Object creation resolves initial common room through517060 with absent old room and identical start/end; this reaches532BA0 geometric point classification. Mover creation can therefore leave a null room; room ownership is not inferred solely from authored AABBs.
// UNREALRED VERIFIED [combat-burn-owner-20261104]: Common-object friendliness at+0x1F8 copies supplied value unless incoming-1, in which case initializes1. This field is not multiplayer TeamId; retain native common friendliness independently of an uninitialized host preview-AI sentinel.
// UNREALRED VERIFIED [combat-route-operands-20261111] Constructor writes common+200=-1 and+204=-1 before model/physics creation.436A80 resolves Entity200 and requires attached entity Use exactly1 before406130 uses its physical/common operands. A host common-lifetime null mapping may represent this known initial-1; attached-use transitions require their own actual writers, not inference from UE attachment lists.
// UNREALRED VERIFIED [combat-original-snapdown-20261112]: Initial room admission is before allocation: with world-solid present and supplied roomNULL,517060(world,NULL,setup+3C,setup+3C,0) directly classifies through532BA0. A NULL result rejects ordinary type0 in singleplayer; any nonzero native MP mode permits type0 NULL. World-solid absent skips this lookup/admission gate; an empty present solid is distinct.4BC210 writes cached ROOM atCOMMON+0 and copies currentCOMMON3C into cached+4; later4BC330 does not reclassify or dirty this room value.426790 updates auxiliary sphere positions only. A host may preserve this completed birth-room receipt through later topology edits; query-time source/topology fences are separate from its lifetime.
float *__cdecl rf_object_create(int a1, int a2, int a3, int a4, int a5, void *a6)
{
  float v7[7]; // [esp-18h] [ebp-74h] BYREF
  float v8[3]; // [esp+4h] [ebp-58h] BYREF
  float v9[3]; // [esp+10h] [ebp-4Ch] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-40h] BYREF
  float v11[3]; // [esp+28h] [ebp-34h] BYREF
  char v12[12]; // [esp+34h] [ebp-28h] BYREF
  int i; // [esp+40h] [ebp-1Ch]
  int v14; // [esp+44h] [ebp-18h]
  float *v15; // [esp+48h] [ebp-14h]
  int v16; // [esp+4Ch] [ebp-10h]
  int v17; // [esp+50h] [ebp-Ch]
  void *v18; // [esp+54h] [ebp-8h]
  int v19; // [esp+58h] [ebp-4h]

  v18 = a6;
  if ( rf_world_solid )
  {
    if ( !v18 )
    {
      v18 = rf_world_resolve_cached_room(
              (void *)rf_world_solid,
              nullptr,
              (const float *)(a4 + 60),
              (const float *)(a4 + 60),
              0);
      if ( !v18 && a1 != 6 && a1 != 8 && (!rf_multiplayer_runtime_mode || a1) )
        return nullptr;
    }
  }
  if ( (_DWORD *)dword_7B4DFC == &dword_7B4DFC )
    return nullptr;
  v16 = dword_7B4DFC;
  v17 = *(_DWORD *)(dword_7B4DFC + 8);
  v15 = (float *)rf_object_allocate_by_type(a1, a2);
  if ( !v15 )
    return nullptr;
  unk_7B7E10[v17] = (int)v15;
  *(_DWORD *)unk_7B4E14[3 * v17] = unk_7B4E10[3 * v17];
  *(_DWORD *)(unk_7B4E10[3 * v17] + 4) = unk_7B4E14[3 * v17];
  unk_7B4E10[3 * v17] = 0;
  unk_7B4E14[3 * v17] = 0;
  *((_DWORD *)v15 + 11) = v17;
  *((_DWORD *)v15 + 11) += word_7B4E08[0]++ << 16;
  if ( word_7B4E08[0] >= 0x752Fu )
    word_7B4E08[0] = 1;
  rf_string_assign_from_cstr((_DWORD *)v15 + 6, (char *)byte_63B86E);
  *((_DWORD *)v15 + 8) = dword_662DC4--;
  *((_DWORD *)v15 + 9) = a1;
  *((_DWORD *)v15 + 12) = a3;
  v15[127] = *(float *)(a4 + 16);
  v15[13] = 100.0;
  rf_vector_copy(v15 + 15, copy_result, (const float *)(a4 + 60));
  rf_vector_copy(v15 + 27, v9, (const float *)(a4 + 60));
  rf_matrix3_copy(v15 + 18, (const float *)(a4 + 72));
  rf_vector_copy(v15 + 142, v8, (const float *)(a4 + 60));
  rf_matrix3_copy(v15 + 145, (const float *)(a4 + 72));
  v15[157] = NAN;
  *((_BYTE *)v15 + 624) = -1;
  v15[158] = 0.0;
  v15[155] = NAN;
  v15[128] = NAN;
  v15[129] = NAN;
  v15[14] = 0.0;
  *((_DWORD *)v15 + 31) = a5;
  if ( (a5 & 0x4000) != 0 )
    *((_DWORD *)v15 + 31) |= 0x8000u;
  *((_DWORD *)v15 + 31) |= 0x6000000u;
  v19 = rf_object_resolve_handle(a3);
  if ( v19 )
    *((_BYTE *)v15 + 40) = *(_BYTE *)(v19 + 40);
  else
    *((_BYTE *)v15 + 40) = 0;
  if ( v19 )
    v15[126] = *(float *)(v19 + 504);
  else
    *((_DWORD *)v15 + 126) = 1;
  if ( *(_DWORD *)a4 )
  {
    if ( !rf_object_bind_model_filename_by_kind((int)v15, *(char **)a4, *(_DWORD *)(a4 + 4)) )
    {
      rf_object_release_slot_and_storage(v17);
      return nullptr;
    }
    if ( rf_receiver_get_first_dword((void *)(a4 + 136)) < 1 )
    {
      v14 = rf_model_handle_named_sphere_count_adapter(*((_DWORD **)v15 + 32));
      for ( i = 0; i < v14; ++i )
      {
        rf_vector_prefix_construct_noop(v11);
        rf_model_handle_get_named_sphere_adapter(*((_DWORD **)v15 + 32), i, v11, (float *)v12);
        if ( v14 == 1 )
          rf_vector3_zero_return_destination(v11);
        rf_record24_copy_construct_six_floats(v7, v11);
        rf_array24_append_record_by_value(
          (int *)(a4 + 136),
          v7[0],
          SLODWORD(v7[1]),
          SLODWORD(v7[2]),
          SLODWORD(v7[3]),
          SLODWORD(v7[4]),
          SLODWORD(v7[5]));
      }
    }
  }
  else
  {
    v15[32] = 0.0;
    v15[33] = NAN;
    if ( *(float *)(a4 + 132) <= 0.0 )
      v15[30] = 1.0;
    else
      v15[30] = *(float *)(a4 + 132);
  }
  if ( *(float *)(a4 + 132) < 0.0 )
    *(float *)(a4 + 132) = v15[30];
  if ( (a5 & 0x10000) != 0 )
    *(_DWORD *)(a4 + 148) &= ~0x20u;
  rf_physics_state_initialize_from_setup((int)(v15 + 34), a4);
  rf_object_set_room_and_cache_position(v15, (int)v18);
  if ( *((_DWORD *)v15 + 9) != 8
    && *((_DWORD *)v15 + 9) != 5
    && *((_DWORD *)v15 + 9) != 6
    && *((_DWORD *)v15 + 9) != 10
    && *((_DWORD *)v15 + 9) != 9 )
  {
    *((_DWORD *)v15 + 31) |= 0x400000u;
  }
  return v15;
}

