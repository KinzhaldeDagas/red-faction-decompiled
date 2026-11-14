// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00596730 rf_file_transfer_send_next_chunk_or_finish
// UNREALRED VERIFIED [transfer-scene-20261028]: Record pointer. Signed completed+412 < total+408 selects data: computes capacity490-(strlen(name+4)+4), chooses min(remaining,capacity) with signed comparison, stores WORD count, increments completed BEFORE reading. Reads count via0x5A0230(member+132,buffer,count,0,0). Exact read sends opcode3,WORD wire ID,WORD byte count,data, length=count+5, and arms10-second deadline. Short read sends reject then aborts; increment is not rolled back. If completed>=total, sets end-wait0x40, arms deadline and sends opcode4. Does not wait for ACK here or mark success; ACK handler schedules next call. No filename length/capacity guard, so pathological lengths may wrap WORD count. Return is sender callback or abort result, not a uniform byte count.
int __cdecl rf_file_transfer_send_next_chunk_or_finish(int a1)
{
  int buffered_bytes_versioned; // eax
  int v3; // [esp+10h] [ebp-218h]
  unsigned int v4; // [esp+14h] [ebp-214h]
  _BYTE v5[3]; // [esp+18h] [ebp-210h] BYREF
  unsigned __int16 v6; // [esp+1Bh] [ebp-20Dh]
  char v7[511]; // [esp+1Dh] [ebp-20Bh] BYREF
  unsigned __int16 v8; // [esp+220h] [ebp-8h]
  char v9; // [esp+227h] [ebp-1h]

  if ( *(_DWORD *)(a1 + 412) < *(_DWORD *)(a1 + 408) )
  {
    v4 = strlen((const char *)(a1 + 4)) + 4;
    if ( *(_DWORD *)(a1 + 408) - *(_DWORD *)(a1 + 412) < (int)(490 - v4) )
      v8 = *(_WORD *)(a1 + 408) - *(_WORD *)(a1 + 412);
    else
      v8 = 490 - v4;
    *(_DWORD *)(a1 + 412) += v8;
    v9 = 3;
    v5[0] = 3;
    *(_WORD *)&v5[1] = *(_WORD *)(a1 + 432);
    v6 = v8;
    buffered_bytes_versioned = rf_vfile_read_buffered_bytes_versioned((int *)(a1 + 132), v7, v8, 0, 0);
    if ( buffered_bytes_versioned == v8 )
    {
      v3 = v8 + 5;
      rf_replicator_arm_milliseconds((int *)(a1 + 424), 10000);
      return unk_1BC3CBC(*(_DWORD *)(a1 + 420), v5, v3);
    }
    else
    {
      rf_file_transfer_send_reject_packet(*(_DWORD *)(a1 + 420), *(_WORD *)(a1 + 432));
      return rf_file_transfer_abort_record(a1);
    }
  }
  else
  {
    *(_DWORD *)a1 |= 0x40u;
    rf_replicator_arm_milliseconds((int *)(a1 + 424), 10000);
    return rf_file_transfer_send_finish_packet(a1);
  }
}

