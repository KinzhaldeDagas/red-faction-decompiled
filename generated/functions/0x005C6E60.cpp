// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C6E60 rf_positional_sound_create_segment
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): Five cdecl arguments: resource index, segment start/end vectors, update interval, loop byte. Creates an ordinary instance; on -1 returns -1. Otherwise copies endpoints to +84/+96, sets segment flag 4 and returns the instance index. Endpoint pointers are mandatory; no playback starts here. Function definition recovered from original instructions.
int __cdecl rf_positional_sound_create_segment(
        int resource_index,
        const float *segment_start,
        const float *segment_end,
        int update_interval,
        unsigned __int8 looping)
{
  float v6[3]; // [esp+0h] [ebp-20h] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-14h] BYREF
  int point; // [esp+18h] [ebp-8h]
  int *v9; // [esp+1Ch] [ebp-4h]

  point = rf_positional_sound_create_point(resource_index, update_interval, looping);
  if ( point == -1 )
    return -1;
  v9 = &unk_1DAEE58[27 * point];
  rf_vector_copy((float *)v9 + 21, copy_result, segment_start);
  rf_vector_copy((float *)v9 + 24, v6, segment_end);
  v9[20] |= 4u;
  return point;
}

