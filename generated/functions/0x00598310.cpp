// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00598310 rf_file_transfer_get_progress_fraction
// UNREALRED VERIFIED [file-transfer-20261028]: Unsigned slot<60, active bit1, nonempty name and nonzero total required; otherwise x87 returns -1. Uses signed DWORD completed bytes+412 divided by signed DWORD total+408, rounds through float local, returns via x87. No clamp or normalization; values may be outside0..1.
double __cdecl rf_file_transfer_get_progress_fraction(unsigned int a1)
{
  if ( a1 >= 0x3C
    || (unk_1BC3CC8[109 * a1] & 1) == 0
    || (char *)&unk_1BC3CCC + 436 * a1 + strlen((const char *)&unk_1BC3CCC + 436 * a1) + 1 == (char *)&unk_1BC3CCC
                                                                                            + 436 * a1
                                                                                            + 1 )
  {
    return -1.0;
  }
  if ( !unk_1BC3E60[109 * a1] )
    return -1.0;
  return (float)((double)unk_1BC3E64[109 * a1] / (double)unk_1BC3E60[109 * a1]);
}

