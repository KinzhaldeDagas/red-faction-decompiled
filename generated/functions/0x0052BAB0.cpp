// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052BAB0 rf_geomod_collect_candidate_faces_from_tree
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Cdecl operand,outCountPointer,outFacePointerArray,root,optionalOpposingMin,optionalOpposingMax. Two fixed1024-DWORD local stacks fornodes/classifications, uncheckedcapacity. Seedroot with state0. State0: ifBOTH boundsnonnull, ordinary inclusiveAABB overlap failure ->state2; overlap ->52BE00 endpoint-inside test yieldsstate1 ifnodefullycontained else0. Missingbounds ->state2. Selectedtable[40*operand+5*GLOBALmodeD4B890+state]==2 prunes ENTIRE nodeandchildren. Else push child32 then36 withsame state; popLIFO so36first. Iterate nodeface-list24:state1 setsfaceclass0, state2 setsclass2 and incrementsD4B7E8;state0 outsidefacebounds/missingbounds
// similarlyclass2,otherwiseleaveexistingclass. Then require tableaction!=2 and(terraineligible ORglobalmode==6). Appendface to callerarray[*count]++,removefrombackupD4C528,tailappend GLOBALworkspaceD4B88C.face112. Eligibility differs fromlinearstage1: mode6 override,not explicitliquidpredicate. No operand filter againstfacebit (caller/treeassumption), geometricplane test, nullroot/output/capacity guard, allocation or actualspatial-node removal. Return incidental lastclassification/helperresult, not emittedcount.
int __cdecl rf_geomod_collect_candidate_faces_from_tree(int a1, _DWORD *a2, int a3, int a4, float *a5, float *a6)
{
  int result; // eax
  _DWORD *v7; // esi
  int i; // [esp+8h] [ebp-2010h]
  int v9; // [esp+Ch] [ebp-200Ch]
  int v10; // [esp+10h] [ebp-2008h]
  int v11; // [esp+14h] [ebp-2004h]
  _DWORD v12[1024]; // [esp+18h] [ebp-2000h]
  _DWORD v13[1024]; // [esp+1018h] [ebp-1000h]

  v12[0] = a4;
  v13[0] = 0;
  result = 1;
  v11 = 1;
  while ( v11 > 0 )
  {
    v10 = v12[--v11];
    v9 = v13[v11];
    if ( !v9 )
    {
      if ( a5 && a6 )
      {
        if ( rf_aabb_overlap_inclusive(a5, a6, (float *)v10, (float *)(v10 + 12)) )
          v9 = rf_aabb_min_max_points_inside_aabb((float *)v10, a5, a6);
        else
          v9 = 2;
      }
      else
      {
        v9 = 2;
      }
    }
    result = v9;
    if ( rf_geomod_boolean_action_table[40 * a1 + 5 * dword_D4B890 + v9] != 2 )
    {
      if ( *(_DWORD *)(v10 + 32) )
      {
        v12[v11] = *(_DWORD *)(v10 + 32);
        v13[v11++] = v9;
      }
      if ( *(_DWORD *)(v10 + 36) )
      {
        v12[v11] = *(_DWORD *)(v10 + 36);
        v13[v11++] = v9;
      }
      result = rf_receiver_get_first_dword((void *)(v10 + 24));
      for ( i = result; i; i = result )
      {
        if ( v9 )
        {
          if ( v9 == 1 )
          {
            rf_geomod_face_boolean_class_set((int *)(i + 40), 0);
          }
          else if ( v9 == 2 )
          {
            rf_geomod_face_boolean_class_set((int *)(i + 40), 2);
            ++unk_D4B7E8;
          }
        }
        else if ( !a5 || !a6 || !rf_geomod_face_bounds_overlap_aabb((float *)i, a5, a6) )
        {
          rf_geomod_face_boolean_class_set((int *)(i + 40), 2);
          ++unk_D4B7E8;
        }
        v7 = &rf_geomod_boolean_action_table[40 * a1 + 5 * dword_D4B890];
        if ( v7[rf_geomod_face_boolean_class_get((_DWORD *)(i + 40))] != 2
          && (rf_geomod_terrain_component_face_eligible((__int16 *)(i + 40)) || dword_D4B890 == 6) )
        {
          *(_DWORD *)(a3 + 4 * (*a2)++) = i;
          rf_solid_face_list_remove(&dword_D4C528, i);
          rf_solid_face_list_append((int *)(dword_D4B88C + 112), i);
        }
        result = rf_face_next_spatial_node_link(i);
      }
    }
  }
  return result;
}

