// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CE560 rf_scene_transform_state40_vector_deleting_destructor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): MSVC deleting adapter,element stride40 bytes;used for runtime array+32;previous Concurrency GlobalNode name/type was false. Flag byte mask2 reads element count DWORD atthis-4 and invokes element destructor (verified no-op5FADF0) for each record;mask1 additionally operator deletes cookie base(this-4),returns cookie base even if freed. Without mask2 destroys one element,optionally frees receiver for mask1,returns receiver. Other bits ignored. Does not validate count/allocation or NULL caller pointer;containing owner pointers/counts are not reset here.
void *__thiscall rf_scene_transform_state40_vector_deleting_destructor(void *this, unsigned __int8 a2)
{
  if ( (a2 & 2) != 0 )
  {
    `eh vector destructor iterator'((char *)this, 0x28u, *((_DWORD *)this - 1), rf_saved_receiver_noop_5FADF0);
    if ( (a2 & 1) != 0 )
      operator delete((char *)this - 4);
    return (char *)this - 4;
  }
  else
  {
    rf_saved_receiver_noop_5FADF0(this);
    if ( (a2 & 1) != 0 )
      operator delete(this);
    return this;
  }
}

