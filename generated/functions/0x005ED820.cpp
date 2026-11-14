// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ED820 rf_acm_stream_source_bytes_for_destination_size
// UNREALRED VERIFIED [audio-streaming-20261028]: Calls acmStreamSize(handle,inputBytes,&result,flags1). Returns result on API success,0xFFFFFFFF on failure. Streaming caller supplies desired decoded destination length and interprets result as required encoded source length. No readiness global,range or signedness check in helper.
DWORD __cdecl rf_acm_stream_source_bytes_for_destination_size(HACMSTREAM has, DWORD cbInput)
{
  DWORD pdwOutputBytes; // [esp+4h] [ebp-4h] BYREF

  if ( acmStreamSize(has, cbInput, &pdwOutputBytes, 1u) )
    return -1;
  else
    return pdwOutputBytes;
}

