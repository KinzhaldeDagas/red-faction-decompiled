// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051EAF0 rf_pointer_array_find_index
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, plane splits,intrusive face lists,room/portal visibility,clip apertures and decal submission,original ECX/stack flow and PE bytes): Thiscall12-byte array header(count0,capacity4,backing8),DWORD target RET4. Signed ascending i<count, compare raw backingDWORD[i] pointer/value equality; first match returns index, otherwise-1. Count<=0 returns-1; capacity ignored. No append, removal, dereference of elements, tolerance or storage checks. Preserves duplicates and all state.
int __thiscall rf_pointer_array_find_index(_DWORD *this, int a2)
{
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < *this; ++i )
  {
    if ( *(_DWORD *)(*(this + 2) + 4 * i) == a2 )
      return i;
  }
  return -1;
}

