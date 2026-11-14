// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006017A0 rf_jpeg_jinit_huff_encoder
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jchuff.c:jinit_huff_encoder matched): Allocates108-byteentropyobjectimagepool1,cinfo.entropy360=it,start_pass0=601830. Clears4DCderivedptrs44..59,4ACderived60..75,4DCcountptrs76..91,4ACcount92..107. Othercallbacks,savedbitstate,predictorsandrestartfieldsinitializedstartpass. Savedstate12=put_buffer,16=put_bits,20..35=4lastDCs;restartstogo36,nextrestartnum40. No tablegeneration/outputhere;APIvoid.
_DWORD *__cdecl rf_jpeg_jinit_huff_encoder(int a1)
{
  _DWORD *result; // eax
  int i; // [esp+0h] [ebp-8h]
  _DWORD *v3; // [esp+4h] [ebp-4h]

  result = (_DWORD *)(**(int (__cdecl ***)(int, int, int))(a1 + 4))(a1, 1, 108);
  v3 = result;
  *(_DWORD *)(a1 + 360) = result;
  *result = rf_jpeg_huff_start_pass;
  for ( i = 0; i < 4; ++i )
  {
    v3[i + 15] = 0;
    v3[i + 11] = 0;
    v3[i + 23] = 0;
    result = v3;
    v3[i + 19] = 0;
  }
  return result;
}

