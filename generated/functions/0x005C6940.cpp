// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C6940 rf_positional_sound_find_quietest_voice
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): Walks live-instance list and chooses a slot whose voice handle +12>=0 and cached gain +16 is strictly below the current minimum, initialized to 1000. Returns its index or -1 if no candidate. Ties retain the first candidate. Does not query whether the backend voice is still playing.
int rf_positional_sound_find_quietest_voice()
{
  float v1; // [esp+0h] [ebp-Ch]
  int v2; // [esp+4h] [ebp-8h]
  float *i; // [esp+8h] [ebp-4h]

  v1 = 1000.0;
  v2 = -1;
  for ( i = (float *)dword_1DB2458; i != (float *)&dword_1DB2458; i = *(float **)i )
  {
    if ( *((int *)i + 3) >= 0 && v1 > (double)i[4] )
    {
      v1 = i[4];
      v2 = ((char *)i - (char *)unk_1DAEE58) / 108;
    }
  }
  return v2;
}

