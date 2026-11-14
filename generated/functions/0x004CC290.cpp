// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CC290 rf_particle_spawn_collision_fragment
// UNREALRED VERIFIED [combat-particle-contact-20261104]: Appends clone to matching emitter/global active-list tail. Copies source handle, primary flags, bitmap handle/count, start/destination/current packed colors, position, acceleration/gravity/growth, room/callback/emitter/pool, and current age. Radius=parent-current-radius*0.75; life=parent-full-life*random_float_range(0.9,1.2); velocity supplied by caller. Does NOT initialize/copy secondary flags +78, rotation +84, or VBM-finish fraction +92, leaving reused pool-slot values. Caller already shrinks parent radius by0.75 (child net0.5625) and checks pool count. Omitted-slot fields require explicit adapter policy, not claimed inheritance.
_DWORD *__cdecl rf_particle_spawn_collision_fragment(int a1, const float source, int a3, int a4, float a5)
{
  _DWORD *result; // eax
  float v6[3]; // [esp+8h] [ebp-20h] BYREF
  float copy_result[3]; // [esp+14h] [ebp-14h] BYREF
  _DWORD *v8; // [esp+20h] [ebp-8h]
  int v9; // [esp+24h] [ebp-4h]

  v8 = (_DWORD *)((char *)&unk_866600 + 252 * *(char *)(a1 + 80));
  v9 = v8[2];
  **(_DWORD **)(v9 + 4) = *(_DWORD *)v9;
  *(_DWORD *)(*(_DWORD *)v9 + 4) = *(_DWORD *)(v9 + 4);
  *(_DWORD *)v9 = 0;
  *(_DWORD *)(v9 + 4) = 0;
  if ( *(_DWORD *)(a1 + 104) )
  {
    *(_DWORD *)(v9 + 4) = *(_DWORD *)(*(_DWORD *)(a1 + 104) + 180);
    *(_DWORD *)v9 = *(_DWORD *)(a1 + 104) + 176;
    **(_DWORD **)(*(_DWORD *)(a1 + 104) + 180) = v9;
    *(_DWORD *)(*(_DWORD *)(a1 + 104) + 180) = v9;
  }
  else if ( *(_BYTE *)(a1 + 80) == 1 )
  {
    *(_DWORD *)(v9 + 4) = unk_867C64;
    *(_DWORD *)v9 = &unk_867C60;
    *unk_867C64 = v9;
    unk_867C64 = v9;
  }
  else
  {
    *(_DWORD *)(v9 + 4) = v8[33];
    *(_DWORD *)v9 = v8 + 32;
    *(_DWORD *)v8[33] = v9;
    v8[33] = v9;
  }
  *(_DWORD *)(v9 + 8) = *(_DWORD *)(a1 + 8);
  *(_DWORD *)(v9 + 88) = *(_DWORD *)(a1 + 88);
  *(_DWORD *)(v9 + 72) = *(_DWORD *)(a1 + 72);
  *(_WORD *)(v9 + 76) = *(_WORD *)(a1 + 76);
  *(float *)(v9 + 56) = *(float *)(a1 + 56) * a5;
  *(_DWORD *)(v9 + 40) = *(_DWORD *)(a1 + 40);
  *(_DWORD *)(v9 + 44) = *(_DWORD *)(a1 + 44);
  *(_DWORD *)(v9 + 48) = *(_DWORD *)(a1 + 48);
  *(float *)(v9 + 52) = rf_random_float_range(0.89999998, 1.2) * *(float *)(a1 + 52);
  rf_vector_copy((float *)(v9 + 12), copy_result, (const float *)(a1 + 12));
  *(float *)(v9 + 64) = *(float *)(a1 + 64);
  *(float *)(v9 + 68) = *(float *)(a1 + 68);
  *(float *)(v9 + 60) = *(float *)(a1 + 60);
  rf_vector_copy((float *)(v9 + 24), v6, &source);
  *(float *)(v9 + 36) = *(float *)(a1 + 36);
  *(_DWORD *)(v9 + 100) = *(_DWORD *)(a1 + 100);
  *(_DWORD *)(v9 + 96) = *(_DWORD *)(a1 + 96);
  *(_BYTE *)(v9 + 80) = *(_BYTE *)(a1 + 80);
  *(_DWORD *)(v9 + 104) = *(_DWORD *)(a1 + 104);
  result = v8;
  ++v8[62];
  return result;
}

