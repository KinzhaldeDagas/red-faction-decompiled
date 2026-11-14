// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005971D0 rf_file_transfer_accept_offer
// UNREALRED VERIFIED [file-transfer-20261028]: Logical inputs peer,wire ID,name,total,CRC (decompiler also shows unused first argument). Disabled global0x1BC3CC0 or no free slot sends rejection. Initializes receive flags5,total+408,CRC+416,peer+420,10-second deadline+424,WORD ID+432,name+4 and temporary path+68 from global prefix plus name; path selector+428 starts at0x66479C. Invokes configured callback0x1BC3CB8(slot), allowing selector/flags adjustments. Flag0x800 or temporary open failure sends reject and clears flags. Else deletes existing final named file, opens temporary path for writing, sets flag0x20 and sends ACK. Unbounded string copies; does not explicitly zero completed+412 in this body. Return is sender callback result, not slot.
int __cdecl rf_file_transfer_accept_offer(int a1, int a2, __int16 a3, const char *a4, int a5, int a6)
{
  int result; // eax
  char *v8; // [esp+Ch] [ebp-40h]
  const char *v9; // [esp+20h] [ebp-2Ch]
  char v10; // [esp+27h] [ebp-25h]
  _BYTE *v11; // [esp+2Ch] [ebp-20h]
  char *v12; // [esp+30h] [ebp-1Ch]
  char v13; // [esp+37h] [ebp-15h]
  _BYTE *v14; // [esp+3Ch] [ebp-10h]
  const char *v15; // [esp+40h] [ebp-Ch]
  int inactive_slot; // [esp+44h] [ebp-8h]
  int *v17; // [esp+48h] [ebp-4h]

  if ( unk_1BC3CC0 )
    return rf_file_transfer_send_reject_packet(a2, a3);
  inactive_slot = rf_file_transfer_find_inactive_slot();
  if ( inactive_slot == -1 )
    return rf_file_transfer_send_reject_packet(a2, a3);
  v17 = &unk_1BC3CC8[109 * inactive_slot];
  *v17 = 0;
  *v17 |= 5u;
  v17[102] = a5;
  v17[104] = a6;
  v17[105] = a2;
  rf_replicator_arm_milliseconds(v17 + 106, 10000);
  *((_WORD *)v17 + 216) = a3;
  v15 = a4;
  v14 = v17 + 1;
  do
  {
    v13 = *v15;
    *v14++ = *v15++;
  }
  while ( v13 );
  v12 = aVsx;
  v11 = v17 + 17;
  do
  {
    v10 = *v12;
    *v11++ = *v12++;
  }
  while ( v10 );
  v9 = &a4[strlen(a4) + 1];
  v8 = (char *)v17 + 67;
  while ( *++v8 )
    ;
  qmemcpy(v8, a4, v9 - a4);
  v17[107] = dword_66479C;
  unk_1BC3CB8(inactive_slot);
  if ( (*v17 & 0x800) != 0
    || (rf_vfile_unlink_resolved_loose_source((int)(v17 + 33), (char *)v17 + 4, v17[107]),
        rf_vfile_open_with_extension_cache_control_paths(v17 + 33, (char *)v17 + 68, 2, (char *)v17[107]) < 0) )
  {
    result = rf_file_transfer_send_reject_packet(a2, a3);
    *v17 = 0;
  }
  else
  {
    *v17 |= 0x20u;
    return rf_file_transfer_send_ack_packet(a2, a3);
  }
  return result;
}

