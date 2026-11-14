// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CEBE0 rf_scene_pool48_vector_deleting_destructor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): MSVC deleting adapter,element stride48 bytes;used for definition pool+284. Flag byte mask2 reads element count DWORD atthis-4 and invokes element destructor (verified no-op5F8750) for each record;mask1 additionally operator deletes cookie base(this-4),returns cookie base even if freed. Without mask2 destroys one element,optionally frees receiver for mask1,returns receiver. Other bits ignored. Does not validate count/allocation or NULL caller pointer;containing owner pointers/counts are not reset here.
char *__thiscall rf_scene_pool48_vector_deleting_destructor(char *this, char a2)
{
  if ( (a2 & 2) != 0 )
  {
    `eh vector destructor iterator'(this, 0x30u, *((_DWORD *)this - 1), rf_saved_receiver_noop_5F8750);
    if ( (a2 & 1) != 0 )
      operator delete(this - 4);
    return this - 4;
  }
  else
  {
    rf_saved_receiver_noop_5F8750(this);
    if ( (a2 & 1) != 0 )
      operator delete(this);
    return this;
  }
}

