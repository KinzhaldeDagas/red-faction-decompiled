// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00597DC0 rf_file_transfer_release_slot_delete_receive_file
// UNREALRED VERIFIED [file-transfer-20261028]: Valid active named slot only. Closes open virtual-file member+132; receive bit4 triggers unlink of record temporary path+68 with selector+428, regardless completion bit0x80. Sets peer+420=-1 and flags=0. Other fields remain. Does not send a protocol message or call a completion callback.
void __cdecl rf_file_transfer_release_slot_delete_receive_file(unsigned int a1)
{
  int *v1; // [esp+20h] [ebp-4h]

  if ( a1 < 0x3C
    && (unk_1BC3CC8[109 * a1] & 1) != 0
    && (char *)&unk_1BC3CCC + 436 * a1 + strlen((const char *)&unk_1BC3CCC + 436 * a1) + 1 != (char *)&unk_1BC3CCC
                                                                                            + 436 * a1
                                                                                            + 1 )
  {
    v1 = &unk_1BC3CC8[109 * a1];
    if ( rf_vfile_has_nonnegative_stream_slot(v1 + 33) )
      rf_vfile_close_stdio_or_vpp(v1 + 33);
    if ( (*v1 & 4) != 0 && (char *)v1 + strlen((const char *)v1 + 4) + 5 != (char *)v1 + 5 )
      rf_vfile_unlink_resolved_loose_source((int)(v1 + 33), (char *)v1 + 68, v1[107]);
    v1[105] = -1;
    *v1 = 0;
  }
}

