// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A4110 rf_model_set_special_lod_light_mode
// UNREALRED VERIFIED [character-pipeline-20261029]: Argument BYTE,stores directly to global0x1C99894 and returns it. Does not boolean-normalize,rebuild lights or draw. Nonzero bypasses distance-based LOD selection and selects alternate first-light direction/scaling in0x5A1070.
char __cdecl rf_model_set_special_lod_light_mode(char a1)
{
  unk_1C99894 = a1;
  return a1;
}

