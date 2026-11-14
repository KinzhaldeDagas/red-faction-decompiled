// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B0E70 rf_multiplayer_initialize_team_names_and_colors
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Noarg. Set team0 name literal Red Team and RGBA(255,0,0,255); set team1 literal Blue Team but RGBA(0,255,0,255), i.e. GREEN bytes despite Blue name.
// Exact caller pushes and verified color constructor prove component order; do not silently correct blue. Names/colors use checked setters then register4B0ED0 at exit, return CRT
// registration result. No localization, gameplay-team redistribution, old-resource release or duplicate-registration gate.
int rf_multiplayer_initialize_team_names_and_colors()
{
  rf_multiplayer_set_team_name(0, "Red Team");
  rf_multiplayer_set_team_rgb_opaque(0, 255, 0, 0);
  rf_multiplayer_set_team_name(1u, "Blue Team");
  rf_multiplayer_set_team_rgb_opaque(1u, 0, 255, 0);
  return atexit(rf_multiplayer_atexit_clear_team_names);
}

