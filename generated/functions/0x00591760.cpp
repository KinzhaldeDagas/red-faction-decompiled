// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00591760 rf_audio_set_environment_if_property_extension_enabled
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tokenizer ownership/quote rules, native hook contracts, observer registration, startup signaling and thread-exit/calling-convention paths): Cdecl mutable preset-name cstring. Reads raw property-extension mode byte5915C0; zero returns EAX0 without preset operation, nonzero delegates rf_audio_environment_set_preset_by_mutable_name and returns helper result. Does not enable extension, copy/validate name or inspect independent3D-mode byte; name mutability and case handling belong to existing environment helper.
int __cdecl rf_audio_set_environment_if_property_extension_enabled(char *String1)
{
  int result; // eax

  result = (unsigned __int8)rf_audio_get_property_extension_mode_byte();
  if ( (_BYTE)result )
    return rf_audio_environment_set_preset_by_mutable_name(String1);
  return result;
}

