// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059F3C0 rf_vpackfile_entry_read
// UNREALRED VERIFIED [vfile-loose-precedence] Reads payload bytes from the opened VPP entry stream.
size_t __cdecl rf_vpackfile_entry_read(void *Buffer, size_t ElementSize, size_t ElementCount, int a4)
{
  if ( !a4 || !*(_DWORD *)(a4 + 16) )
    return 0;
  if ( *(_DWORD *)(a4 + 20) )
    return fread(Buffer, ElementSize, ElementCount, *(FILE **)(a4 + 20));
  return 0;
}

