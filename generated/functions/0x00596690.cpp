// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00596690 rf_file_transfer_send_reject_packet
// UNREALRED VERIFIED [file-transfer-20261028]: Arguments peer,wire ID. Writes packet byte0=1 and little-endian WORD ID at+1, invokes configured sender0x1BC3CBC(peer,packet,3), returns callback result. No slot cleanup or callback pointer validation. Local byte519 is not transmitted.
int __cdecl rf_file_transfer_send_reject_packet(int a1, __int16 a2)
{
  _BYTE v3[520]; // [esp+4h] [ebp-208h] BYREF

  v3[519] = 1;
  v3[0] = 1;
  *(_WORD *)&v3[1] = a2;
  return unk_1BC3CBC(a1, v3, 3);
}

