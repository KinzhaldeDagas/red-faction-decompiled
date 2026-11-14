// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046CF10 rf_audio_messages_gain_from_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Cdecl(x,y). Update/read slider6F8588;x87 value rounded toFLOAT on stack;call rf_sound_channel_group_set_gain(2,gain) with TWO32-bit stack
// words,total8 caller cleanup. No own range/finite/input admission,player/config write,save or sound;slider/setter own policy and live propagation. Return setterEAX residue,not
// slider value.
unsigned int __cdecl rf_audio_messages_gain_from_pointer(int a1, int a2)
{
  float v3; // [esp+0h] [ebp-4h]

  rf_ui_slider_update_value_from_pointer((int)unk_6F8588, a1, a2);
  v3 = rf_ui_slider_value_get(unk_6F8588);
  return rf_sound_channel_group_set_gain(2u, v3);
}

