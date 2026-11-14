// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058FB30 rf_dsound_create_static_pcm_sample_buffer
// UNREALRED VERIFIED [dsound-creation-20261028]: Argument sample index. Builds36-byte DSBUFFERDESC with flags393456 if global0x193BBE0==1 else234,bytes=data chunk remaining+552,format=output WAVEFORMAT+536. Device0x1951804 CreateSoundBuffer+12 writes sample buffer+524. Negative result or null buffer-1. Fills through0x58FC70; failure marks return-1 but retains sample pointer. When global==1,queries3D interface0x58FD10 into+528,IGNORES query result. Returns0/-1 for creation/fill only. No index/format validation or cleanup on fill/query failure.
int __cdecl rf_dsound_create_static_pcm_sample_buffer(int a1)
{
  int v2; // [esp+4h] [ebp-30h] BYREF
  int v3; // [esp+8h] [ebp-2Ch]
  int v4; // [esp+Ch] [ebp-28h]
  int v5; // [esp+10h] [ebp-24h]
  int v6; // [esp+14h] [ebp-20h]
  int v7; // [esp+18h] [ebp-1Ch]
  int v8; // [esp+1Ch] [ebp-18h]
  int v9; // [esp+20h] [ebp-14h]
  int v10; // [esp+24h] [ebp-10h]
  char *v11; // [esp+2Ch] [ebp-8h]
  int v12; // [esp+30h] [ebp-4h]

  v12 = 0;
  v11 = (char *)&unk_1951808 + 592 * a1;
  v3 = 0;
  v4 = 0;
  v5 = 0;
  v6 = 0;
  v7 = 0;
  v8 = 0;
  v9 = 0;
  v10 = 0;
  v2 = 36;
  if ( unk_193BBE0 == 1 )
    v3 = 393456;
  else
    v3 = 234;
  v4 = *((_DWORD *)v11 + 138);
  v6 = *((_DWORD *)v11 + 134);
  if ( (*(int (__stdcall **)(int, int *, char *, _DWORD))(*(_DWORD *)dword_1951670[101] + 12))(
         dword_1951670[101],
         &v2,
         v11 + 524,
         0) < 0
    || !*((_DWORD *)v11 + 131) )
  {
    return -1;
  }
  if ( rf_dsound_fill_pcm_buffer_from_wave_chunk(
         *((HMMIO *)v11 + 136),
         (int)(v11 + 548),
         *((_DWORD *)v11 + 131),
         *((_DWORD *)v11 + 138)) )
  {
    v12 = -1;
  }
  if ( unk_193BBE0 == 1 )
    rf_dsound_query_buffer_3d_interface_if_capable(*((_DWORD *)v11 + 131), (_DWORD *)v11 + 132);
  return v12;
}

