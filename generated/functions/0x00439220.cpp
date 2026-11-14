// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00439220 rf_character_drop_selected_weapon_item
// UNREALRED VERIFIED [combat-panic-20261104]:40B1A0 calls selected-item helper439220(a2=0), not entire Drop_Weapon mission action. Early rejection can retain selection/inventory. Admitted a2=0 calls403C20(selectedID), clearsEntity+2A4 before mandatory radius.1/flag2000 ground sweep and optional itemspawn. It does not unconditionally clear every ownedweapon. Worlddrop failure occurs after admitted selection mutation; keep failure phases and ownedammo distinct.
// UNREALRED VERIFIED [combat-selected-drop-20261111]: Panic literal a2=0 requires native earlyadmission/prop/worldmodel/itemmapping before selected presence clear403C20 andEntity+2A4=-1. Ground query finalargument1 at43957D makeseffectivebestT1 despiteFLT_MAXpreload; nohit/spawnfailure doesnotrollback selection. Ground extentEntity+7C4 isAI+524 retained initialization height. FullmissionDrop clearsallpresence separately and cannot replace this helper.
// UNREALRED VERIFIED [combat-ammo-identity-20261111]: Selected-drop ammo is retained weapon loaded PLUS DIRECT rawreserve[AmmoID], so unknownAmmoID-1 contributes actual numeric secondary selection. There is NO403D00 ownershipadmission in this owner: unownedselectedweapon maydrop ifothergatespass; loaded/presence remain separate. Host needs native-ID-indexed counterrecords even whennotowned. Wrap/prefix/callback ownership mustnot be replaced by a normalized fallbackpool or an owned-only guard.
int __cdecl rf_character_drop_selected_weapon_item(unsigned int *entity, char a2)
{
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float v12; // [esp+Ch] [ebp-1ECh]
  float v13; // [esp+10h] [ebp-1E8h]
  float v14; // [esp+14h] [ebp-1E4h]
  float v15[3]; // [esp+18h] [ebp-1E0h] BYREF
  float v16[3]; // [esp+24h] [ebp-1D4h] BYREF
  float v17[3]; // [esp+30h] [ebp-1C8h] BYREF
  float sum_result[3]; // [esp+3Ch] [ebp-1BCh] BYREF
  float scaled_result[3]; // [esp+48h] [ebp-1B0h] BYREF
  float v20[3]; // [esp+54h] [ebp-1A4h] BYREF
  float v21[3]; // [esp+60h] [ebp-198h] BYREF
  float v22[3]; // [esp+6Ch] [ebp-18Ch] BYREF
  float v23[3]; // [esp+78h] [ebp-180h] BYREF
  float v24[3]; // [esp+84h] [ebp-174h] BYREF
  float v25[3]; // [esp+90h] [ebp-168h] BYREF
  float v26[3]; // [esp+9Ch] [ebp-15Ch] BYREF
  float v27[3]; // [esp+A8h] [ebp-150h] BYREF
  float v28[3]; // [esp+B4h] [ebp-144h] BYREF
  float v29[3]; // [esp+C0h] [ebp-138h] BYREF
  float v30[3]; // [esp+CCh] [ebp-12Ch] BYREF
  float v31[3]; // [esp+D8h] [ebp-120h] BYREF
  float out_vector[3]; // [esp+E4h] [ebp-114h] BYREF
  float copy_result[3]; // [esp+F0h] [ebp-108h] BYREF
  int v34; // [esp+FCh] [ebp-FCh]
  char v35[4]; // [esp+100h] [ebp-F8h] BYREF
  float v36[3]; // [esp+104h] [ebp-F4h] BYREF
  float v37[9]; // [esp+110h] [ebp-E8h] BYREF
  float destination[3]; // [esp+134h] [ebp-C4h] BYREF
  float v39[12]; // [esp+140h] [ebp-B8h] BYREF
  _DWORD v40[2]; // [esp+170h] [ebp-88h] BYREF
  float source[3]; // [esp+178h] [ebp-80h] BYREF
  float vector[5]; // [esp+184h] [ebp-74h] BYREF
  int v43; // [esp+198h] [ebp-60h]
  int v44; // [esp+19Ch] [ebp-5Ch]
  int v45; // [esp+1A0h] [ebp-58h]
  float out_orientation[3]; // [esp+1A4h] [ebp-54h] BYREF
  float v47[3]; // [esp+1B0h] [ebp-48h] BYREF
  float v48[3]; // [esp+1BCh] [ebp-3Ch] BYREF
  float rhs[3]; // [esp+1C8h] [ebp-30h] BYREF
  float out_attachment_position[3]; // [esp+1D4h] [ebp-24h] BYREF
  float lhs[3]; // [esp+1E0h] [ebp-18h] BYREF
  float out_corrected_position; // [esp+1ECh] [ebp-Ch] BYREF
  float v53; // [esp+1F0h] [ebp-8h]
  float v54; // [esp+1F4h] [ebp-4h]

  rf_vector3_default_construct_noop(rhs);
  rf_vector3_default_construct_noop(lhs);
  if ( entity[169] == rf_weapon_index_grenade || (entity[106] & 0x400000) != 0 )
    return 0;
  if ( (entity[169] & 0x80000000) == 0 )
  {
    v44 = entity[dword_912024[340 * entity[169]] + 171] + entity[entity[169] + 203];
    if ( v44 <= 0 )
      return 0;
  }
  v45 = 0;
  rf_vector3_default_construct_noop(out_attachment_position);
  rf_vector3_default_construct_noop(&out_corrected_position);
  rf_matrix3_construct((char *)out_orientation);
  if ( !rf_entity_copy_weapon_attachment_transforms(
          entity,
          0,
          out_attachment_position,
          &out_corrected_position,
          out_orientation) )
  {
    v43 = rf_item_definition_find_by_given_weapon(entity[169]);
    if ( v43 != -1 )
    {
      v34 = 0;
      if ( rf_multiplayer_runtime_mode == 1 )
      {
        v34 = entity[dword_912024[340 * entity[169]] + 171] + entity[entity[169] + 203];
      }
      else
      {
        v34 = unk_912088[340 * entity[169]];
        v34 -= (int)(rf_random_float_range(0.0, 0.2) * (double)v34);
        if ( v34 < 4 )
          v34 = 4;
      }
      if ( rf_string_equals_case_insensitive((int)&unk_6F9130 + 80 * v43, "Remote Charges") )
        v43 = rf_item_definition_find_by_name("Remote Charge");
      if ( a2 == 1 )
      {
        v14 = v53 + 0.5;
        rf_vector3_set_components_thiscall(rhs, out_corrected_position, v14, v54);
        v13 = v53 - *((float *)entity + 497) * 4.0;
        rf_vector3_set_components_thiscall(lhs, out_corrected_position, v13, v54);
      }
      else
      {
        rf_vector3_set_components_thiscall(
          rhs,
          *((float *)entity + 15),
          *((float *)entity + 16),
          *((float *)entity + 17));
        v12 = *((float *)entity + 16) - *((float *)entity + 497) * 4.0;
        rf_vector3_set_components_thiscall(lhs, *((float *)entity + 15), v12, *((float *)entity + 17));
        sub_403C20((int)(entity + 168), entity[169]);
        entity[169] = -1;
      }
      rf_solid_collision_query_construct_clear_face_hint(v35);
      rf_solid_collision_result_construct_noop((int)v40);
      rf_vector_copy(destination, copy_result, rhs);
      v3 = rf_vector_subtract(lhs, out_vector, rhs);
      rf_vector_copy(v39, v31, v3);
      v39[3] = 0.1;
      LODWORD(v39[4]) = 0x2000;
      rf_vector3_zero_return_destination(v36);
      rf_identity_orientation_matrix(v37);
      *(float *)&v40[1] = 3.4028235e38;
      rf_world_collision_sweep((char *)rf_world_solid, (int)v35, (int)v40, 1);
      if ( v40[0] > 0 )
      {
        rf_vector_copy(&out_corrected_position, v30, source);
        if ( rf_vector_dot(out_orientation, vector) <= 0.0 )
        {
          v6 = rf_vector_cross(vector, v25, v48);
          rf_vector_copy(v47, v24, v6);
          rf_vector_normalize(v47);
          v7 = rf_vector_cross(v47, v23, vector);
          rf_vector_copy(v48, v22, v7);
        }
        else
        {
          v4 = rf_vector_cross(v48, v29, vector);
          rf_vector_copy(v47, v28, v4);
          rf_vector_normalize(v47);
          v5 = rf_vector_cross(vector, v27, v47);
          rf_vector_copy(v48, v26, v5);
        }
        v8 = rf_vector_cross(v47, v21, v48);
        rf_vector_copy(out_orientation, v20, v8);
        if ( rf_multiplayer_runtime_mode )
        {
          v9 = rf_vector_multiply_scalar(vector, scaled_result, flt_66151C);
          v10 = rf_vector_add(&out_corrected_position, sum_result, v9);
          rf_vector_copy(&out_corrected_position, v17, v10);
        }
        v45 = rf_item_instance_spawn(
                v43,
                (char *)&byte_631AFD,
                v34,
                entity[11],
                (int)&out_corrected_position,
                (int)out_orientation,
                -1,
                0,
                0);
        if ( a2 )
          rf_ai_publish_deferred_route_context(entity[1299], v43, &out_corrected_position);
      }
      if ( v45 )
      {
        *(_DWORD *)(v45 + 700) |= 8u;
        if ( v40[0] > 0 )
        {
          rf_model_handle_bounds_aabb_adapter(*(_DWORD *)(v45 + 128), (int)rhs, (int)lhs);
          v11 = rf_vector_multiply_scalar(vector, v16, lhs[0]);
          rf_vector_accumulate((float *)(v45 + 228), v11);
          rf_vector_copy((float *)(v45 + 60), v15, (const float *)(v45 + 228));
        }
      }
    }
  }
  return v45;
}

