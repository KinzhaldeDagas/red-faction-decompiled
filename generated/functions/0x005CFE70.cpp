// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CFE70 rf_audio_stream_bytes_played_since_write_cursor
// UNREALRED VERIFIED [audio-streaming-20261028]: Slot index selects28-byte record at0x1E012F0+28*index; DS buffer from44-byte backend record0x1BA1820+44*streamDWORD+4. Calls buffer vtable+16 GetCurrentPosition into play/write outputs but uses ONLY play cursor. Negative HRESULT returns0. Else computes unsigned wrapped distance from logical write cursor+12 to play cursor using ring bytes+8. No safety gap, cursor normalization, slot or pointer validation.
unsigned int __cdecl rf_audio_stream_bytes_played_since_write_cursor(int a1)
{
  unsigned int v2; // [esp+0h] [ebp-14h] BYREF
  int v3; // [esp+4h] [ebp-10h]
  int v4; // [esp+8h] [ebp-Ch]
  int *v5; // [esp+Ch] [ebp-8h]
  char v6[4]; // [esp+10h] [ebp-4h] BYREF

  v5 = &unk_1E012F0[7 * a1];
  v4 = 0;
  v3 = (*(int (__stdcall **)(int, unsigned int *, char *))(*(_DWORD *)unk_1BA1820[11 * v5[1]] + 16))(
         unk_1BA1820[11 * v5[1]],
         &v2,
         v6);
  if ( v3 < 0 )
    return 0;
  if ( v5[3] > v2 )
    return v2 + v5[2] - v5[3];
  else
    return v2 - v5[3];
}

