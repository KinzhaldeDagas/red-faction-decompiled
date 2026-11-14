// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005068E0 rf_vclip_initialize_definition_and_runtime_state
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VClip initialization/preloads,byte occupancy and physical array sizes,trigger suppression/member cleanup and constructor ABI,original ECX/stack flow and PE bytes): Sets loaded definition count90B820=0. For EXACT64 definition records stride224 at90DC80, assigns empty RFStrings0/12/36 from original NUL literals63E50F/63E517/63E529, writes bitmap handle+20=-1 and Foley handle+44=-1. No blanket scalar/particle/default clearing or explicit release of previous bitmap/VFX handles. Self-links runtime sentinel next90B838/previous90B83C to90B838; then clears ONLY active BYTE+60 in EACH128 runtime records at90B880 stride72, leaving payload/links untouched. Loads table506A10, then performs fixed64-slot case-insensitive name lookups507610 in order:
// water_splash_small->90B830,water_splash_medium->90B824,water_splash_large->90B834,water_splash_huge->90B828,bullet_splash->90B82C, retaining-1 failures. Registers rf_vclip_effect_system_clear with atexit and returns registration result. No active VFX destruction before resetting sentinel/bytes; repeated initialization is not a teardown operation.
int rf_vclip_initialize_definition_and_runtime_state()
{
  int i; // [esp+0h] [ebp-8h]
  int j; // [esp+0h] [ebp-8h]
  _DWORD *v3; // [esp+4h] [ebp-4h]

  unk_90B820 = 0;
  for ( i = 0; i < 64; ++i )
  {
    v3 = (_DWORD *)((char *)&unk_90DC80 + 224 * i);
    rf_string_assign_from_cstr(v3, (char *)&byte_63E50F);
    rf_string_assign_from_cstr(v3 + 3, (char *)&byte_63E517);
    v3[5] = -1;
    rf_string_assign_from_cstr(v3 + 9, (char *)&byte_63E529);
    v3[11] = -1;
  }
  dword_90B838 = &dword_90B838;
  unk_90B83C = &dword_90B838;
  for ( j = 0; j < 128; ++j )
    unk_90B8BC[72 * j] = 0;
  rf_vclip_load_table_records();
  unk_90B830 = sub_507610("water_splash_small");
  unk_90B824 = sub_507610("water_splash_medium");
  unk_90B834 = sub_507610("water_splash_large");
  unk_90B828 = sub_507610("water_splash_huge");
  unk_90B82C = sub_507610("bullet_splash");
  return atexit(rf_vclip_effect_system_clear);
}

