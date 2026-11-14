// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00591250 rf_sound_sample_get_output_format_fields
// UNREALRED VERIFIED [dsound-buffers-20261028]: Argument source sample INDEX,optional sample-rate,bits,channels outputs. Reads output WAVEFORMAT pointer at0x1951A20+592*index; fields DWORD+4 rate,WORD+14 bits,WORD+2 channels. Writes only nonnull outputs. No sample-index/format-pointer validation. Return last path-dependent loaded field/pointer,undefined when all outputs null; use outputs,not return.
int __cdecl rf_sound_sample_get_output_format_fields(int a1, int *a2, int *a3, _DWORD *a4)
{
  int result; // eax

  if ( a2 )
  {
    result = *(_DWORD *)(unk_1951A20[148 * a1] + 4);
    *a2 = result;
  }
  if ( a3 )
  {
    result = *(unsigned __int16 *)(unk_1951A20[148 * a1] + 14);
    *a3 = result;
  }
  if ( a4 )
  {
    result = unk_1951A20[148 * a1];
    *a4 = *(unsigned __int16 *)(result + 2);
  }
  return result;
}

