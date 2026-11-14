// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00598040 rf_file_transfer_set_path_selector
// UNREALRED VERIFIED [file-transfer-20261028]: Arguments unsigned slot, virtual-file path/source selector. For slot<60 with flags bit1 set and nonempty name, writes selector at record+428. Records at 0x1BC3CC8 stride436. Selector is passed to virtual-file open, resolve, CRC, rename and unlink helpers. Does not set peer or associate another transfer. Incidental EAX is not a success status and is uninitialized on out-of-range entry.
unsigned int __cdecl rf_file_transfer_set_path_selector(unsigned int a1, int a2)
{
  unsigned int result; // eax
  char *v3; // [esp+8h] [ebp-8h]
  char *v4; // [esp+Ch] [ebp-4h]

  if ( a1 < 0x3C )
  {
    result = 436 * a1;
    if ( (unk_1BC3CC8[109 * a1] & 1) != 0 )
    {
      v3 = (char *)&unk_1BC3CCC + 436 * a1 + 1;
      v4 = (char *)&unk_1BC3CCC + 436 * a1 + strlen((const char *)&unk_1BC3CCC + 436 * a1) + 1;
      result = v4 - v3;
      if ( v4 != v3 )
        unk_1BC3E74[109 * a1] = a2;
    }
  }
  return result;
}

