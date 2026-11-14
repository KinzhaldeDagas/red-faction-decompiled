// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00596F80 rf_file_transfer_finish_received_file
// UNREALRED VERIFIED [file-transfer-20261028]: Record pointer. Calls0x5932D0, closes open member+132, computes raw CRC32 of temporary path+68 using selector+428. CRC failure/mismatch sets error0x100 and calls0x597DC0 without sending a reply here. On matching CRC, renames temporary file to record name+4 through0x593650. Rename failure sets error0x100, attempts unlink, sends rejection; success sets0x80 and sends ACK. Either rename branch auto-releases through0x596B20 when0x8000 set. Does not compare completed bytes to declared total here.
void __cdecl rf_file_transfer_finish_received_file(int a1)
{
  int v1; // ecx
  int v2; // [esp+0h] [ebp-4h] BYREF

  v2 = v1;
  rf_vfile_flush_stdio_preserve_prior_status((_DWORD *)(a1 + 132));
  if ( rf_vfile_has_nonnegative_stream_slot((_DWORD *)(a1 + 132)) )
    rf_vfile_close_stdio_or_vpp((int *)(a1 + 132));
  v2 = 0;
  if ( rf_vfile_compute_raw_crc32((int *)(a1 + 132), &v2, (char *)(a1 + 68), *(_DWORD *)(a1 + 428)) >= 0
    && v2 == *(_DWORD *)(a1 + 416) )
  {
    if ( rf_vfile_rename_loose_source_with_same_directory_prefix(
           a1 + 132,
           (const char *)(a1 + 4),
           (char *)(a1 + 68),
           *(_DWORD *)(a1 + 428)) )
    {
      *(_DWORD *)a1 |= 0x100u;
      rf_vfile_unlink_resolved_loose_source(a1 + 132, (char *)(a1 + 68), *(_DWORD *)(a1 + 428));
      rf_file_transfer_send_reject_packet(*(_DWORD *)(a1 + 420), *(_WORD *)(a1 + 432));
    }
    else
    {
      *(_DWORD *)a1 |= 0x80u;
      rf_file_transfer_send_ack_packet(*(_DWORD *)(a1 + 420), *(_WORD *)(a1 + 432));
    }
    if ( (*(_DWORD *)a1 & 0x8000) != 0 )
      rf_file_transfer_release_slot_preserve_success((a1 - (int)unk_1BC3CC8) / 436);
  }
  else
  {
    *(_DWORD *)a1 |= 0x100u;
    rf_file_transfer_release_slot_delete_receive_file((a1 - (int)unk_1BC3CC8) / 436);
  }
}

