// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EEFF0 rf_player_initialize_undercover_profile_strings
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model cache fallback, material replacement, leg animation transitions and native caller ABI): Assigns existing RFStrings:87FC28=scientist_gun;87FC34/3C/54=scientisthand1.tga;87FC44/64=ultorgun1st_01A.tga;87FC4C/6C/74=ultorgun1st_01.tga;87FC5C/7C=scientisthand2.tga. Sets87FC30=10; resolves entity classes miner1->87FC14,parker_suit->87FC10,parker_sci->87FC04;87FC18=-1; disarms timestamp87FC20. Registers4EF100 with atexit and returns registration EAX. Does not change undercover-active byte87FC01 or load models/textures here.
// UNREALRED VERIFIED [combat-native-pickup-runtime-20261111]: Actual4F1440 startup call4F18DC writes alarmvoice87FC18=-1 and Reset87FC20=-1 before normal level initialization. Static62D050 separately constructs timer invalid. Thus initial session values are known-1, not guessed BSS0. Subsequent4EF150 level reset does not alter either field. Profile class/string initialization is separate.
int rf_player_initialize_undercover_profile_strings()
{
  rf_string_assign_from_cstr(unk_87FC28, "scientist_gun");
  unk_87FC30 = 10;
  rf_string_assign_from_cstr(dword_87FC34, "scientisthand1.tga");
  rf_string_assign_from_cstr(dword_87FC44, "ultorgun1st_01A.tga");
  rf_string_assign_from_cstr(dword_87FC4C, "ultorgun1st_01.tga");
  rf_string_assign_from_cstr(dword_87FC5C, "scientisthand2.tga");
  rf_string_assign_from_cstr(dword_87FC3C, "scientisthand1.tga");
  rf_string_assign_from_cstr(dword_87FC54, "scientisthand1.tga");
  rf_string_assign_from_cstr(dword_87FC64, "ultorgun1st_01A.tga");
  rf_string_assign_from_cstr(dword_87FC6C, "ultorgun1st_01.tga");
  rf_string_assign_from_cstr(dword_87FC74, "ultorgun1st_01.tga");
  rf_string_assign_from_cstr(dword_87FC7C, "scientisthand2.tga");
  unk_87FC14 = sub_431680("miner1");
  unk_87FC10 = sub_431680("parker_suit");
  unk_87FC04 = sub_431680("parker_sci");
  unk_87FC18 = -1;
  rf_replicator_reset(unk_87FC20);
  return atexit(rf_undercover_clear_profile_strings_at_exit);
}

