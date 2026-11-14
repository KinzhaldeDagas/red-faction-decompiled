// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049C440 rf_geomod_apply_live_boolean_payload41
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet registry, field permutations, x87 transfers, face-list mutation and HUD native stores):
// Original descriptor row41 at662B34 binds this callback under boolean. Cdecl payload pointer only consumed; dispatcher supplies an additional source word which this body ignores, no
// length passed. Initializes local runtime100-byte operation, then consumes25 DWORDs in the same permutation as sender49BDD0: runtime offsets
// [0,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,4,76,80,84,88,92,96]. Float slots undergo native FLD/FSTP. No payload size, source, authority, runtime, cutter-ID or
// finite-value check here. Resolve runtime id0 via cutter delegate, unconditionally dereference returned solid+96; impact size=operation float60*cutter float96. Default material is
// DWORD6FC338; flags56 bit10 selects bitmap ice_ice01.tga loaded(-1,1) without result validation. Spawn impact fragments using operation+8,size,operation+64,material,0 BEFORE
// execution_queue_append(operation). Returns append delegate EAX. Does not call operation_begin/step directly or arm shared replication timer.
int __cdecl rf_geomod_apply_live_boolean_payload41(int a1)
{
  int v2; // [esp+10h] [ebp-78h]
  float v3; // [esp+14h] [ebp-74h]
  int v4[2]; // [esp+18h] [ebp-70h] BYREF
  _DWORD v5[12]; // [esp+20h] [ebp-68h] BYREF
  int v6; // [esp+50h] [ebp-38h]
  float v7; // [esp+54h] [ebp-34h]
  _DWORD v8[10]; // [esp+58h] [ebp-30h] BYREF
  int v9; // [esp+80h] [ebp-8h]
  int v10; // [esp+84h] [ebp-4h]

  rf_geomod_operation_init((char *)v4);
  v9 = 0;
  v4[0] = *(_DWORD *)a1;
  v9 = 4;
  v5[0] = *(_DWORD *)(a1 + 4);
  v9 = 8;
  v5[1] = *(_DWORD *)(a1 + 8);
  v9 = 12;
  v5[2] = *(_DWORD *)(a1 + 12);
  v9 = 16;
  v5[3] = *(_DWORD *)(a1 + 16);
  v9 = 20;
  v5[4] = *(_DWORD *)(a1 + 20);
  v9 = 24;
  v5[5] = *(_DWORD *)(a1 + 24);
  v9 = 28;
  v5[6] = *(_DWORD *)(a1 + 28);
  v9 = 32;
  v5[7] = *(_DWORD *)(a1 + 32);
  v9 = 36;
  v5[8] = *(_DWORD *)(a1 + 36);
  v9 = 40;
  v5[9] = *(_DWORD *)(a1 + 40);
  v9 = 44;
  v5[10] = *(_DWORD *)(a1 + 44);
  v9 = 48;
  v5[11] = *(_DWORD *)(a1 + 48);
  v9 = 52;
  v6 = *(_DWORD *)(a1 + 52);
  v9 = 56;
  v7 = *(float *)(a1 + 56);
  v9 = 60;
  v8[0] = *(_DWORD *)(a1 + 60);
  v9 = 64;
  v8[1] = *(_DWORD *)(a1 + 64);
  v9 = 68;
  v8[2] = *(_DWORD *)(a1 + 68);
  v9 = 72;
  v4[1] = *(_DWORD *)(a1 + 72);
  v9 = 76;
  v8[3] = *(_DWORD *)(a1 + 76);
  v9 = 80;
  v8[4] = *(_DWORD *)(a1 + 80);
  v9 = 84;
  v8[5] = *(_DWORD *)(a1 + 84);
  v9 = 88;
  v8[6] = *(_DWORD *)(a1 + 88);
  v9 = 92;
  v8[7] = *(_DWORD *)(a1 + 92);
  v9 = 96;
  v8[8] = *(_DWORD *)(a1 + 96);
  v9 = 100;
  v10 = rf_geomod_cutter_resolve(v4[0]);
  v3 = v7 * *(float *)(v10 + 96);
  v2 = unk_6FC338;
  if ( (v6 & 0x10) != 0 )
    v2 = rf_bitmap_load_with_optional_mipmap_generation("ice_ice01.tga", (void *)0xFFFFFFFF, 1);
  rf_geomod_impact_fragment_spawn((int)v5, v3, (int)v8, v2, 0);
  return rf_geomod_execution_queue_append((int)v4);
}

