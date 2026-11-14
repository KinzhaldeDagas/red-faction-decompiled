// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059F320 rf_vpackfile_entry_close
// UNREALRED VERIFIED [vfile-loose-precedence] Closes the per-entry VPP stream handle.
int __cdecl rf_vpackfile_entry_close(int a1)
{
  int result; // eax

  if ( a1 )
  {
    result = a1;
    if ( *(_DWORD *)(a1 + 16) )
    {
      if ( *(_DWORD *)(a1 + 20) )
      {
        result = fclose(*(FILE **)(a1 + 20));
        *(_DWORD *)(a1 + 20) = 0;
      }
    }
  }
  return result;
}

