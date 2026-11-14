// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C6A30 rf_positional_sound_start_voice_with_budget
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): Enforces a nominal 16-voice budget. When count>=16, finds quietest candidate; rejects the new voice only if its cached gain is lower, otherwise stops the candidate. Does NOT check candidate!=-1 before indexing/stopping. Retrieves resource record without checking return. Computes cachedGain/resourceBaseGain without a zero guard before the loop branch. Hardware-selection helper always returns 0 in this build: looping uses backend_loop_start(resource,ratio,0,0,0); nonlooping uses start_at_point(resource,position,0,0). Stores returned handle and increments active voice count only for a nonnegative handle.
void __cdecl rf_positional_sound_start_voice_with_budget(int a1)
{
  int quietest_voice; // [esp+10h] [ebp-14h]
  float v2; // [esp+14h] [ebp-10h]
  int *v3; // [esp+18h] [ebp-Ch]
  int v4; // [esp+1Ch] [ebp-8h] BYREF
  char v5; // [esp+23h] [ebp-1h]

  v3 = &unk_1DAEE58[27 * a1];
  if ( dword_1DAEE50 >= 16 )
  {
    quietest_voice = rf_positional_sound_find_quietest_voice();
    if ( *((float *)v3 + 4) < (double)*((float *)&unk_1DAEE68 + 27 * quietest_voice) )
      return;
    rf_positional_sound_stop_voice(quietest_voice, 0);
  }
  rf_sound_resource_get_record_out(v3[2], &v4);
  v5 = (v3[20] & 8) != 0;
  if ( rf_positional_sound_use_hardware_3d_disabled() == 1 )
  {
    v3[3] = rf_sound_voice_start_at_point(v3[2], (float *)v3 + 9, v5, 0.0);
  }
  else if ( v5 == 1 )
  {
    v2 = *((float *)v3 + 4) / *(float *)(v4 + 32);
    v3[3] = rf_sound_voice_start_looping(v3[2], v2, 0.0, 0.0, 0);
  }
  else
  {
    v3[3] = rf_sound_voice_start_at_point(v3[2], (float *)v3 + 9, 0, 0.0);
  }
  if ( v3[3] >= 0 )
    ++dword_1DAEE50;
}

