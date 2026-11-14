// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005922D0 rf_vfile_is_special_path
// UNREALRED VERIFIED [streaming-contract-20260829] Classifies drive-colon, leading-forward-slash, and leading-backslash requests as special paths before any loose-table or VPP lookup.
bool __stdcall rf_vfile_is_special_path(_BYTE *a1)
{
  if ( a1[1] == 58 )
    return 1;
  return *a1 == 47 || *a1 == 92;
}

