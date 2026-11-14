// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C4AA0 rf_geomod_impact_chunk_allocate
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original fragment spawn and bounded pool, eight-vertex twelve-triangle layout, fourteen-ray scoring, full room-pointer ABI and native glass branching): 
// Cdecl no args returns raw chunk. Signed activeCount814FA4<80: increments count and selects first free node815248.next. Otherwise selects first/oldest active node814FB0.next without
// count change (even count>80). Unlinks selected node through next0/prev4, clears links, appends at active tail814FB4, returns node. At capacity oldest active is reused/moved to tail
// directly, not sent through recycle helper. No heap allocation, payload memset, material/resource release, list-empty/count-consistency guard or NULL failure path. Requires
// initialized consistent80-record pool; corrupt count/list can select sentinel. Native XOR/JNZ tails are dead.
_DWORD **rf_geomod_impact_chunk_allocate()
{
  _DWORD **v1; // [esp+0h] [ebp-4h]

  if ( rf_geomod_impact_chunk_count < 80 )
  {
    ++rf_geomod_impact_chunk_count;
    v1 = (_DWORD **)rf_geomod_impact_chunk_free_head;
  }
  else
  {
    v1 = (_DWORD **)rf_geomod_impact_chunk_active_head;
  }
  *v1[1] = *v1;
  (*v1)[1] = v1[1];
  *v1 = nullptr;
  v1[1] = nullptr;
  v1[1] = (_DWORD *)rf_geomod_impact_chunk_active_tail;
  *v1 = &rf_geomod_impact_chunk_active_head;
  *rf_geomod_impact_chunk_active_tail = v1;
  rf_geomod_impact_chunk_active_tail = v1;
  return v1;
}

