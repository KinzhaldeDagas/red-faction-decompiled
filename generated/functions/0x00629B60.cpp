// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00629B60 rf_body_state_names_initialize
// UNREALRED VERIFIED [death-selector-decode]: Constructs RF's 23 canonical body-state names.
int rf_body_state_names_initialize()
{
  rf_string_construct_from_cstr(&unk_683490, "stand");
  rf_string_construct_from_cstr(dword_683498, "attack_stand");
  rf_string_construct_from_cstr(dword_6834A0, "walk");
  rf_string_construct_from_cstr(dword_6834A8, "attack_walk");
  rf_string_construct_from_cstr(dword_6834B0, (char *)off_631C0C);
  rf_string_construct_from_cstr(dword_6834B8, "attack_run");
  rf_string_construct_from_cstr(dword_6834C0, "flee_run");
  rf_string_construct_from_cstr(dword_6834C8, "flail_run");
  rf_string_construct_from_cstr(dword_6834D0, "crouch");
  rf_string_construct_from_cstr(dword_6834D8, "attack_crouch");
  rf_string_construct_from_cstr(dword_6834E0, "attack_crouch_walk");
  rf_string_construct_from_cstr(dword_6834E8, "attack_lean_left");
  rf_string_construct_from_cstr(dword_6834F0, "attack_lean_right");
  rf_string_construct_from_cstr(dword_6834F8, "cower");
  rf_string_construct_from_cstr(dword_683500, "freefall");
  rf_string_construct_from_cstr(dword_683508, "on_turret");
  rf_string_construct_from_cstr(dword_683510, "corpse_carry_stand");
  rf_string_construct_from_cstr(dword_683518, "corpse_carry_walk");
  rf_string_construct_from_cstr(dword_683520, "swim_stand");
  rf_string_construct_from_cstr(dword_683528, "swim_walk");
  rf_string_construct_from_cstr(dword_683530, "jeep_drive");
  rf_string_construct_from_cstr(dword_683538, "jeep_gun");
  rf_string_construct_from_cstr(dword_683540, "custom");
  return atexit(rf_static_destroy_array_00683490);
}

