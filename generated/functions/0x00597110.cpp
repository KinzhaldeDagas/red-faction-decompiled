// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00597110 rf_file_transfer_handle_data_chunk
// UNREALRED VERIFIED [file-transfer-20261028]: Arguments receive-record pointer,buffer,byte count. Calls0x5A0990 on virtual file+132. If file status helper reports error, sends rejection, aborts record, then STILL adds count to completed+412 and returns record address. Otherwise increments completed, sends ACK, arms10-second Replicator. Does not cap count against remaining total or verify write count locally.
int *__cdecl rf_file_transfer_handle_data_chunk(int a1, void *Buffer, size_t ElementSize)
{
  rf_vfile_write_bytes_with_optional_feedback((_DWORD *)(a1 + 132), Buffer, ElementSize);
  if ( rf_vfile_get_open_slot_status((_DWORD *)(a1 + 132)) )
  {
    rf_file_transfer_send_reject_packet(*(_DWORD *)(a1 + 420), *(_WORD *)(a1 + 432));
    rf_file_transfer_abort_record(a1);
    *(_DWORD *)(a1 + 412) += ElementSize;
    return (int *)a1;
  }
  else
  {
    *(_DWORD *)(a1 + 412) += ElementSize;
    rf_file_transfer_send_ack_packet(*(_DWORD *)(a1 + 420), *(_WORD *)(a1 + 432));
    return rf_replicator_arm_milliseconds((int *)(a1 + 424), 10000);
  }
}

