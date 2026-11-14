// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059F2B0 rf_vpackfile_entry_open
// UNREALRED VERIFIED [vfile-loose-precedence] Opens the containing VPP and seeks to the selected entry's 0x800-byte block offset.
int __cdecl rf_vpackfile_entry_open(int a1)
{
  if ( !a1 || !*(_DWORD *)(a1 + 16) )
    return 0;
  if ( *(_DWORD *)(a1 + 20) )
    return 0;
  *(_DWORD *)(a1 + 20) = fopen((const char *)(*(_DWORD *)(a1 + 16) + 32), "rb");
  if ( !*(_DWORD *)(a1 + 20) )
    return 0;
  fseek(*(FILE **)(a1 + 20), *(_DWORD *)(a1 + 8) << 11, 0);
  return 1;
}

