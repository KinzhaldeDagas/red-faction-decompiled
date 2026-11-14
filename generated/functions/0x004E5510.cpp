// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E5510 rf_player_embedded_options_unpack_792
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player configuration packing/file I/O, fpgun type records and parser ECX/stack ABI): Cdecl(destination player-options member at player+228,packed source). FPU-copy F32 source0 to dst0; byte4->4; ZERO-EXTEND source BYTE5 into DWORD dst3596. Exactly128 entries copy WORDs packed8/10/12+6*i into dst32/34/36+28*i, leaving other28-byte entry fields unchanged. Four packed DWORDs776+4*i yield normalized booleans to BYTE dst3600/3601+16*i and ARITHMETIC RIGHT SHIFT2 to DWORD dst3604+16*i. Thus sign-extends30-bit payload (range -2^29..2^29-1), not unsigned shift or lossless32-bit roundtrip. No enum/count/size/pointer/overlap validation or full record initialization. Native EAX48 after final record is incidental, not success/count.
int __cdecl rf_player_embedded_options_unpack_792(int a1, int a2)
{
  int result; // eax
  int j; // [esp+4h] [ebp-Ch]
  int i; // [esp+Ch] [ebp-4h]
  int k; // [esp+Ch] [ebp-4h]

  *(float *)a1 = *(float *)a2;
  *(_BYTE *)(a1 + 4) = *(_BYTE *)(a2 + 4);
  result = *(unsigned __int8 *)(a2 + 5);
  *(_DWORD *)(a1 + 3596) = result;
  for ( i = 0; i < 128; ++i )
  {
    for ( j = 0; j < 2; ++j )
      *(_WORD *)(a1 + 28 * i + 12 + 2 * j + 20) = *(_WORD *)(a2 + 6 * i + 8 + 2 * j);
    result = a2;
    *(_WORD *)(a1 + 28 * i + 36) = *(_WORD *)(a2 + 6 * i + 12);
  }
  for ( k = 0; k < 4; ++k )
  {
    *(_BYTE *)(a1 + 16 * k + 3600) = (*(_DWORD *)(a2 + 4 * k + 776) & 1) != 0;
    *(_BYTE *)(a1 + 16 * k + 3601) = (*(_DWORD *)(a2 + 4 * k + 776) & 2) != 0;
    result = 16 * k;
    *(_DWORD *)(a1 + 16 * k + 3604) = *(int *)(a2 + 4 * k + 776) >> 2;
  }
  return result;
}

