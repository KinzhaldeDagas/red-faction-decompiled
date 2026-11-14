// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E4C70 rf_player_runtime_state_snapshot
// VERIFIED: Runtime-options export stores the current global gamma as float field +128 in the options record.
// UNREALRED VERIFIED [ingame-hud-layers] Snapshots broad player state; HUD master, weapon status, player status, persona-message, and reticle bytes +0xF3B..+0xF3F map independently to save-mask bits 0x40..0x400.
int __cdecl rf_player_runtime_state_snapshot(int a1, int a2)
{
  char v3; // [esp+7h] [ebp-21h]
  _BYTE *v4; // [esp+Ch] [ebp-1Ch]
  const char *v5; // [esp+10h] [ebp-18h]
  char v6; // [esp+17h] [ebp-11h]
  _BYTE *v7; // [esp+1Ch] [ebp-Ch]
  const char *v8; // [esp+20h] [ebp-8h]
  int i; // [esp+24h] [ebp-4h]

  v8 = rf_string_object_c_str_or_empty((const void *)(a1 + 8));
  v7 = (_BYTE *)a2;
  do
  {
    v6 = *v8;
    *v7++ = *v8++;
  }
  while ( v6 );
  *(float *)(a2 + 32) = rf_sound_channel_group_gain_get_unchecked(0);
  *(float *)(a2 + 36) = rf_sound_channel_group_gain_get_unchecked(1);
  *(float *)(a2 + 40) = rf_sound_channel_group_gain_get_unchecked(2);
  *(float *)(a2 + 124) = rf_player_get_option_float_3928(a1);
  *(_DWORD *)(a2 + 44) = dword_6612A4;
  *(_DWORD *)(a2 + 48) = dword_662E2C;
  *(float *)(a2 + 128) = rf_graphics_gamma;
  *(_DWORD *)(a2 + 108) = *(_DWORD *)(a1 + 3916);
  *(_DWORD *)(a2 + 112) = *(_DWORD *)(a1 + 3920);
  *(_DWORD *)(a2 + 116) = *(_DWORD *)(a1 + 3924);
  *(_DWORD *)(a2 + 120) = 0;
  *(_DWORD *)(a2 + 120) |= *(_BYTE *)(a1 + 3892) != 0;
  *(_DWORD *)(a2 + 120) |= *(_BYTE *)(a1 + 3894) != 0 ? 2 : 0;
  *(_DWORD *)(a2 + 120) |= *(_BYTE *)(a1 + 3895) != 0 ? 4 : 0;
  *(_DWORD *)(a2 + 120) |= *(_BYTE *)(a1 + 3896) != 0 ? 8 : 0;
  *(_DWORD *)(a2 + 120) |= *(_BYTE *)(a1 + 3897) != 0 ? 0x10 : 0;
  *(_DWORD *)(a2 + 120) |= *(_BYTE *)(a1 + 3898) != 0 ? 0x20 : 0;
  *(_DWORD *)(a2 + 120) |= *(_BYTE *)(a1 + 3899) != 0 ? 0x40 : 0;
  *(_DWORD *)(a2 + 120) |= *(_BYTE *)(a1 + 3900) != 0 ? 0x80 : 0;
  *(_DWORD *)(a2 + 120) |= *(_BYTE *)(a1 + 3901) != 0 ? 0x100 : 0;
  *(_DWORD *)(a2 + 120) |= *(_BYTE *)(a1 + 3902) != 0 ? 0x200 : 0;
  *(_DWORD *)(a2 + 120) |= *(_BYTE *)(a1 + 3903) != 0 ? 0x400 : 0;
  *(_DWORD *)(a2 + 120) |= *(_BYTE *)(a1 + 3893) != 0 ? 0x800 : 0;
  *(_DWORD *)(a2 + 120) |= *(_BYTE *)(a1 + 3904) != 0 ? 0x1000 : 0;
  *(_DWORD *)(a2 + 120) |= *(_BYTE *)(a1 + 3905) != 0 ? 0x2000 : 0;
  *(_DWORD *)(a2 + 120) |= *(_BYTE *)(a1 + 3906) != 0 ? 0x8000 : 0;
  *(_DWORD *)(a2 + 120) |= *(_BYTE *)(a1 + 3907) != 0 ? 0x10000 : 0;
  *(_DWORD *)(a2 + 120) |= *(_BYTE *)(a1 + 3908) != 0 ? 0x20000 : 0;
  *(_DWORD *)(a2 + 120) |= *(_BYTE *)(a1 + 3909) != 0 ? 0x40000 : 0;
  *(_DWORD *)(a2 + 120) |= *(_BYTE *)(a1 + 3910) != 0 ? 0x80000 : 0;
  *(_DWORD *)(a2 + 120) |= *(_BYTE *)(a1 + 3911) != 0 ? 0x100000 : 0;
  *(_DWORD *)(a2 + 120) |= *(_BYTE *)(a1 + 3912) != 0 ? 0x200000 : 0;
  v5 = rf_string_object_c_str_or_empty((const void *)(a1 + 8));
  v4 = (_BYTE *)(a2 + 52);
  do
  {
    v3 = *v5;
    *v4++ = *v5++;
  }
  while ( v3 );
  *(_DWORD *)(a2 + 100) = *(_DWORD *)(a1 + 3932);
  for ( i = 0; i < 32; ++i )
    *(_WORD *)(a2 + 2 * i + 200) = *(_WORD *)(a1 + 4 * i + 4436);
  return rf_player_embedded_options_pack_792(a2 + 264, a1 + 228);
}

