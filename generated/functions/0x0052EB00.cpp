// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052EB00 rf_geomod_classify_cutter_faces_against_selected_room
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Cdecl workspace,selectedRoom. ResetD4B7EC=0;forceclass1 onoperand0activefacesonly. ResetD4B7F4/E0;foroperand1class0 incrementattempts, callthiscall532310(face,workspace,selectedRoom),incrementE0 ontrue. NOclassfloodfillinthiswrapper. Storefragmenttotalactivecount+backupcount. Ifglobalspatialenabled&&tempRootD4B90Cnonnull DESTROYtemporarytreeandclearpointer ratherthanmerge into persistentroot. Returnbackupcountorlasttreedestroyresidue. Doesnotdeletefacegeometry or applyactiontable; nullroomargumentnotvalidated.
int __cdecl rf_geomod_classify_cutter_faces_against_selected_room(int a1, float *a2)
{
  int v2; // esi
  int result; // eax
  int i; // [esp+4h] [ebp-4h]
  int j; // [esp+4h] [ebp-4h]

  unk_D4B7EC = 0;
  for ( i = rf_receiver_get_first_dword((void *)(a1 + 112)); i; i = rf_solid_face_next_link(i) )
  {
    if ( !rf_geomod_face_operand_get((_DWORD *)(i + 40)) )
      rf_geomod_face_boolean_class_set((int *)(i + 40), 1);
  }
  unk_D4B7F4 = 0;
  unk_D4B8E0 = 0;
  for ( j = rf_receiver_get_first_dword((void *)(a1 + 112)); j; j = rf_solid_face_next_link(j) )
  {
    if ( rf_geomod_face_operand_get((_DWORD *)(j + 40)) && !rf_geomod_face_boolean_class_get((_DWORD *)(j + 40)) )
    {
      ++unk_D4B7F4;
      if ( sub_532310((float *)j, a1, a2) )
        ++unk_D4B8E0;
    }
  }
  v2 = rf_shared_second_dword_getter_518050((_DWORD *)(a1 + 112));
  result = rf_shared_second_dword_getter_518050(&dword_D4C528);
  rf_geomod_boolean_fragment_count = result + v2;
  if ( rf_geomod_spatial_classifier_enabled && dword_D4B90C )
  {
    result = rf_geomod_spatial_tree_destroy_recursive((int)dword_D4B90C);
    dword_D4B90C = nullptr;
  }
  return result;
}

