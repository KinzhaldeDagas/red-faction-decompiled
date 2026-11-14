// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C68B0 rf_positional_sound_instance_reset
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): For a 108-byte slot, clears flags +80, sets resource index +8 and voice handle +12 to -1, and zeros velocity +60 and position +36. Leaves links, cached gains/pan/frequencies, interval/deadline and segment endpoints untouched. No index bounds check. Return EAX is the last vector destination, not a status.
float *__cdecl rf_positional_sound_instance_reset(int a1)
{
  int *v2; // [esp+0h] [ebp-4h]

  v2 = &unk_1DAEE58[27 * a1];
  v2[20] = 0;
  v2[2] = -1;
  v2[3] = -1;
  rf_vector3_zero_return_destination((float *)v2 + 15);
  return rf_vector3_zero_return_destination((float *)v2 + 9);
}

