// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00476D50 rf_cutscene_copy_active_orientation
// UNREALRED VERIFIED [cutscene-ui-20261028]: Passes matrix at active record0x6FB24C+2096 to shared rf_matrix3_copy with destination loaded from first stack argument into ECX. No null-active check. Native cdecl takes one float* destination stack parameter; restored the saved one-parameter type from original instructions and callers (2026-11-12).
int __cdecl rf_cutscene_copy_active_orientation(float *destination)
{
  return rf_matrix3_copy(destination, (const float *)(dword_6FB24C + 2096));
}

