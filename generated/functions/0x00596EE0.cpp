// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00596EE0 rf_file_transfer_handle_ack
// UNREALRED VERIFIED [file-transfer-20261028]: Record pointer, only acts for send bit2. If end-wait bit0x40 set, clears it and sets success0x80; auto-release0x8000 then calls0x596B20. Else if waiting bit0x10 set, invokes0x596730 to send next file chunk. Does not check peer or wire ID; dispatcher already performs lookup.
void __cdecl rf_file_transfer_handle_ack(char *a1)
{
  if ( (*(_DWORD *)a1 & 2) != 0 )
  {
    if ( (*(_DWORD *)a1 & 0x40) != 0 )
    {
      *(_DWORD *)a1 &= ~0x40u;
      *(_DWORD *)a1 |= 0x80u;
      if ( (*(_DWORD *)a1 & 0x8000) != 0 )
        rf_file_transfer_release_slot_preserve_success((a1 - (char *)unk_1BC3CC8) / 436);
    }
    else if ( (*(_DWORD *)a1 & 0x10) != 0 )
    {
      rf_file_transfer_send_next_chunk_or_finish((int)a1);
    }
  }
}

