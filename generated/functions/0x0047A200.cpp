// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047A200 rf_pointer_array_remove_first
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, liquid transition lifecycle, native x87 unordered comparisons, stable pointer erase, static runtime ownership and level-browser flow): 
// Thiscall12-byte pointer array(count0,capacity4,backing8), one stack DWORD value, RET4. Signed scan locates FIRST equal DWORD and delegates erase_index_unchecked, which decrements
// count and shifts later slots left without freeing pointees or clearing stale tail. Then executes empty loop to new count; successful normal EAX is new count, not Boolean. Miss
// performs no deletion; empty-container return is incidental. No duplicate sweep, backing release or capacity change.
int __thiscall rf_pointer_array_remove_first(int *this, int a2)
{
  int result; // eax
  int i; // [esp+4h] [ebp-4h]
  int j; // [esp+4h] [ebp-4h]

  for ( i = 0; i < *this; ++i )
  {
    result = *(_DWORD *)(*(this + 2) + 4 * i);
    if ( result == a2 )
      break;
    result = i + 1;
  }
  if ( i != *this )
  {
    rf_pointer_array_erase_index_unchecked(this, i);
    for ( j = 0; ; ++j )
    {
      result = j;
      if ( j >= *this )
        break;
    }
  }
  return result;
}

