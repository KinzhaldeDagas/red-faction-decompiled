// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E49A0 rf_vehicle_cockpit_initialize_camera_sound_and_cleanup
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): Construct temporary RFString Camera Change, resolve Foley row by case-insensitive exact name446EE0, destroy temporary normally/SEH, get variant0 via446F60, store event index87C6B0 (including -1). Register existing fighter-chaingun model release callback with atexit and return registration result EAX. No cockpit bitmap loads, node-cache reset, camera-mode reset or sound-result validation in this function.
int __cdecl rf_vehicle_cockpit_initialize_camera_sound_and_cleanup()
{
  char *v0; // eax
  std::exception *v2; // [esp+4h] [ebp-24h]
  _DWORD v3[3]; // [esp+Ch] [ebp-1Ch] BYREF
  int name; // [esp+18h] [ebp-10h]
  int v5; // [esp+24h] [ebp-4h]

  v3[2] = 0;
  v2 = (std::exception *)rf_string_construct_from_cstr(v3, "Camera Change");
  v5 = 0;
  v0 = (char *)rf_string_object_c_str_or_empty(v2);
  name = rf_foley_definition_find_name(v0);
  v5 = -1;
  rf_string_destroy_buffer(v3);
  unk_87C6B0 = rf_foley_get_sound_by_index(name, 0);
  return atexit(rf_fighter_chaingun_model_release);
}

