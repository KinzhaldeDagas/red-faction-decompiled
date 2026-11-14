// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00596470 rf_file_transfer_abort_record
// UNREALRED VERIFIED [file-transfer-20261028]: Record pointer. Clears flags0x70 and sets error bit0x100, closes open virtual file+132, deletes named receive temporary path+68 using selector+428, disarms Replicator+424 with-1. If auto-release bit0x8000 set, invokes0x596B20 using record index. Finally clears all flags unconditionally. Does not itself send a rejection packet. EAX is previous auto-release mask, not transfer status.
int __cdecl rf_file_transfer_abort_record(int a1)
{
  int result; // eax

  *(_DWORD *)a1 &= 0xFFFFFF8F;
  *(_DWORD *)a1 |= 0x100u;
  if ( rf_vfile_has_nonnegative_stream_slot((_DWORD *)(a1 + 132)) )
    rf_vfile_close_stdio_or_vpp((int *)(a1 + 132));
  if ( (*(_DWORD *)a1 & 4) != 0 && a1 + 4 + strlen((const char *)(a1 + 4)) + 1 != a1 + 5 )
    rf_vfile_unlink_resolved_loose_source(a1 + 132, (char *)(a1 + 68), *(_DWORD *)(a1 + 428));
  rf_replicator_arm_milliseconds((int *)(a1 + 424), -1);
  result = *(_DWORD *)a1 & 0x8000;
  if ( result )
    rf_file_transfer_release_slot_preserve_success((a1 - (int)unk_1BC3CC8) / 436);
  *(_DWORD *)a1 = 0;
  return result;
}

