// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005965F0 rf_file_transfer_send_ack_packet
// UNREALRED VERIFIED [file-transfer-20261028]: Arguments peer,wire ID. Writes packet byte0=0 and little-endian WORD ID at+1, invokes configured sender0x1BC3CBC(peer,packet,3), returns callback result. No callback pointer validation. Local byte519 is initialized but not transmitted.
int __cdecl rf_file_transfer_send_ack_packet(int a1, __int16 a2)
{
  _BYTE v3[520]; // [esp+4h] [ebp-208h] BYREF

  v3[519] = 0;
  v3[0] = 0;
  *(_WORD *)&v3[1] = a2;
  return unk_1BC3CBC(a1, v3, 3);
}

