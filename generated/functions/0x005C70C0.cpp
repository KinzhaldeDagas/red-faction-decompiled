// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C70C0 rf_positional_sound_update_segment
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): Requires initialized and signed index in [0,127]. Optionally copies non-NULL segment start/end to +84/+96. Calls update_point(index,storedStart,velocity,gainScale), so stored start also becomes current position when the deadline permits. Does not set the segment flag or test allocation; caller must have created a segment instance. Endpoint updates occur before the shared deadline gate.
void __cdecl rf_positional_sound_update_segment(
        int instance_index,
        const float *segment_start,
        const float *segment_end,
        const float *velocity,
        float gain_scale)
{
  float v5[3]; // [esp+4h] [ebp-1Ch] BYREF
  float copy_result[3]; // [esp+10h] [ebp-10h] BYREF
  int *v7; // [esp+1Ch] [ebp-4h]

  if ( byte_1DAEE54 && (unsigned int)instance_index < 0x80 )
  {
    v7 = &unk_1DAEE58[27 * instance_index];
    if ( segment_start )
      rf_vector_copy((float *)v7 + 21, copy_result, segment_start);
    if ( segment_end )
      rf_vector_copy((float *)v7 + 24, v5, segment_end);
    rf_positional_sound_update_point(instance_index, (float *)v7 + 21, (float *)velocity, gain_scale);
  }
}

