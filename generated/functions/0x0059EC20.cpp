// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059EC20 rf_vpackfile_setup_file_offsets
// UNREALRED VERIFIED [vpp-streaming] Assigns payload offsets in 0x800-byte blocks, beginning after the 0x800-byte header and all aligned table blocks.
int __cdecl rf_vpackfile_setup_file_offsets(int a1, int a2)
{
  int result; // eax
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = i;
    if ( i >= *(_DWORD *)(a1 + 164) )
      break;
    *(_DWORD *)(*(_DWORD *)(a1 + 168) + 24 * i + 8) = a2;
    a2 += (unsigned int)(*(_DWORD *)(*(_DWORD *)(a1 + 168) + 24 * i + 12) + 2047) >> 11;
  }
  return result;
}

