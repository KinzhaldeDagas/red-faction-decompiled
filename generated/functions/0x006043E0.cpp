// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006043E0 rf_jpeg_color_rgb_ycc_start
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jccolor.c:rgb_ycc_start matched): Allocates eight 256-entry int32 tables (8192 bytes) in pool 1; converter+8 points to them. For i=0..255: RY=19595*i, GY=38470*i, BY=7471*i+32768, RCb=-11059*i, GCb=-21709*i, shared BCb/RCr=32768*i+0x807FFF, GCr=-27439*i, BCr=-5329*i. Chroma bias is (128<<16)+32767; the half-minus-one rounding prevents a maximum value of 256.
int __cdecl rf_jpeg_color_rgb_ycc_start(int a1)
{
  int result; // eax
  int v2; // [esp+0h] [ebp-Ch]
  int v3; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  v3 = *(_DWORD *)(a1 + 348);
  v2 = (**(int (__cdecl ***)(int, int, int))(a1 + 4))(a1, 1, 0x2000);
  result = v3;
  *(_DWORD *)(v3 + 8) = v2;
  for ( i = 0; i <= 255; ++i )
  {
    *(_DWORD *)(v2 + 4 * i) = 19595 * i;
    *(_DWORD *)(v2 + 4 * i + 1024) = 38470 * i;
    *(_DWORD *)(v2 + 4 * i + 2048) = 7471 * i + 0x8000;
    *(_DWORD *)(v2 + 4 * i + 3072) = -11059 * i;
    *(_DWORD *)(v2 + 4 * i + 4096) = -21709 * i;
    *(_DWORD *)(v2 + 4 * i + 5120) = (char *)&unk_807FFF + 0x8000 * i;
    *(_DWORD *)(v2 + 4 * i + 6144) = -27439 * i;
    result = -5329 * i;
    *(_DWORD *)(v2 + 4 * i + 7168) = -5329 * i;
  }
  return result;
}

