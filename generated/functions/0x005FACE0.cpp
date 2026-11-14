// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FACE0 rf_bluebeard_metadata_clear_tables
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Zeroes0xB4000 bytes at0x1F6D330 (4096*180records),0x2800 bytes at0x1F6A968 (256*40groupnames). Sets group count0x1F6D16C=0,filter index0x1F6D24C=-1,cursor0x2021330=-1,global BYTE0x1F6D24B=1. Does not free external resources or COM objects. Returns group-table memset destination as incidental EAX.
void *rf_bluebeard_metadata_clear_tables()
{
  void *result; // eax

  memset(&unk_1F6D330, 0, 0xB4000u);
  result = memset(unk_1F6A968, 0, sizeof(unk_1F6A968));
  dword_1F6D16C = 0;
  dword_1F6D24C = -1;
  dword_2021330 = -1;
  unk_1F6D24B = 1;
  return result;
}

