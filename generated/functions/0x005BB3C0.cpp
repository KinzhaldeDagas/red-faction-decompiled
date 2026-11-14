// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BB3C0 rf_rfa_compute_average_translation_rate
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): Lazily gets raw header; computes float reciprocal of ((end-start)/160/30), multiplies header TotalTranslation float3 at+60 into output and returns output. Equivalent intended scale4800/durationTicks but sequential x87/float rounding preserved. No zero/negative-duration or failed-load guard. No image xrefs observed in this snapshot; absence of xrefs alone does not prove unreachable code.
float *__thiscall rf_rfa_compute_average_translation_rate(void *this, float *a2)
{
  float scalar; // [esp+4h] [ebp-1Ch]
  unsigned __int8 *raw_buffer; // [esp+10h] [ebp-10h]
  float scaled_result[3]; // [esp+14h] [ebp-Ch] BYREF

  raw_buffer = rf_rfa_get_or_load_raw_buffer(this);
  scalar = 1.0 / ((double)(*((_DWORD *)raw_buffer + 5) - *((_DWORD *)raw_buffer + 4)) / 160.0 / 30.0);
  rf_vector_multiply_scalar((const float *)raw_buffer + 15, scaled_result, scalar);
  rf_vector3_copy_return_destination(a2, scaled_result);
  return a2;
}

