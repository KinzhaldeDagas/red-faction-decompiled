// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00569100 rf_ambient_voice_slot_reset
// UNREALRED VERIFIED [ambient-audio]: Resets one 24-byte frontend ambient slot: sound handle -1, backend voice -1, zero position, and zero source gain.
float *__cdecl rf_ambient_voice_slot_reset(int a1)
{
  float *result; // eax

  *(_DWORD *)a1 = -1;
  *(_DWORD *)(a1 + 4) = -1;
  result = rf_vector3_set_components_thiscall((float *)(a1 + 8), 0.0, 0.0, 0.0);
  *(float *)(a1 + 20) = 0.0;
  return result;
}

