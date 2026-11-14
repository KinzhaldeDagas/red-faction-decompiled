// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F0B00 rf_video_settings_read_registry_defaults
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): Sets screen selector88E44C=1. Reads root registry DWORDs in order: Resolution Bit Depth->88E424 default16; Resolution Width->88E40C default640; Resolution Height->88E418 default480; Resolution Backbuffer Format->663054 default-1; Selected Video Card->88E458 default0. Returns last registry helper EAX. No own bounds/format/card validation, renderer allocation or use of earlier helper return codes.
int rf_video_settings_read_registry_defaults()
{
  unk_88E44C = 1;
  rf_registry_read_dword_or_default(nullptr, "Resolution Bit Depth", MEMORY[0x88E424], 16);
  rf_registry_read_dword_or_default(nullptr, "Resolution Width", byte_88E40C, 640);
  rf_registry_read_dword_or_default(nullptr, "Resolution Height", byte_88E418, 480);
  rf_registry_read_dword_or_default(nullptr, "Resolution Backbuffer Format", &dword_663054, -1);
  return rf_registry_read_dword_or_default(nullptr, "Selected Video Card", byte_88E458, 0);
}

