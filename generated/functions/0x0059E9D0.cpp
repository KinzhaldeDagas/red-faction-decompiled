// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059E9D0 rf_vpackfile_process_header
// UNREALRED VERIFIED [vpp-streaming] Decodes the 16-byte VPP header. Signature must be 0x51890ACE and the unsigned revision must be nonzero (revision >= 1).
int __cdecl rf_vpackfile_process_header(int a1, int *a2)
{
  int v3; // [esp+0h] [ebp-8h]
  int v4; // [esp+4h] [ebp-4h]

  v4 = *a2;
  v3 = a2[1];
  *(_DWORD *)(a1 + 164) = a2[2];
  *(_DWORD *)(a1 + 172) = a2[3];
  if ( v4 == 1367935694 && v3 )
    return *(_DWORD *)(a1 + 164);
  else
    return 0;
}

