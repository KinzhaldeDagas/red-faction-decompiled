// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00596970 rf_file_transfer_send_offer_packet
// UNREALRED VERIFIED [file-transfer-20261028]: Record pointer. Sends opcode2,WORD wire ID+432,DWORD name length, name bytes without NUL,DWORD total bytes+408,DWORD expected CRC32+416 through callback0x1BC3CBC(peer+420,packet,nameLength+15). Uses local fixed packet storage without name-length bound checking. Returns callback result; does not arm timeout itself.
int __cdecl rf_file_transfer_send_offer_packet(int a1)
{
  int v2; // [esp+8h] [ebp-218h]
  unsigned int v3; // [esp+Ch] [ebp-214h]
  _BYTE v4[7]; // [esp+18h] [ebp-208h] BYREF
  _BYTE v5[513]; // [esp+1Fh] [ebp-201h] BYREF

  v5[512] = 2;
  v4[0] = 2;
  *(_WORD *)&v4[1] = *(_WORD *)(a1 + 432);
  v2 = a1 + 5;
  v3 = a1 + 4 + strlen((const char *)(a1 + 4)) + 1;
  *(_DWORD *)&v4[3] = v3 - (a1 + 5);
  memcpy(v5, (const void *)(a1 + 4), *(size_t *)&v4[3]);
  *(_DWORD *)&v4[v3 - v2 + 7] = *(_DWORD *)(a1 + 408);
  *(_DWORD *)&v4[v3 - v2 + 11] = *(_DWORD *)(a1 + 416);
  return unk_1BC3CBC(*(_DWORD *)(a1 + 420), v4, v3 - (a1 + 5) + 15);
}

