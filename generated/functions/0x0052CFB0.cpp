// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052CFB0 rf_geomod_fragments_classify_spatial
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Cdecl workspace,mode. ResetD4B7EC=0. Mode5 setsclass1 ONLYoperand0 activefaces;mode6 setsclass1 onALLactivefaces;othermodesno preforce. Resetattempt/flooddiagnosticsD4B7F4/D4B8E0. For eachactiveface whoseclassstill0 incrementattemptcount; operand1 queries532850(face,workspace,persistentroot0),operand0 queries532850(face,workspace,tempCutterRootD4B90C). Trueclassificationreturn incrementsD4B8E0 and invokesclassfloodfill. No initialvertexvisited reset or separateadjacencyclassification pass here. Record fragmenttotal=activecount+backupcount. If spatialglobal stillnonzero andtempRootnonnull calltreeMerge(persistentroot,tempRoot),then cleartempRootNULL (graft,notdestroy). Return
// incidental backupcount/merge result. No actiontablepolicies or deletioninthisstage; mode5 behavior differs fromlinear whichpreforcesALLfaces.
int __cdecl rf_geomod_fragments_classify_spatial(float **a1, int a2)
{
  int v2; // esi
  int result; // eax
  int i; // [esp+4h] [ebp-4h]
  int j; // [esp+4h] [ebp-4h]
  float *k; // [esp+4h] [ebp-4h]

  unk_D4B7EC = 0;
  if ( a2 == 5 )
  {
    for ( i = rf_receiver_get_first_dword(a1 + 28); i; i = rf_solid_face_next_link(i) )
    {
      if ( !rf_geomod_face_operand_get((_DWORD *)(i + 40)) )
        rf_geomod_face_boolean_class_set((int *)(i + 40), 1);
    }
  }
  else if ( a2 == 6 )
  {
    for ( j = rf_receiver_get_first_dword(a1 + 28); j; j = rf_solid_face_next_link(j) )
      rf_geomod_face_boolean_class_set((int *)(j + 40), 1);
  }
  unk_D4B7F4 = 0;
  unk_D4B8E0 = 0;
  for ( k = (float *)rf_receiver_get_first_dword(a1 + 28); k; k = (float *)rf_solid_face_next_link((int)k) )
  {
    if ( !rf_geomod_face_boolean_class_get((_DWORD *)k + 10) )
    {
      ++unk_D4B7F4;
      if ( rf_geomod_face_operand_get((_DWORD *)k + 10) )
      {
        if ( sub_532850(k, (int)a1, *a1) )
        {
          ++unk_D4B8E0;
          rf_geomod_fragment_class_flood_fill(k);
        }
      }
      else if ( sub_532850(k, (int)a1, (float *)dword_D4B90C) )
      {
        ++unk_D4B8E0;
        rf_geomod_fragment_class_flood_fill(k);
      }
    }
  }
  v2 = rf_shared_second_dword_getter_518050(a1 + 28);
  result = rf_shared_second_dword_getter_518050(&dword_D4C528);
  rf_geomod_boolean_fragment_count = result + v2;
  if ( rf_geomod_spatial_classifier_enabled && dword_D4B90C )
  {
    result = rf_spatial_tree_merge((int)*a1, (int)dword_D4B90C);
    dword_D4B90C = nullptr;
  }
  return result;
}

