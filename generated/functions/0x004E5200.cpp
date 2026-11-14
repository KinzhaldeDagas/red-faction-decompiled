// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E5200 rf_player_runtime_state_restore
// VERIFIED: Loaded-options application reads float field +128 and passes it through rf_graphics_gamma_set, so the same retail clamp and LUT rebuild apply to persisted values.
// UNREALRED VERIFIED [ingame-hud-layers] Restores broad player state, including the five independent HUD visibility bytes from save-mask bits 0x40, 0x80, 0x100, 0x200, and 0x400.
int __cdecl rf_player_runtime_state_restore(int a1, int a2)
{
  int i; // [esp+4h] [ebp-4h]

  rf_sound_channel_group_set_gain(0, *(float *)(a2 + 32));
  rf_sound_channel_group_set_gain(1u, *(float *)(a2 + 36));
  rf_sound_channel_group_set_gain(2u, *(float *)(a2 + 40));
  rf_player_set_clamped_option_float_3928(a1, *(float *)(a2 + 124));
  rf_difficulty_set_valid_choice_copy_configured_and_load_ui(*(_DWORD *)(a2 + 44));
  dword_662E2C = *(_DWORD *)(a2 + 48);
  rf_graphics_gamma_set(*(float *)(a2 + 128));
  *(_DWORD *)(a1 + 3916) = *(_DWORD *)(a2 + 108);
  *(_DWORD *)(a1 + 3920) = *(_DWORD *)(a2 + 112);
  *(_DWORD *)(a1 + 3924) = *(_DWORD *)(a2 + 116);
  *(_BYTE *)(a1 + 3892) = (*(_DWORD *)(a2 + 120) & 1) != 0;
  *(_BYTE *)(a1 + 3894) = (*(_DWORD *)(a2 + 120) & 2) != 0;
  *(_BYTE *)(a1 + 3895) = (*(_DWORD *)(a2 + 120) & 4) != 0;
  *(_BYTE *)(a1 + 3896) = (*(_DWORD *)(a2 + 120) & 8) != 0;
  *(_BYTE *)(a1 + 3897) = (*(_DWORD *)(a2 + 120) & 0x10) != 0;
  *(_BYTE *)(a1 + 3898) = (*(_DWORD *)(a2 + 120) & 0x20) != 0;
  *(_BYTE *)(a1 + 3899) = (*(_DWORD *)(a2 + 120) & 0x40) != 0;
  *(_BYTE *)(a1 + 3900) = (*(_DWORD *)(a2 + 120) & 0x80) != 0;
  *(_BYTE *)(a1 + 3901) = (*(_DWORD *)(a2 + 120) & 0x100) != 0;
  *(_BYTE *)(a1 + 3902) = (*(_DWORD *)(a2 + 120) & 0x200) != 0;
  *(_BYTE *)(a1 + 3903) = (*(_DWORD *)(a2 + 120) & 0x400) != 0;
  *(_BYTE *)(a1 + 3893) = (*(_DWORD *)(a2 + 120) & 0x800) != 0;
  *(_BYTE *)(a1 + 3904) = (*(_DWORD *)(a2 + 120) & 0x1000) != 0;
  *(_BYTE *)(a1 + 3905) = (*(_DWORD *)(a2 + 120) & 0x2000) != 0;
  *(_BYTE *)(a1 + 3906) = (*(_DWORD *)(a2 + 120) & 0x8000) != 0;
  *(_BYTE *)(a1 + 3907) = (*(_DWORD *)(a2 + 120) & 0x10000) != 0;
  *(_BYTE *)(a1 + 3908) = (*(_DWORD *)(a2 + 120) & 0x20000) != 0;
  *(_BYTE *)(a1 + 3909) = (*(_DWORD *)(a2 + 120) & 0x40000) != 0;
  *(_BYTE *)(a1 + 3910) = (*(_DWORD *)(a2 + 120) & 0x80000) != 0;
  *(_BYTE *)(a1 + 3911) = (*(_DWORD *)(a2 + 120) & 0x100000) != 0;
  *(_BYTE *)(a1 + 3912) = (*(_DWORD *)(a2 + 120) & 0x200000) != 0;
  rf_string_assign_from_cstr((_DWORD *)(a1 + 8), (char *)(a2 + 52));
  *(_DWORD *)(a1 + 3932) = *(_DWORD *)(a2 + 100);
  for ( i = 0; i < 32; ++i )
    *(_DWORD *)(a1 + 4 * i + 4436) = *(__int16 *)(a2 + 2 * i + 200);
  return rf_player_embedded_options_unpack_792(a1 + 228, a2 + 264);
}

