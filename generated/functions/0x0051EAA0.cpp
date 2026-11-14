// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051EAA0 rf_pointer_array_resize_count_unchecked
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): ECX DWORD array header(count0,capacity4,data8), new count as DWORD arg. Nonzero count calls exact-capacity reallocator, which copies OLD count unchecked, so shrinking can overflow new storage. Then sets count to requested value; newly added slots uninitialized. Zero count operator-deletes existing data8 if nonnull BUT leaves data pointer and capacity unchanged/dangling, then count0; later destroy/reuse can double-free or use freed data. Returns requested count bits; no element construction/destruction.
void *__thiscall rf_pointer_array_resize_count_unchecked(void **this, void *a2)
{
  if ( a2 )
  {
    rf_dword_array_reallocate_capacity_unchecked(this, (int)a2);
  }
  else if ( *(this + 2) )
  {
    operator delete(*(this + 2));
  }
  *this = a2;
  return a2;
}

