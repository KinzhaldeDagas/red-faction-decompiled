// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00598150 rf_file_transfer_enable_auto_release
// UNREALRED VERIFIED [file-transfer-20261028]: For unsigned slot<60, active bit1 and nonempty name, ORs flags with0x8000. Enables automatic slot cleanup on completion/error/timeout paths, as verified in 0x596EE0,0x596F80,0x596C40 and0x596470. Does not cancel transfer or send packets. Incidental return, not a reliable success status.
int __cdecl rf_file_transfer_enable_auto_release(unsigned int a1)
{
  int result; // eax
  char *v2; // [esp+8h] [ebp-8h]
  char *v3; // [esp+Ch] [ebp-4h]

  if ( a1 < 0x3C )
  {
    result = 436 * a1;
    if ( (unk_1BC3CC8[109 * a1] & 1) != 0 )
    {
      v2 = (char *)&unk_1BC3CCC + 436 * a1 + 1;
      v3 = (char *)&unk_1BC3CCC + 436 * a1 + strlen((const char *)&unk_1BC3CCC + 436 * a1) + 1;
      result = v3 - v2;
      if ( v3 != v2 )
      {
        unk_1BC3CC8[109 * a1] |= 0x8000u;
        return 436 * a1;
      }
    }
  }
  return result;
}

