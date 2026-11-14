// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052BE50 rf_geomod_boolean_stage_2_split
// UNREALRED VERIFIED [combat-native-query-20261104]: Drains evolving pending pairs from tail. Mode6 caller52E9D0 supplies restricted splitting true,excludedOperand0, so pair division suppresses world-operand splits. After pending pairs finish,52ACE0 runs on BOTH active workspace and backup lists: >16-corner world faces can still split in this later cleanup.
_DWORD *__cdecl rf_geomod_boolean_stage_2_split(_DWORD *a1, char a2, int a3)
{
  float *v4; // [esp+0h] [ebp-Ch]
  float *v5; // [esp+4h] [ebp-8h]

  rf_geomod_boolean_split_face_count = 0;
  while ( rf_geomod_candidate_pair_list_tail != (_DWORD *)&rf_geomod_candidate_pair_list_sentinel )
  {
    v4 = (float *)*rf_geomod_candidate_pair_list_tail;
    v5 = (float *)rf_geomod_candidate_pair_list_tail[1];
    rf_geomod_candidate_pair_remove(rf_geomod_candidate_pair_list_tail);
    rf_geomod_split_candidate_pair(a1, v4, v5, a2, a3);
  }
  sub_52ACE0((int)a1, a1 + 28);
  return sub_52ACE0((int)a1, &dword_D4C528);
}

