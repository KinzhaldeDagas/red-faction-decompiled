// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00490460 rf_multiplayer_settings_destroy_string_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Thiscall aggregate destructor; static exit wrapper62F0C0 passes global704EC0. Destroys RFString-array backing atreceiver64 (global rotation vector704F00),then RFString8,then
// RFString0. Unwind destroys remaining strings. No receiver free,level rotation selection,live player teardown or scalar clearing. Array delegate destroys all allocated RFString
// elements via allocation cookie,not only logical count.
void __thiscall rf_multiplayer_settings_destroy_string_members(_DWORD *this)
{
  rf_string_array8_destroy_storage(this + 16);
  rf_string_destroy_buffer(this + 2);
  rf_string_destroy_buffer(this);
}

