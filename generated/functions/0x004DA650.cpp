// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DA650 rf_developer_toggle_first_person_freelook
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): Execute nonzero reads local player camera196 state at camera+8: state2 calls4120D0, state0 calls411FA0, all other states unchanged. No own player/camera NULL checks. Independent help prints toggle description. No incoming references in current database; preserves existing callback name.
void rf_developer_toggle_first_person_freelook()
{
  int dword8; // [esp+0h] [ebp-4h]

  if ( dword_1809818 )
  {
    dword8 = rf_view_wrapper_get_dword8(*(_DWORD *)(rf_local_fpgun_player + 196));
    if ( dword8 == 2 )
    {
      rf_camera_slot_enter_first_person(*(float ***)(rf_local_fpgun_player + 196));
    }
    else if ( !dword8 )
    {
      rf_camera_slot_enter_state2_and_detach_nonnegative_handle(*(int **)(rf_local_fpgun_player + 196));
    }
  }
  if ( dword_1809814 )
    rf_console_output_append_text_lines("Toggle between freelook and first person\n", nullptr);
}

