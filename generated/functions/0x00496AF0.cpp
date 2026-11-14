// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00496AF0 rf_ctf_return_flag_home
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF carrier transforms, return/capture ordering, scoring and packet layouts): 
// Cdecl(raw byte red selector, raw byte play sound). Any nonzero selector chooses red flag 77D6E4, saved room 77D6D0, position 77D714 and matrix 77D6EC; zero chooses blue flag
// 77D6E8, room 77D6D4, position 77D720 and matrix 77D738. No initial mode/authority/null guard. Only runtime mode 1 and authority exactly 1 clears score byte +6 for all players on
// opposing team (team exactly 1 for red reset, exactly 0 for blue reset). Any nonzero sound byte plays positional event65 at home position.
// Copies saved position to common/current/predicted +60/+228/+240 and matrix to common +72; bounds expand only for ORDERED radius +384 > 0, otherwise collapse including NaN. Clears
// common +124 mask04000000 and stores saved room. Clears definition DWORD[DWORD[flag+660]+68] bit2 and sets instance DWORD[flag+700] bit200. Always arms shared cooldown 77D72C for
// 500 ms and resets BOTH return timers 77D710/77D75C. Does not clear either global carrier pointer itself. Pose and timer changes occur outside the server-only score-byte loop.
_DWORD *__cdecl rf_ctf_return_flag_home(char a1, char a2)
{
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  int v7; // [esp+Ch] [ebp-E8h]
  int v8; // [esp+10h] [ebp-E4h]
  float v9[3]; // [esp+14h] [ebp-E0h] BYREF
  float v10[3]; // [esp+20h] [ebp-D4h] BYREF
  float v11[3]; // [esp+2Ch] [ebp-C8h] BYREF
  int v12[3]; // [esp+38h] [ebp-BCh] BYREF
  float v13[3]; // [esp+44h] [ebp-B0h] BYREF
  int v14[3]; // [esp+50h] [ebp-A4h] BYREF
  float v15[3]; // [esp+5Ch] [ebp-98h] BYREF
  float v16[3]; // [esp+68h] [ebp-8Ch] BYREF
  float v17[3]; // [esp+74h] [ebp-80h] BYREF
  float v18[3]; // [esp+80h] [ebp-74h] BYREF
  float v19[3]; // [esp+8Ch] [ebp-68h] BYREF
  float v20[3]; // [esp+98h] [ebp-5Ch] BYREF
  int v21[3]; // [esp+A4h] [ebp-50h] BYREF
  float v22[3]; // [esp+B0h] [ebp-44h] BYREF
  int v23[3]; // [esp+BCh] [ebp-38h] BYREF
  float v24[3]; // [esp+C8h] [ebp-2Ch] BYREF
  float v25[3]; // [esp+D4h] [ebp-20h] BYREF
  float copy_result[3]; // [esp+E0h] [ebp-14h] BYREF
  int j; // [esp+ECh] [ebp-8h]
  int i; // [esp+F0h] [ebp-4h]

  if ( a1 )
  {
    if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
    {
      for ( i = dword_87C324; i; i = v8 )
      {
        if ( *(_BYTE *)(i + 48) == 1 )
          *(_BYTE *)(*(_DWORD *)(i + 44) + 6) = 0;
        if ( *(_DWORD *)i == dword_87C324 )
          v8 = 0;
        else
          v8 = *(_DWORD *)i;
      }
    }
    if ( a2 )
      rf_gamesound_play_positional_event(65, unk_77D714, 1.0, (int)&unk_17F10B0, 0);
    rf_vector_copy((float *)(dword_77D6E4 + 60), copy_result, unk_77D714);
    rf_vector_copy((float *)(dword_77D6E4 + 228), v25, unk_77D714);
    rf_vector_copy((float *)(dword_77D6E4 + 240), v24, unk_77D714);
    if ( *(float *)(dword_77D6E4 + 384) <= 0.0 )
    {
      rf_vector_copy((float *)(dword_77D6E4 + 400), v19, (const float *)(dword_77D6E4 + 228));
      rf_vector_copy((float *)(dword_77D6E4 + 412), v18, (const float *)(dword_77D6E4 + 228));
    }
    else
    {
      v2 = rf_vector3_subtract_scalar_from_components(
             (float *)(dword_77D6E4 + 228),
             (float *)v23,
             *(float *)(dword_77D6E4 + 384));
      rf_vector_copy((float *)(dword_77D6E4 + 400), v22, v2);
      v3 = rf_vector3_add_scalar_to_components(
             (float *)(dword_77D6E4 + 228),
             (float *)v21,
             *(float *)(dword_77D6E4 + 384));
      rf_vector_copy((float *)(dword_77D6E4 + 412), v20, v3);
    }
    *(_DWORD *)(dword_77D6E4 + 124) &= ~0x4000000u;
    rf_matrix3_copy((float *)(dword_77D6E4 + 72), &flt_77D6EC);
    rf_object_store_room_pointer_only((_DWORD *)dword_77D6E4, unk_77D6D0);
    *(_DWORD *)(*(_DWORD *)(dword_77D6E4 + 660) + 68) &= ~2u;
    *(_DWORD *)(dword_77D6E4 + 700) |= 0x200u;
  }
  else
  {
    if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
    {
      for ( j = dword_87C324; j; j = v7 )
      {
        if ( !*(_BYTE *)(j + 48) )
          *(_BYTE *)(*(_DWORD *)(j + 44) + 6) = 0;
        if ( *(_DWORD *)j == dword_87C324 )
          v7 = 0;
        else
          v7 = *(_DWORD *)j;
      }
    }
    if ( a2 )
      rf_gamesound_play_positional_event(65, unk_77D720, 1.0, (int)&unk_17F10B0, 0);
    rf_vector_copy((float *)(dword_77D6E8 + 60), v17, unk_77D720);
    rf_vector_copy((float *)(dword_77D6E8 + 228), v16, unk_77D720);
    rf_vector_copy((float *)(dword_77D6E8 + 240), v15, unk_77D720);
    if ( *(float *)(dword_77D6E8 + 384) <= 0.0 )
    {
      rf_vector_copy((float *)(dword_77D6E8 + 400), v10, (const float *)(dword_77D6E8 + 228));
      rf_vector_copy((float *)(dword_77D6E8 + 412), v9, (const float *)(dword_77D6E8 + 228));
    }
    else
    {
      v4 = rf_vector3_subtract_scalar_from_components(
             (float *)(dword_77D6E8 + 228),
             (float *)v14,
             *(float *)(dword_77D6E8 + 384));
      rf_vector_copy((float *)(dword_77D6E8 + 400), v13, v4);
      v5 = rf_vector3_add_scalar_to_components(
             (float *)(dword_77D6E8 + 228),
             (float *)v12,
             *(float *)(dword_77D6E8 + 384));
      rf_vector_copy((float *)(dword_77D6E8 + 412), v11, v5);
    }
    *(_DWORD *)(dword_77D6E8 + 124) &= ~0x4000000u;
    rf_matrix3_copy((float *)(dword_77D6E8 + 72), &flt_77D738);
    rf_object_store_room_pointer_only((_DWORD *)dword_77D6E8, unk_77D6D4);
    *(_DWORD *)(*(_DWORD *)(dword_77D6E8 + 660) + 68) &= ~2u;
    *(_DWORD *)(dword_77D6E8 + 700) |= 0x200u;
  }
  rf_replicator_arm_milliseconds(&unk_77D72C, 500);
  rf_replicator_reset(&unk_77D710);
  return rf_replicator_reset(&unk_77D75C);
}

