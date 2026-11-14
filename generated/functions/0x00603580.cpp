// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00603580 rf_jpeg_downsample_dispatch_components
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcsample.c:sep_downsample matched): Dispatches each component to its selected downsampling method: (cinfo, component, inputRows[i]+inRowIndex, outputRows[i]+outRowGroupIndex*v_samp). Component records have an 84-byte stride. Row pointer offsets are scaled by four bytes.
_DWORD *__cdecl rf_jpeg_downsample_dispatch_components(_DWORD *a1, int a2, int a3, int a4, int a5)
{
  _DWORD *result; // eax
  int v6; // [esp+0h] [ebp-14h]
  int v7; // [esp+8h] [ebp-Ch]
  int i; // [esp+Ch] [ebp-8h]

  v6 = a1[88];
  v7 = 0;
  for ( i = a1[16]; ; i += 84 )
  {
    result = a1;
    if ( v7 >= a1[14] )
      break;
    (*(void (__cdecl **)(_DWORD *, int, int, int))(v6 + 4 * v7 + 12))(
      a1,
      i,
      *(_DWORD *)(a2 + 4 * v7) + 4 * a3,
      *(_DWORD *)(a4 + 4 * v7) + 4 * *(_DWORD *)(i + 12) * a5);
    ++v7;
  }
  return result;
}

