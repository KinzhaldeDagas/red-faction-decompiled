// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CE400 rf_scene_point_state60_vector_deleting_destructor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): MSVC deleting adapter,element stride60 bytes;used for runtime array+24. Flag byte mask2 reads element count DWORD atthis-4 and invokes element destructor (rf_scene_point_track_release_pool_slot releases its point pool slot) for each record;mask1 additionally operator deletes cookie base(this-4),returns cookie base even if freed. Without mask2 destroys one element,optionally frees receiver for mask1,returns receiver. Other bits ignored. Does not validate count/allocation or NULL caller pointer;containing owner pointers/counts are not reset here.
char *__thiscall rf_scene_point_state60_vector_deleting_destructor(char *this, char a2)
{
  if ( (a2 & 2) != 0 )
  {
    `eh vector destructor iterator'(
      this,
      0x3Cu,
      *((_DWORD *)this - 1),
      (void (__thiscall *)(void *))rf_scene_point_track_release_pool_slot);
    if ( (a2 & 1) != 0 )
      operator delete(this - 4);
    return this - 4;
  }
  else
  {
    rf_scene_point_track_release_pool_slot((int *)this);
    if ( (a2 & 1) != 0 )
      operator delete(this);
    return this;
  }
}

