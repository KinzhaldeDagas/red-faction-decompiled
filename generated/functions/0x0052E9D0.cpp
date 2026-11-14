// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052E9D0 rf_geomod_boolean_mode6_apply_immediate
// UNREALRED VERIFIED [combat-native-query-20261104]: Initial liquid mode6 disables spatial classifier, runs stage0/1, stage2 with(excludeWorld=true,operand0), custom selected-room classification and mode6 face actions, then unused-vertex cleanup. Global solid/workspace order and room order differ when reverse clones prepend globally but append to room tails. Preserve vertex identity through any bijective unused-slot compaction.
int __cdecl rf_geomod_boolean_mode6_apply_immediate(void **a1, void **a2, float *a3)
{
  int result; // eax
  int v4; // [esp+Ch] [ebp-4h]

  v4 = rf_geomod_spatial_classifier_enabled;
  rf_geomod_spatial_classifier_enabled = 0;
  rf_geomod_primary_affected_room = nullptr;
  dword_D4B88C = (int)a1;
  unk_D4B7C8 = (int)a2;
  dword_D4B890 = 6;
  unk_D4B8E4 = 0;
  unk_D4B7D5 = 0;
  unk_D4B7D4 = 0;
  unk_D4B7D0 = 0;
  unk_D4B7F0 = 0;
  unk_D4B894 = 0;
  unk_D4B8E8 = 0.0;
  unk_D4B8DC = 0;
  rf_geomod_boolean_stage_0_merge(a1, a2, nullptr, nullptr, 0.0, nullptr, nullptr);
  rf_geomod_boolean_stage_1_candidates((int *)dword_D4B88C, dword_D4B890);
  rf_geomod_boolean_stage_2_split((_DWORD *)dword_D4B88C, 1, 0);
  rf_geomod_classify_cutter_faces_against_selected_room(dword_D4B88C, a3);
  rf_geomod_boolean_mode6_face_policy_apply(dword_D4B88C, dword_D4B890, a3);
  result = rf_geomod_boolean_stage_6_cleanup(dword_D4B88C);
  rf_geomod_spatial_classifier_enabled = v4;
  return result;
}

