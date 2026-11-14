// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EFBF0 rf_localization_initialize_language_and_load
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, thermal renderer x87 branches, native stack aliases, localization pool writes and skin-profile selection): Cdecl language integer. Clears exactly1000 DWORD pointers at88D438, stores language88E3DC; language1 setsDWORD88E3E0=1, language2 sets88E3E4=1. Does NOT clear the other language flag or either flag for language0/other values. Calls strings-table loader, forwarding incidental EAX. Does not reset shared cursor663044 (PE initializer87FC98), fallback table/count88C498/88E3D8 or loaded byte88E3E8.
void **__cdecl rf_localization_initialize_language_and_load(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 1000; ++i )
    unk_88D438[i] = 0;
  unk_88E3DC = a1;
  if ( a1 == 1 )
  {
    unk_88E3E0 = 1;
  }
  else if ( unk_88E3DC == 2 )
  {
    unk_88E3E4 = 1;
  }
  return rf_localization_load_strings_table();
}

