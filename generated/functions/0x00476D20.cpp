// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00476D20 rf_cutscene_copy_active_position
// UNREALRED VERIFIED [cutscene-playback-20261028]: Copies vec3 at active record0x6FB24C+2084 to caller destination through rf_vector_copy. No null-active or destination guard. Does not resolve camera registry or evaluate curve.
float *__cdecl rf_cutscene_copy_active_position(float *destination)
{
  float copy_result[3]; // [esp+0h] [ebp-Ch] BYREF

  return rf_vector_copy(destination, copy_result, (const float *)(dword_6FB24C + 2084));
}

