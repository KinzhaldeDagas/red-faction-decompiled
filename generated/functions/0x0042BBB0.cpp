// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0042BBB0 rf_entity_update_speech_body_actions
// UNREALRED VERIFIED [entity-speech-lifecycle-20261027] Speech body-action scheduler uses owner+0x1400 != -1 as admission, not a live playback query. Subtract frame_delta_seconds from +0x1408; if negative, clamp to 0 and return. Require both animation indices +0xCE4/+0xCF4 != -1 and elapsed +0x140C. For finite values, with durations D41/D42 from 0x564FE0: choose body action 41 if D41 < remaining; otherwise choose 42 only if remaining > 0.75*D42. Request chosen action at speed 1 with flags (0,1), arm +0x140C for trunc(chosen_duration*1000) milliseconds, and copy nonnegative action record at owner+0xA54+16*action to +0x1404. Countdown expiry does not stop or clear the voice; audio and body-action deadlines are separate.
// UNREALRED VERIFIED [combat-entity-speech-20261111]: Per-entity speech actions: retained voicehandle!=-1 admits; storefloat remaining-frameDelta FIRST; negative clamps0 and returns. Require both action slots41/42 !=-1 and elapsed140C, query duration41 THEN42. Finite choose41 iff D41<remaining; else42 iff remaining>double(D42)*0.75. Request action(mix1,flag0,Foley1), ignore request return, arm trunc(chosen float duration*1000), then re-read selected canonical slot A54+16*index and copy nonnegative animation handle to1404. This is not a new active-record serial. Do not clear unrelated body actions or suppress authored action Foley.
void __cdecl rf_entity_update_speech_body_actions(int a1)
{
  int v1; // [esp+Ch] [ebp-10h]
  float v2; // [esp+10h] [ebp-Ch]
  float v3; // [esp+14h] [ebp-8h]
  float v4; // [esp+18h] [ebp-4h]

  if ( *(_DWORD *)(a1 + 5120) != -1 )
  {
    *(float *)(a1 + 5128) = *(float *)(a1 + 5128) - rf_frame_delta_seconds;
    if ( *(float *)(a1 + 5128) < 0.0 )
    {
      *(float *)(a1 + 5128) = 0.0;
      return;
    }
    if ( *(_DWORD *)(a1 + 3300) != -1 && *(_DWORD *)(a1 + 3316) != -1 && rf_replicator_has_elapsed((int *)(a1 + 5132)) )
    {
      v3 = rf_model_animation_duration_seconds((unsigned int *)*(_DWORD *)(a1 + 128), *(_DWORD *)(a1 + 3300));
      v2 = rf_model_animation_duration_seconds((unsigned int *)*(_DWORD *)(a1 + 128), *(_DWORD *)(a1 + 3316));
      if ( v3 >= (double)*(float *)(a1 + 5128) )
      {
        if ( *(float *)(a1 + 5128) <= v2 * 0.75 )
          return;
        v1 = 42;
        v4 = v2;
        rf_entity_request_body_action(a1, 0x2Au, 1.0, 0, 1);
      }
      else
      {
        v1 = 41;
        v4 = v3;
        rf_entity_request_body_action(a1, 0x29u, 1.0, 0, 1);
      }
      rf_replicator_arm_milliseconds((int *)(a1 + 5132), (int)(v4 * 1000.0));
      if ( *(int *)(a1 + 16 * v1 + 2644) >= 0 )
        *(_DWORD *)(a1 + 5124) = *(_DWORD *)(a1 + 16 * v1 + 2644);
    }
  }
}

