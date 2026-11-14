// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005901F0 rf_sound_sample_release_reference
// UNREALRED VERIFIED [dsound-creation-20261028]: If sample index>=0,decrements reference DWORD at record+588. Only new zero calls0x58F610 cleanup and decrements global registry count0x1BA1818. Does not compact remaining records,move last record or reset count to highest occupied index; later scans/allocation use the shortened prefix. Negative index has uninitialized/incidental return; positive return varies by path. No upper bound or reference underflow guard.
int __cdecl rf_sound_sample_release_reference(int a1)
{
  int result; // eax

  if ( a1 >= 0 )
  {
    --unk_1951A54[148 * a1];
    result = 592 * a1;
    if ( !unk_1951A54[148 * a1] )
    {
      rf_sound_sample_release_formats_file_buffers(a1);
      --unk_1BA1818;
    }
  }
  return result;
}

