// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ED760 rf_acm_stream_convert_buffer_once
// UNREALRED VERIFIED [audio-streaming-20261028]: Arguments ACM handle,source bytes/length,destination bytes/capacity,used-destination output,used-source output. Requires global0x1F6710C nonzero. Zeroes84-byte ACMSTREAMHEADER,fills pointers/lengths,PrepareHeader flags0,Convert flags0,outputs used byte counts,UnprepareHeader flags0. Any API error returns-1,otherwise0. Convert failure returns WITHOUT unpreparing successfully prepared header; unprepare failure occurs after outputs written. No output initialization on early failure,codec reset or output-length postvalidation.
int __cdecl rf_acm_stream_convert_buffer_once(
        HACMSTREAM has,
        BYTE *a2,
        DWORD a3,
        BYTE *a4,
        DWORD a5,
        DWORD *a6,
        DWORD *a7)
{
  struct tACMSTREAMHEADER pash; // [esp+0h] [ebp-60h] BYREF
  MMRESULT v9; // [esp+5Ch] [ebp-4h]

  if ( !unk_1F6710C )
    return -1;
  memset(&pash, 0, sizeof(pash));
  pash.cbStruct = 84;
  pash.pbSrc = a2;
  pash.cbSrcLength = a3;
  pash.pbDst = a4;
  pash.cbDstLength = a5;
  v9 = acmStreamPrepareHeader(has, &pash, 0);
  if ( v9 )
    return -1;
  v9 = acmStreamConvert(has, &pash, 0);
  if ( v9 )
    return -1;
  *a6 = pash.cbDstLengthUsed;
  *a7 = pash.cbSrcLengthUsed;
  v9 = acmStreamUnprepareHeader(has, &pash, 0);
  if ( v9 )
    return -1;
  else
    return 0;
}

