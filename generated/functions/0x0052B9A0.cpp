// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052B9A0 rf_geomod_candidate_pair_append
// UNREALRED VERIFIED [combat-native-query-20261104]: Candidate nodes append at global pending-list tail;52BE50 pops/processes that tail, giving LIFO ordering. Candidate seed scan order and refreshed-node placement are observable through later split/classification order.
int __cdecl rf_geomod_candidate_pair_append(int a1, int a2)
{
  _DWORD *v3; // [esp+4h] [ebp-4h]

  v3 = operator new(0x10u);
  *v3 = a1;
  v3[1] = a2;
  v3[2] = rf_geomod_candidate_pair_list_tail;
  *(_DWORD *)(rf_geomod_candidate_pair_list_tail + 12) = v3;
  rf_geomod_candidate_pair_list_tail = v3;
  v3[3] = &rf_geomod_candidate_pair_list_sentinel;
  return ++rf_geomod_candidate_pair_count;
}

