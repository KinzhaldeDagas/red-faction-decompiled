// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C69C0 rf_positional_sound_stop_voice
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): If slot voice handle +12>=0, fade<=0 calls backend_voice_stop; positive fade calls music_backend_fade. Immediately sets handle=-1 and decrements global active voice count even when fading is asynchronous or the lower backend is unavailable. Does not unlink/reset the instance. No bounds check; EAX incidental.
int *__cdecl rf_positional_sound_stop_voice(int a1, int a2)
{
  int *result; // eax
  int *v3; // [esp+0h] [ebp-4h]

  result = &unk_1DAEE58[27 * a1];
  v3 = result;
  if ( result[3] >= 0 )
  {
    if ( a2 <= 0 )
      result = rf_sound_backend_voice_stop(result[3]);
    else
      result = rf_music_backend_fade(result[3], a2);
    v3[3] = -1;
    --unk_1DAEE50;
  }
  return result;
}

