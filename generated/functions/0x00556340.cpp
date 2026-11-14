// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556340 rf_pointer_array_append_dword
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Thiscall array header(count0,capacity4,backing8),DWORD value. If count==capacity,grows to2*capacity or16 when zero via549FD0. Saves old count,postincrements count,stores DWORD at backing+4*oldcount,returns old index. No bounds/overflow/allocation failure checks here;also used for owned/borrowed volume pointers. Growth triggers equality only,not count>=capacity.
int __thiscall rf_pointer_array_append_dword(_DWORD *this, int a2)
{
  int v3; // [esp+0h] [ebp-Ch]
  int v5; // [esp+8h] [ebp-4h]

  if ( *this == *(this + 1) )
  {
    if ( *(this + 1) )
      v3 = 2 * *(this + 1);
    else
      v3 = 16;
    rf_dword_array_reallocate_capacity_unchecked(this, v3);
  }
  v5 = (*this)++;
  *(_DWORD *)(*(this + 2) + 4 * v5) = a2;
  return v5;
}

