// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B9BA0 rf_world_submit_object_callbacks_for_room
// UNREALRED VERIFIED [impact-callbacks-20261028]: Queues items,eligible projectiles(flags+124 mask0x1 clear),clutter,physical debris and corpses whose first-dword room matches caller; payload runtime handle+44,stored/cull position+60,radius+120,callback0x4BA6E0,sort from flags+124 mask0x100000,lighting byte0x4BDC50()/0. Another list0x704BCC uses room-admission0x4BA930 and lighting0/1. Enabled records in list0x680DA0 (next+696) can submit null callback for culling-only or sorted object callback depending definition+684 field+36; successful submission ORs record+692 mask0x80000000. Entities in list0x68211C skip respawn-inactive; special predicate0x43C910 uses room-admission,others first-dword room equality. For admitted entities copies position and optionally adjusts speech/body-action culling point via0x4BD150. Main entity callback always follows optional muzzle work. Muzzle attachments
// require observed view/owner gates and unelapsed entity timer+4972, with separate normal-weapon,definition-prop and vehicle/jeep transform branches; queued callbacks0x4BA8F0 use shared16-slot56-byte ring0x7D0F10. After each submission fills effect ID,position,matrix,variant then slot=(slot+1)&15; does not reserve slots against reuse by other pending callbacks. Main stored position can differ from adjusted culling center; submission failures do not rollback ring advancement. Return AL incidental, not submitted count. Full numerical gates retained in disassembly; no inference that all admitted callbacks draw visible geometry.
char __cdecl rf_world_submit_object_callbacks_for_room(int a1, char a2)
{
  char gate; // al
  char v3; // al
  char v4; // al
  char v5; // al
  char v6; // al
  int first_dword; // eax
  int v8; // eax
  char v9; // al
  float v11[3]; // [esp+20h] [ebp-13Ch] BYREF
  float v12[3]; // [esp+2Ch] [ebp-130h] BYREF
  float copy_result[3]; // [esp+38h] [ebp-124h] BYREF
  int v14; // [esp+44h] [ebp-118h]
  float out_position[3]; // [esp+48h] [ebp-114h] BYREF
  float v16[9]; // [esp+54h] [ebp-108h] BYREF
  char v17; // [esp+7Bh] [ebp-E1h]
  char *v18; // [esp+7Ch] [ebp-E0h]
  float v19[3]; // [esp+80h] [ebp-DCh] BYREF
  float v20[9]; // [esp+8Ch] [ebp-D0h] BYREF
  float source[3]; // [esp+B0h] [ebp-ACh] BYREF
  float v22[9]; // [esp+BCh] [ebp-A0h] BYREF
  int v23; // [esp+E0h] [ebp-7Ch]
  int muzzle_1_bone_index; // [esp+E4h] [ebp-78h]
  float out_orientation[9]; // [esp+E8h] [ebp-74h] BYREF
  float out_attachment_position[3]; // [esp+10Ch] [ebp-50h] BYREF
  float out_corrected_position[3]; // [esp+118h] [ebp-44h] BYREF
  char *v28; // [esp+124h] [ebp-38h]
  int v29; // [esp+128h] [ebp-34h]
  int v30[3]; // [esp+12Ch] [ebp-30h] BYREF
  char v31; // [esp+13Bh] [ebp-21h]
  unsigned int *entity; // [esp+13Ch] [ebp-20h]
  void *i; // [esp+140h] [ebp-1Ch]
  void *j; // [esp+144h] [ebp-18h]
  void *m; // [esp+148h] [ebp-14h]
  void *n; // [esp+14Ch] [ebp-10h]
  int ii; // [esp+150h] [ebp-Ch]
  void *jj; // [esp+154h] [ebp-8h]
  void *k; // [esp+158h] [ebp-4h]

  for ( i = (void *)unk_6FB1C4; i != &unk_6FAF38; i = *((void **)i + 163) )
  {
    if ( rf_receiver_get_first_dword(i) == a1 )
    {
      gate = rf_world_object_callback_light_query_gate();
      rf_world_submit_render_callback_entry(
        *((_DWORD *)i + 11),
        (int)i + 60,
        (int)i + 60,
        *((float *)i + 30),
        (int)rf_world_object_handle_render_callback,
        (*((_DWORD *)i + 31) & 0x100000) != 0,
        0,
        0,
        0,
        gate,
        0);
    }
  }
  for ( j = (void *)dword_911F74; j != &unk_911CE8; j = *((void **)j + 163) )
  {
    if ( (*((_DWORD *)j + 31) & 1) == 0 && rf_receiver_get_first_dword(j) == a1 )
    {
      v3 = rf_world_object_callback_light_query_gate();
      rf_world_submit_render_callback_entry(
        *((_DWORD *)j + 11),
        (int)j + 60,
        (int)j + 60,
        *((float *)j + 30),
        (int)rf_world_object_handle_render_callback,
        (*((_DWORD *)j + 31) & 0x100000) != 0,
        0,
        0,
        0,
        v3,
        0);
    }
  }
  for ( k = (void *)rf_clutter_list_head; k != &unk_666D18; k = *((void **)k + 163) )
  {
    if ( rf_receiver_get_first_dword(k) == a1 )
    {
      v4 = rf_world_object_callback_light_query_gate();
      rf_world_submit_render_callback_entry(
        *((_DWORD *)k + 11),
        (int)k + 60,
        (int)k + 60,
        *((float *)k + 30),
        (int)rf_world_object_handle_render_callback,
        (*((_DWORD *)k + 31) & 0x100000) != 0,
        0,
        0,
        0,
        v4,
        0);
    }
  }
  for ( m = (void *)rf_physical_debris_list_head; m != &rf_physical_debris_list_sentinel; m = *((void **)m + 163) )
  {
    if ( rf_receiver_get_first_dword(m) == a1 )
    {
      v5 = rf_world_object_callback_light_query_gate();
      rf_world_submit_render_callback_entry(
        *((_DWORD *)m + 11),
        (int)m + 60,
        (int)m + 60,
        *((float *)m + 30),
        (int)rf_world_object_handle_render_callback,
        (*((_DWORD *)m + 31) & 0x100000) != 0,
        0,
        0,
        0,
        v5,
        0);
    }
  }
  for ( n = (void *)rf_corpse_list_head; n != &unk_681AF8; n = *((void **)n + 163) )
  {
    if ( rf_receiver_get_first_dword(n) == a1 )
    {
      v6 = rf_world_object_callback_light_query_gate();
      rf_world_submit_render_callback_entry(
        *((_DWORD *)n + 11),
        (int)n + 60,
        (int)n + 60,
        *((float *)n + 30),
        (int)rf_world_object_handle_render_callback,
        (*((_DWORD *)n + 31) & 0x100000) != 0,
        0,
        0,
        0,
        v6,
        0);
    }
  }
  for ( ii = unk_704BCC; (_UNKNOWN *)ii != &unk_704940; ii = *(_DWORD *)(ii + 652) )
  {
    if ( rf_world_object_admitted_for_room_submission(ii, a1, a2) )
      rf_world_submit_render_callback_entry(
        *(_DWORD *)(ii + 44),
        ii + 60,
        ii + 60,
        *(float *)(ii + 120),
        (int)rf_world_object_handle_render_callback,
        (*(_DWORD *)(ii + 124) & 0x100000) != 0,
        0,
        0,
        0,
        0,
        1);
  }
  for ( jj = (void *)unk_680DA0; jj != &unk_680AE8; jj = *((void **)jj + 174) )
  {
    if ( rf_receiver_get_first_dword(jj) == a1 && *((_BYTE *)jj + 652) )
    {
      if ( *(int *)(*((_DWORD *)jj + 171) + 36) <= 0 )
      {
        if ( rf_world_submit_render_callback_entry(
               *((_DWORD *)jj + 11),
               (int)jj + 60,
               (int)jj + 60,
               *((float *)jj + 30),
               0,
               0,
               0,
               0,
               0,
               0,
               1) )
        {
          *((_DWORD *)jj + 173) |= 0x80000000;
        }
      }
      else if ( rf_world_submit_render_callback_entry(
                  *((_DWORD *)jj + 11),
                  (int)jj + 60,
                  (int)jj + 60,
                  *((float *)jj + 30),
                  (int)rf_world_object_handle_render_callback,
                  1,
                  0,
                  0,
                  0,
                  0,
                  1) )
      {
        *((_DWORD *)jj + 173) |= 0x80000000;
      }
    }
  }
  LOBYTE(first_dword) = dword_68211C;
  for ( entity = (unsigned int *)dword_68211C; entity != (unsigned int *)&unk_681E90; entity = (unsigned int *)entity[163] )
  {
    LOBYTE(first_dword) = rf_object_has_respawn_inactive_flag((int)entity);
    if ( !(_BYTE)first_dword )
    {
      v31 = 0;
      if ( rf_entity_class_flag1000((int)entity) )
      {
        LOBYTE(first_dword) = rf_world_object_admitted_for_room_submission((int)entity, a1, a2);
        if ( (_BYTE)first_dword )
          v31 = 1;
      }
      else
      {
        first_dword = rf_receiver_get_first_dword(entity);
        if ( first_dword == a1 )
          v31 = 1;
      }
      if ( v31 )
      {
        rf_vector3_copy_return_destination((float *)v30, (float *)entity + 15);
        if ( rf_entity_admits_speech_body_actions((int)entity) )
          rf_object_copy_node_or_common_world_position((int)entity, (int)v30);
        v29 = rf_object_resolve_handle(*(_DWORD *)(unk_87C640 + 180));
        if ( entity[1292] != unk_87C640
          || rf_view_wrapper_get_dword8(*(_DWORD *)(unk_87C640 + 196))
          || unk_6807E0 == 1
          || v29 )
        {
          if ( !rf_replicator_has_elapsed((int *)entity + 1243)
            && !rf_entity_has_attached_use_vehicle((int)entity)
            && !rf_object_is_use_vehicle(entity) )
          {
            v28 = (char *)&rf_weapon_records + 1360 * entity[169];
            if ( *((_DWORD *)v28 + 15) != -1 && !rf_entity_custom_mask142C_has_index((int)entity, entity[169]) )
            {
              rf_vector3_default_construct_noop(out_corrected_position);
              rf_vector3_default_construct_noop(out_attachment_position);
              rf_matrix3_construct((char *)out_orientation);
              v8 = rf_receiver_get_first_dword((void *)(entity[167] + 468));
              if ( rf_entity_copy_weapon_attachment_transforms(
                     entity,
                     v8 - 1,
                     out_attachment_position,
                     out_corrected_position,
                     out_orientation) != -1 )
              {
                rf_vector3_default_construct_noop(source);
                rf_matrix3_construct((char *)v22);
                muzzle_1_bone_index = rf_weapon_get_muzzle_1_bone_index(entity[169]);
                v23 = sub_50FFA0(entity[169]);
                rf_vmesh_compose_prop_world_transform(
                  v23,
                  muzzle_1_bone_index,
                  out_orientation,
                  (int)out_corrected_position,
                  (int)v22,
                  source);
                rf_world_submit_render_callback_entry(
                  unk_7B8E1C,
                  (int)source,
                  (int)source,
                  unk_680DF0[13 * *((_DWORD *)v28 + 15)],
                  (int)rf_world_muzzle_effect_ring_render_callback,
                  1,
                  0,
                  0,
                  0,
                  0,
                  1);
                unk_7D0F10[14 * unk_7B8E1C] = *((_DWORD *)v28 + 15);
                rf_vector_copy((float *)&unk_7D0F14 + 14 * unk_7B8E1C, copy_result, source);
                rf_matrix3_copy((float *)&unk_7D0F20 + 14 * unk_7B8E1C, v22);
                unk_7D0F44[56 * unk_7B8E1C] = (*((_DWORD *)v28 + 153) & 0x2000) == 0;
                unk_7B8E1C = ((_BYTE)unk_7B8E1C + 1) & 0xF;
              }
            }
          }
          if ( *(int *)(entity[165] + 252) > -1 && !rf_replicator_has_elapsed((int *)entity + 1243) )
          {
            rf_vector3_default_construct_noop(v19);
            rf_matrix3_construct((char *)v20);
            if ( *(_DWORD *)(entity[165] + 244) != -1 )
            {
              rf_vmesh_compose_prop_world_transform(
                entity[32],
                *(_DWORD *)(entity[165] + 244),
                (float *)entity + 504,
                (int)(entity + 15),
                (int)v20,
                v19);
              rf_world_submit_render_callback_entry(
                unk_7B8E1C,
                (int)v19,
                (int)v19,
                unk_680DF0[13 * *(_DWORD *)(entity[165] + 252)],
                (int)rf_world_muzzle_effect_ring_render_callback,
                1,
                0,
                0,
                0,
                0,
                1);
              unk_7D0F10[14 * unk_7B8E1C] = *(_DWORD *)(entity[165] + 252);
              rf_vector_copy((float *)&unk_7D0F14 + 14 * unk_7B8E1C, v12, v19);
              rf_matrix3_copy((float *)&unk_7D0F20 + 14 * unk_7B8E1C, v20);
              unk_7D0F44[56 * unk_7B8E1C] = 0;
              unk_7B8E1C = ((_BYTE)unk_7B8E1C + 1) & 0xF;
            }
          }
          if ( rf_object_get_use_classification(entity) == 1
            && entity[169] != -1
            && !rf_replicator_has_elapsed((int *)entity + 1243) )
          {
            v18 = (char *)&rf_weapon_records + 1360 * entity[169];
            v17 = 0;
            rf_vector3_default_construct_noop(out_position);
            rf_matrix3_construct((char *)v16);
            if ( rf_entity_has_jeep_flag((int)entity) )
            {
              if ( rf_entity_jeep_auxiliary_tag_world_transform((int)entity, out_position, v16) )
                v17 = 1;
              v14 = rf_entity_resolve_handle(*(_DWORD *)(unk_87C640 + 20));
              if ( v14
                && rf_entity_is_parent_jeep_relation1(v14)
                && *(_DWORD *)(v14 + 512) == entity[11]
                && !rf_view_wrapper_get_dword8(*(_DWORD *)(unk_87C640 + 196)) )
              {
                v17 = 0;
              }
            }
            else if ( *((_DWORD *)v18 + 15) != -1 && *(_DWORD *)(entity[165] + 244) != -1 )
            {
              rf_vmesh_compose_prop_world_transform(
                entity[32],
                *(_DWORD *)(entity[165] + 244),
                (float *)entity + 18,
                (int)(entity + 15),
                (int)v16,
                out_position);
              v17 = 1;
            }
            if ( v17 )
            {
              rf_world_submit_render_callback_entry(
                unk_7B8E1C,
                (int)out_position,
                (int)out_position,
                unk_680DF0[13 * *((_DWORD *)v18 + 15)],
                (int)rf_world_muzzle_effect_ring_render_callback,
                1,
                0,
                0,
                0,
                0,
                1);
              unk_7D0F10[14 * unk_7B8E1C] = *((_DWORD *)v18 + 15);
              rf_vector_copy((float *)&unk_7D0F14 + 14 * unk_7B8E1C, v11, out_position);
              rf_matrix3_copy((float *)&unk_7D0F20 + 14 * unk_7B8E1C, v16);
              unk_7D0F44[56 * unk_7B8E1C] = 1;
              unk_7B8E1C = ((_BYTE)unk_7B8E1C + 1) & 0xF;
            }
          }
        }
        v9 = rf_world_object_callback_light_query_gate();
        LOBYTE(first_dword) = rf_world_submit_render_callback_entry(
                                entity[11],
                                (int)(entity + 15),
                                (int)v30,
                                *((float *)entity + 30),
                                (int)rf_world_object_handle_render_callback,
                                (entity[31] & 0x100000) != 0,
                                0,
                                0,
                                0,
                                v9,
                                0);
      }
    }
  }
  return first_dword;
}

