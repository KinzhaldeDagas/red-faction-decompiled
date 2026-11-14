// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00596F60 rf_file_transfer_handle_reject
// UNREALRED VERIFIED [file-transfer-20261028]: Record-pointer wrapper returning0x596470 result. Aborts locally; does not send an additional rejection packet.
int __cdecl rf_file_transfer_handle_reject(int a1)
{
  return rf_file_transfer_abort_record(a1);
}

