// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00461B60 rf_browser_rebuild_filtered_sorted_row_indices
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg. Set visibleCount6F5088=0;for each live raw row0..<6F51A8,if mode-filter461B20 ALnonzero append RAW index into6F52D4 and increment visibleCount (no
// capacity guard);else if rejected raw row equals selected661F9C,set selected=-1. Qsort(indexArray,visibleCount,4,4613B0);does NOT reorder108-byte records or endpoint-search order.
// Only selected<0 AND visibleCount>0 picks first sorted raw row. Set selectedDisplayPosition6F52E0=0,scan sorted visible indices for selected raw index;firstmatch stores
// position/returns. Positive out-of-range selection can survive;no-match leaves displayposition0,empty list does not force all selection values to-1. Does not reset scroll6F52E4 or
// query state. Comparator's nonzero equal-key behavior retained,not repaired here.
void rf_browser_rebuild_filtered_sorted_row_indices()
{
  int i; // [esp+0h] [ebp-4h]
  signed int j; // [esp+0h] [ebp-4h]

  MEMORY[0x6F5088] = 0;
  for ( i = 0; i < unk_6F51A8; ++i )
  {
    if ( rf_browser_row_matches_mode_filter(i) )
    {
      *((_DWORD *)MEMORY[0x6F52D4] + MEMORY[0x6F5088]++) = i;
    }
    else if ( dword_661F9C == i )
    {
      dword_661F9C = -1;
    }
  }
  qsort(
    MEMORY[0x6F52D4],
    MEMORY[0x6F5088],
    4u,
    (_CoreCrtNonSecureSearchSortCompareFunction)rf_browser_compare_server_row_indices);
  if ( dword_661F9C < 0 && (int)MEMORY[0x6F5088] > 0 )
    dword_661F9C = *(_DWORD *)MEMORY[0x6F52D4];
  unk_6F52E0 = 0;
  for ( j = 0; j < (int)MEMORY[0x6F5088]; ++j )
  {
    if ( *((_DWORD *)MEMORY[0x6F52D4] + j) == dword_661F9C )
    {
      unk_6F52E0 = j;
      return;
    }
  }
}

