// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DF680 rf_player_get_option_float_3928
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player lifecycle, weapon-class selection, team-skin material/profile loops, native string-buffer aliases and caller ABI): Cdecl player pointer. FLD DWORD player+3928 directly and return through x87 ST0, declared double; no intermediate F32 spill, clamp, validation or side effects. This field is options member3700 at player+228; defaults initializer writes float0.5 and restore setter clamps ordered values to0..1. Stronger gameplay meaning not assigned.
double __cdecl rf_player_get_option_float_3928(int a1)
{
  return *(float *)(a1 + 3928);
}

