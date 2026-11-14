// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00596550 rf_file_transfer_send_finish_packet
// UNREALRED VERIFIED [transfer-scene-20261028]: Record pointer. Builds opcode4 followed by little-endian WORD wire ID from record+432; invokes sender callback0x1BC3CBC(peer from+420,packet,3). Returns callback result. Does not close source, mark success or release slot. Extra local byte519 is not transmitted.
int __cdecl rf_file_transfer_send_finish_packet(int a1)
{
  _BYTE v2[520]; // [esp+4h] [ebp-208h] BYREF

  v2[519] = 4;
  v2[0] = 4;
  *(_WORD *)&v2[1] = *(_WORD *)(a1 + 432);
  return unk_1BC3CBC(*(_DWORD *)(a1 + 420), v2, 3);
}

