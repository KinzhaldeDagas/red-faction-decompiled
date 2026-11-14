// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046CE80 rf_audio_music_gain_from_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Cdecl(x,y). Update/read slider6F8540;x87 value rounded toFLOAT on stack;call rf_sound_channel_group_set_gain(1,gain) with TWO32-bit stack
// words,total8 caller cleanup. No own range/finite/input admission,player/config write,save or sound;slider/setter own policy and live propagation. Return setterEAX residue,not
// slider value.
unsigned int __cdecl rf_audio_music_gain_from_pointer(int a1, int a2)
{
  float v3; // [esp+0h] [ebp-4h]

  rf_ui_slider_update_value_from_pointer((int)unk_6F8540, a1, a2);
  v3 = rf_ui_slider_value_get(unk_6F8540);
  return rf_sound_channel_group_set_gain(1u, v3);
}

