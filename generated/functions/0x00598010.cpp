// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00598010 rf_file_transfer_disable_new_transfers
// UNREALRED VERIFIED [transfer-scene-20261028]: Sets DWORD global0x1BC3CC0=1 and returns. Both send-slot creation0x5979D0 and incoming offer handler0x5971D0 test this global. Does not abort, close or service existing slots. Original IDA library label ___setargv_1 was misleading; this code does not configure CRT argv.
void rf_file_transfer_disable_new_transfers()
{
  unk_1BC3CC0 = 1;
}

