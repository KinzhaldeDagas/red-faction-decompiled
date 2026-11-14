// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E5090 rf_player_embedded_options_pack_792
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player configuration packing/file I/O, fpgun type records and parser ECX/stack ABI): Cdecl(destination,source player-options member at player+228). FPU-copy source F32+0 to dst0; byte4->4; LOW BYTE of source DWORD3596->dst5. Leave dst6..7 untouched. For exactly128 entries, copy WORDs source32/34/36 +28*i to packed8/10/12 +6*i. For exactly4 records, packed DWORD776+4*i: bit0=source BYTE3600+16*i LOW1,bit1=BYTE3601 LOW1,bits2..31=LOW30 of source DWORD3604 shifted2. Native writes each packed DWORD three times; final word independent of old high bits. No count-driven loop, buffer/overlap checks or full-record memset. Decoder uses SIGNED30-bit payload, not full32-bit preservation. Returns last packed record DWORD EAX, not bytes written/status. Caller embeds792-byte block at snapshot+264, total snapshot1056.
int __cdecl rf_player_embedded_options_pack_792(int a1, int a2)
{
  int result; // eax
  int j; // [esp+4h] [ebp-Ch]
  int i; // [esp+Ch] [ebp-4h]
  int k; // [esp+Ch] [ebp-4h]

  *(float *)a1 = *(float *)a2;
  *(_BYTE *)(a1 + 4) = *(_BYTE *)(a2 + 4);
  result = a2;
  *(_BYTE *)(a1 + 5) = *(_BYTE *)(a2 + 3596);
  for ( i = 0; i < 128; ++i )
  {
    for ( j = 0; j < 2; ++j )
      *(_WORD *)(a1 + 6 * i + 8 + 2 * j) = *(_WORD *)(a2 + 28 * i + 12 + 2 * j + 20);
    result = a2;
    *(_WORD *)(a1 + 6 * i + 12) = *(_WORD *)(a2 + 28 * i + 36);
  }
  for ( k = 0; k < 4; ++k )
  {
    *(_DWORD *)(a1 + 4 * k + 776) = *(_BYTE *)(a2 + 16 * k + 3600) & 1 | *(_DWORD *)(a1 + 4 * k + 776) & 0xFFFFFFFE;
    *(_DWORD *)(a1 + 4 * k + 776) = (2 * (*(_BYTE *)(a2 + 16 * k + 3601) & 1))
                                  | *(_DWORD *)(a1 + 4 * k + 776) & 0xFFFFFFFD;
    result = (4 * *(_DWORD *)(a2 + 16 * k + 3604)) | *(_DWORD *)(a1 + 4 * k + 776) & 3;
    *(_DWORD *)(a1 + 4 * k + 776) = result;
  }
  return result;
}

