// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005979D0 rf_file_transfer_create_send_slot
// UNREALRED VERIFIED [file-transfer-20261028]: Arguments peer,name,path selector,extra flags. Disabled or no free slot returns-1. Copies name unbounded to record+4, opens vfile+132 for reading, requires positive size then records total+408 and completed+412=0. Computes CRC32 via temporary vfile object, seeks source to0, sets active/send/pending flags0xB OR caller flags, peer+420 and next WORD wire ID+432; returns slot. Failures close opened source, return-1; record may retain copied fields. Does not send offer until service routine.
int __cdecl rf_file_transfer_create_send_slot(int a1, char *Str, char *a3, int a4)
{
  char v5; // al
  int size; // eax
  _BYTE *v7; // [esp+Ch] [ebp-154h]
  char *v8; // [esp+10h] [ebp-150h]
  int v9; // [esp+14h] [ebp-14Ch]
  int self[71]; // [esp+2Ch] [ebp-134h] BYREF
  int inactive_slot; // [esp+14Ch] [ebp-14h]
  int *v12; // [esp+150h] [ebp-10h]
  int v13; // [esp+15Ch] [ebp-4h]

  rf_vfile_construct_unopened(self);
  v13 = 0;
  if ( unk_1BC3CC0 )
    goto LABEL_4;
  inactive_slot = rf_file_transfer_find_inactive_slot();
  if ( inactive_slot == -1 )
    goto LABEL_4;
  v12 = &unk_1BC3CC8[109 * inactive_slot];
  v12[105] = -1;
  *v12 = 0;
  v8 = Str;
  v7 = v12 + 1;
  do
  {
    v5 = *v8;
    *v7++ = *v8++;
  }
  while ( v5 );
  if ( rf_vfile_open_with_extension_cache_control_paths(v12 + 33, Str, 1, a3) < 0 )
    goto LABEL_4;
  size = rf_vfile_get_size((int)(v12 + 33), nullptr, (int)byte_98967F);
  v12[102] = size;
  if ( v12[102] <= 0 )
  {
    if ( rf_vfile_has_nonnegative_stream_slot(v12 + 33) )
      rf_vfile_close_stdio_or_vpp(v12 + 33);
LABEL_4:
    v13 = -1;
    rf_vfile_destruct_close_if_open(self);
    return -1;
  }
  v12[103] = 0;
  if ( rf_vfile_compute_raw_crc32(self, v12 + 104, (char *)v12 + 4, (int)a3) < 0 )
  {
    if ( rf_vfile_has_nonnegative_stream_slot(v12 + 33) )
      rf_vfile_close_stdio_or_vpp(v12 + 33);
    goto LABEL_4;
  }
  rf_vfile_seek(v12 + 33, 0, 0);
  *v12 |= 0xBu;
  *v12 |= a4;
  v12[105] = a1;
  *((_WORD *)v12 + 216) = rf_file_transfer_next_wire_id();
  v9 = inactive_slot;
  v13 = -1;
  rf_vfile_destruct_close_if_open(self);
  return v9;
}

