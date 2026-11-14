// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C39E0 rf_geomod_impact_chunk_recycle
// UNREALRED VERIFIED [impact-callbacks-20261028]: Unconditionally decrements rf_geomod_impact_chunk_count, unlinks chunk from doubly-linked list using next+0/prev+4, clears links then inserts before free sentinel rf_geomod_impact_chunk_free_head via tail0x81524C. Returns0. Does not operator-delete memory, release texture or clear payload; invalid/double recycle can corrupt lists/count.
int __cdecl rf_geomod_impact_chunk_recycle(_DWORD **a1)
{
  --rf_geomod_impact_chunk_count;
  *a1[1] = *a1;
  (*a1)[1] = a1[1];
  *a1 = nullptr;
  a1[1] = nullptr;
  a1[1] = (_DWORD *)unk_81524C;
  *a1 = &rf_geomod_impact_chunk_free_head;
  *unk_81524C = a1;
  unk_81524C = a1;
  return 0;
}

