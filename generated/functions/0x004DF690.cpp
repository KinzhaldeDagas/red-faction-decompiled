// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DF690 rf_player_set_clamped_option_float_3928
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player lifecycle, weapon-class selection, team-skin material/profile loops, native string-buffer aliases and caller ABI): Cdecl player,float value. Calls float clamp on stack-local value with lower0,upper1; native helper clamps ordered values below0/above1, leaves NaN unchanged (no forced endpoint or finite normalization). Stores resulting float to player+3928 (options3700 at player+228). No own player NULL check, downstream application/recompute or return status. Getter returns same field via x87 ST0.
void __cdecl rf_player_set_clamped_option_float_3928(int a1, float a2)
{
  rf_float_clamp_in_place(&a2, 0.0, 1.0);
  *(float *)(a1 + 3928) = a2;
}

