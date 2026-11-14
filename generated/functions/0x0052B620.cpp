// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052B620 rf_geomod_boolean_stage_1_candidates
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Cdecl workspaceSolid,mode returns paircount. Move solidface header112/116 into globalbackupD4C528/52C byvalue then reset solidhead/count; no copyingfaces. Linearpath ifspatialdisabled ORmode5/6. Iterate backup cachingnext BEFOREmutation. Operand0 faces test transformed cutterboundsD4C530/B910;operand1 faces test worldboundsD4C53C/B91C. If no priorworldflagD4B8FC andoperand1 OR facebounds nooverlap, setclass2 and incrementD4B7E8. Operand0 with selectedaction2 staysbackup unconditionally. Other faces admitted only terraineligible ORliquid; append pointer to operand-specific unchecked scratcharray(worldD50558,cutterD4C558), removefrombackup, tailappend toactive solid112 preserving
// encounterorder. Spatialpath calls52BAB0 operand0 on worldroot vs cutterbounds;operand1 on cuttertemp root vsworldbounds ifpriorworldflag, elseNULLbounds. Reset paircount then nested world-major/cutter-minor loop appends pair when inclusive facebounds helper52B900 passes. Save initialpaircountD4B8F0 andreturncount. No plane intersection/distance test, paircapacity/dedup guard or modevalidation here. Leaves unselectedbackupfaces separate forlaterpublication.
int __cdecl rf_geomod_boolean_stage_1_candidates(int *a1, int a2)
{
  int v2; // edx
  BOOL v3; // eax
  _DWORD *v4; // esi
  float *v6; // [esp-4h] [ebp-28h]
  float *v7; // [esp+4h] [ebp-20h]
  float *v8; // [esp+8h] [ebp-1Ch]
  int link; // [esp+Ch] [ebp-18h]
  int i; // [esp+10h] [ebp-14h]
  int k; // [esp+14h] [ebp-10h]
  int v12; // [esp+18h] [ebp-Ch] BYREF
  int v13; // [esp+1Ch] [ebp-8h] BYREF
  int j; // [esp+20h] [ebp-4h]

  v2 = a1[29];
  dword_D4C528 = a1[28];
  unk_D4C52C = v2;
  rf_intrusive_list_reset_head_tail(a1 + 28);
  v13 = 0;
  v12 = 0;
  if ( !rf_geomod_spatial_classifier_enabled || a2 == 6 || a2 == 5 )
  {
    for ( i = rf_receiver_get_first_dword(&dword_D4C528); i; i = link )
    {
      link = rf_solid_face_next_link(i);
      if ( !unk_D4B8FC && rf_geomod_face_operand_get((_DWORD *)(i + 40))
        || (v6 = &flt_D4B910[3 * rf_geomod_face_operand_get((_DWORD *)(i + 40))],
            v3 = rf_geomod_face_operand_get((_DWORD *)(i + 40)),
            !rf_geomod_face_bounds_overlap_aabb((float *)i, &flt_D4C530[3 * v3], v6)) )
      {
        rf_geomod_face_boolean_class_set((int *)(i + 40), 2);
        ++unk_D4B7E8;
      }
      if ( !rf_geomod_face_operand_get((_DWORD *)(i + 40)) )
      {
        v4 = &rf_geomod_boolean_action_table[40 * rf_geomod_face_operand_get((_DWORD *)(i + 40)) + 5 * a2];
        if ( v4[rf_geomod_face_boolean_class_get((_DWORD *)(i + 40))] == 2 )
          continue;
      }
      if ( rf_geomod_terrain_component_face_eligible((__int16 *)(i + 40)) || rf_face_is_liquid((_DWORD *)(i + 40)) )
      {
        if ( rf_geomod_face_operand_get((_DWORD *)(i + 40)) )
          unk_D4C558[v12++] = i;
        else
          unk_D50558[v13++] = i;
        rf_solid_face_list_remove(&dword_D4C528, i);
        rf_solid_face_list_append(a1 + 28, i);
      }
    }
  }
  else
  {
    rf_geomod_collect_candidate_faces_from_tree(0, &v13, (int)unk_D50558, *a1, flt_D4C530, flt_D4B910);
    if ( unk_D4B8FC )
      rf_geomod_collect_candidate_faces_from_tree(1, &v12, (int)unk_D4C558, (int)dword_D4B90C, &flt_D4C53C, &flt_D4B91C);
    else
      rf_geomod_collect_candidate_faces_from_tree(1, &v12, (int)unk_D4C558, (int)dword_D4B90C, nullptr, nullptr);
  }
  rf_geomod_candidate_pair_count = 0;
  for ( j = 0; j < v13; ++j )
  {
    v8 = (float *)unk_D50558[j];
    for ( k = 0; k < v12; ++k )
    {
      v7 = (float *)unk_D4C558[k];
      if ( rf_geomod_face_bounds_overlap(v8, v7) )
        rf_geomod_candidate_pair_append((int)v8, (int)v7);
    }
  }
  unk_D4B8F0 = rf_geomod_candidate_pair_count;
  return rf_geomod_candidate_pair_count;
}

