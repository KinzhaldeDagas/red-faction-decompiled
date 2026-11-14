// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F0B90 rf_sound_settings_apply_registry_overrides
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): Constructs RFString, reads root Soundcard registry string, compares whole value case-insensitively with no sound. Match calls sound-frontend shutdown and sets disable BYTE88E444=1. Otherwise reads root DWORD key at63D5BC,default0; nonzero sets BYTE88E3F1=1, zero leaves prior byte unchanged. Does not clear sound-disable byte on nonmatching card or initialize sound itself. Destroys temporary RFString on both normal paths and SEH unwind.
void rf_sound_settings_apply_registry_overrides()
{
  const char *v0; // eax
  int v1[2]; // [esp+4h] [ebp-18h] BYREF
  BYTE Data[4]; // [esp+Ch] [ebp-10h] BYREF
  int v3; // [esp+18h] [ebp-4h]

  rf_string_construct_empty(v1);
  v3 = 0;
  rf_registry_read_string_object(nullptr, "Soundcard", v1);
  v0 = rf_string_object_c_str_or_empty(v1);
  if ( !_stricmp(v0, "no sound") )
  {
    rf_sound_frontend_shutdown();
    unk_88E444 = 1;
    v3 = -1;
    rf_string_destroy_buffer(v1);
  }
  else
  {
    rf_registry_read_dword_or_default(nullptr, off_63D5BC, Data, 0);
    if ( *(_DWORD *)Data )
      unk_88E3F1 = 1;
    v3 = -1;
    rf_string_destroy_buffer(v1);
  }
}

