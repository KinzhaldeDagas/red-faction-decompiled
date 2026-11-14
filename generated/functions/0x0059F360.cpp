// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059F360 rf_vpackfile_entry_seek
// UNREALRED VERIFIED [vfile-loose-precedence] Translates a member-relative seek to the physical VPP payload offset.
BOOL __cdecl rf_vpackfile_entry_seek(int a1, int Offset, int Origin)
{
  if ( !a1 || !*(_DWORD *)(a1 + 16) )
    return 0;
  if ( *(_DWORD *)(a1 + 20) )
    return fseek(*(FILE **)(a1 + 20), Offset + (*(_DWORD *)(a1 + 8) << 11), Origin) == 0;
  return 0;
}

