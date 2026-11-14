// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ED850 rf_acm_stream_destination_bytes_for_source_size
// UNREALRED VERIFIED [wave-codec-20261028]: Calls acmStreamSize(handle,sourceByteCount,&output,flags0). Returns output on success,0xFFFFFFFF on API failure. Counterpart0x5ED820 uses flags1 for inverse size query. No range/readiness checks.
DWORD __cdecl rf_acm_stream_destination_bytes_for_source_size(HACMSTREAM has, DWORD cbInput)
{
  DWORD pdwOutputBytes; // [esp+0h] [ebp-8h] BYREF

  if ( acmStreamSize(has, cbInput, &pdwOutputBytes, 0) )
    return -1;
  else
    return pdwOutputBytes;
}

