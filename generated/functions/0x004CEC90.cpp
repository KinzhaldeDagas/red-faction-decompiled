// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CEC90 rf_particle_emitter_create
// [UnrealRed burn initialization availability 2026-11-12; full original-byte ASM] Shared emitter CREATE: sentinel-free pool empty returns EAX0 BEFORE initializer/RNG. Otherwise unlinks free, invokes4CDAA0 and IGNORES AL, links emitter active, stores extents156/160, increments867900, returns emitter POINTER. Do not derive creation success/failure from initializer AL or a host resource availability bool. Shared native pool is128 records; representing only burn-local embedded controls does not establish pool parity.
int __cdecl rf_particle_emitter_create(int a1, float *a2, void *a3, float *a4, char a5)
{
  float v6; // [esp+0h] [ebp-14h]
  float v7; // [esp+4h] [ebp-10h]
  float v8; // [esp+8h] [ebp-Ch]
  int v9; // [esp+Ch] [ebp-8h]
  float v10; // [esp+10h] [ebp-4h]

  if ( (int *)unk_867E20 == dword_867CD8 )
    return 0;
  v9 = unk_867E20;
  *(_DWORD *)(*(_DWORD *)(unk_867E20 + 332) + 328) = *(_DWORD *)(unk_867E20 + 328);
  *(_DWORD *)(*(_DWORD *)(v9 + 328) + 332) = *(_DWORD *)(v9 + 332);
  *(_DWORD *)(v9 + 328) = 0;
  *(_DWORD *)(v9 + 332) = 0;
  rf_particle_emitter_initialize((char *)v9, a1, (int)a2, a3, a4, a5);
  *(_DWORD *)(v9 + 332) = unk_867A54;
  *(_DWORD *)(v9 + 328) = dword_867908;
  *(_DWORD *)(unk_867A54 + 328) = v9;
  unk_867A54 = v9;
  v8 = fabs(a2[19]);
  v7 = fabs(a2[20] * 9.800000190734863);
  v10 = v8 + v7;
  v6 = fabs(a2[9]);
  *(float *)(v9 + 156) = v10 * a2[15] * a2[15] * 0.5 + v6 * a2[15] + a2[17];
  *(float *)(v9 + 160) = 0.0;
  ++unk_867900;
  return v9;
}

