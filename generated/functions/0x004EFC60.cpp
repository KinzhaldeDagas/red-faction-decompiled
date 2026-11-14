// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EFC60 rf_localization_get_language
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, thermal renderer x87 branches, native stack aliases, localization pool writes and skin-profile selection): No arguments. Returns language DWORD88E3DC unchanged; no validation or side effects.
int rf_localization_get_language()
{
  return unk_88E3DC;
}

