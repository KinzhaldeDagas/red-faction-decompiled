// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005884E0 rf_animation_registry_load
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Resolves clip byname via5BA370, fatal if absent. Searches character handle list/count+3928 for identical clip pointer AND byte classification at+4620+i. Existing pair returns index. Otherwise appends pointer/classification, increments count BEFORE calling rf_rfa_load_raw_file(name,0), ignores raw-load result and returns new index. Fourth stack argument is unused. No handle-array capacity or class-byte validation; same clip pointer with different class bytes can be appended twice.
int __thiscall rf_animation_registry_load(_DWORD *this, char *a2, unsigned __int8 a3, int a4)
{
  char *v6; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  v6 = rf_animation_clip_acquire_registry_entry(a2);
  if ( !v6 )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\vsdk\\ca\\character.cpp",
      720,
      "Couldn't load skeleton!\n");
  for ( i = 0; i < *(this + 982); ++i )
  {
    if ( (char *)*(this + i + 983) == v6 && *((unsigned __int8 *)this + i + 4620) == a3 )
      return i;
  }
  *(this + *(this + 982) + 983) = v6;
  *((_BYTE *)this + (*(this + 982))++ + 4620) = a3;
  rf_rfa_load_raw_file(a2, nullptr);
  return *(this + 982) - 1;
}

