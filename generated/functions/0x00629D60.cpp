// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00629D60 rf_body_action_names_initialize
// VERIFIED: Constructs the 45-entry authored animation-descriptor table at 0x683328 with 8-byte string objects. Entries 28 and 29 are exactly 'idle_to_ready' and 'ready_to_idle'.
// UNREALRED VERIFIED [body-action-decode]: Constructs RF's 45 canonical body-action names as contiguous eight-byte RF string objects.
int rf_body_action_names_initialize()
{
  rf_string_construct_from_cstr(&rf_body_action_names, "corpse_drop");
  rf_string_construct_from_cstr(dword_683330, "corpse_carry");
  rf_string_construct_from_cstr(dword_683338, "fire_stand");
  rf_string_construct_from_cstr(dword_683340, "alt_fire_stand");
  rf_string_construct_from_cstr(dword_683348, "fire_crouch");
  rf_string_construct_from_cstr(dword_683350, "death_generic");
  rf_string_construct_from_cstr(dword_683358, "death_blast_forward");
  rf_string_construct_from_cstr(dword_683360, "death_blast_backward");
  rf_string_construct_from_cstr(dword_683368, "death_head_forward");
  rf_string_construct_from_cstr(dword_683370, "death_head_backward");
  rf_string_construct_from_cstr(dword_683378, "death_head_neutral");
  rf_string_construct_from_cstr(dword_683380, "death_chest_forward");
  rf_string_construct_from_cstr(dword_683388, "death_chest_backward");
  rf_string_construct_from_cstr(dword_683390, "death_chest_neutral");
  rf_string_construct_from_cstr(dword_683398, "death_leg_left");
  rf_string_construct_from_cstr(dword_6833A0, "death_leg_right");
  rf_string_construct_from_cstr(dword_6833A8, "death_crouch");
  rf_string_construct_from_cstr(dword_6833B0, "sidestep_left");
  rf_string_construct_from_cstr(dword_6833B8, "sidestep_right");
  rf_string_construct_from_cstr(dword_6833C0, "roll_left");
  rf_string_construct_from_cstr(dword_6833C8, "roll_right");
  rf_string_construct_from_cstr(dword_6833D0, "land");
  rf_string_construct_from_cstr(dword_6833D8, "flinch_stand");
  rf_string_construct_from_cstr(dword_6833E0, "flinch_attack_stand");
  rf_string_construct_from_cstr(dword_6833E8, "flinch_chest");
  rf_string_construct_from_cstr(dword_6833F0, "flinch_back");
  rf_string_construct_from_cstr(dword_6833F8, "flinch_leg_left");
  rf_string_construct_from_cstr(dword_683400, "flinch_leg_right");
  rf_string_construct_from_cstr(dword_683408, "idle_to_ready");
  rf_string_construct_from_cstr(dword_683410, "ready_to_idle");
  rf_string_construct_from_cstr(dword_683418, "idle_1");
  rf_string_construct_from_cstr(dword_683420, "idle_2");
  rf_string_construct_from_cstr(dword_683428, "idle_3");
  rf_string_construct_from_cstr(dword_683430, "idle_4");
  rf_string_construct_from_cstr(dword_683438, "rock_drop");
  rf_string_construct_from_cstr(dword_683440, "rock_pickup");
  rf_string_construct_from_cstr(dword_683448, "death_still_1");
  rf_string_construct_from_cstr(dword_683450, "death_still_2");
  rf_string_construct_from_cstr(dword_683458, "death_still_3");
  rf_string_construct_from_cstr(dword_683460, "reload");
  rf_string_construct_from_cstr(dword_683468, "unholster");
  rf_string_construct_from_cstr(dword_683470, "speak");
  rf_string_construct_from_cstr(dword_683478, "speak_short");
  rf_string_construct_from_cstr(dword_683480, "heal_light_1");
  rf_string_construct_from_cstr(dword_683488, "hit_alarm");
  return atexit(rf_static_destroy_array_00683328);
}

