// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00513DC0 rf_shadow_projector276_copy_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projected mesh decal pools,shadow records,x87 unordered filters and recovered no-op constructors,original ECX/stack flow and PE bytes): Thiscall destination276,source276*,RET4,returndestination. Copy six16-byte planes0..95; vectors96/108/120; four vectors132..179; matrix180..215; vectors216/228/240; fiveF32 scalar fields252/256/260/264/268 viaFLD/FSTP; rawDWORD272. Covers complete276-byte logical record without allocation,normalization,ownership increment or geometry transformation. Exact self-copy works;arbitrary partial overlap is not protected by whole-record snapshot. Float members pass through x87 helpers/stores,so do not infer universal raw-bit preservation for signaling NaNs.
int __thiscall rf_shadow_projector276_copy_members(int this, int a2)
{
  float v4[3]; // [esp+4h] [ebp-5Ch] BYREF
  float v5[3]; // [esp+10h] [ebp-50h] BYREF
  float v6[3]; // [esp+1Ch] [ebp-44h] BYREF
  float v7[3]; // [esp+28h] [ebp-38h] BYREF
  float v8[3]; // [esp+34h] [ebp-2Ch] BYREF
  float v9[3]; // [esp+40h] [ebp-20h] BYREF
  float copy_result[3]; // [esp+4Ch] [ebp-14h] BYREF
  unsigned int j; // [esp+58h] [ebp-8h]
  unsigned int i; // [esp+5Ch] [ebp-4h]

  for ( i = 0; i < 6; ++i )
    rf_plane_copy((float *)(this + 16 * i), (float *)(a2 + 16 * i));
  rf_vector_copy((float *)(this + 96), copy_result, (const float *)(a2 + 96));
  rf_vector_copy((float *)(this + 108), v9, (const float *)(a2 + 108));
  rf_vector_copy((float *)(this + 120), v8, (const float *)(a2 + 120));
  for ( j = 0; j < 4; ++j )
    rf_vector_copy((float *)(this + 12 * j + 132), v7, (const float *)(a2 + 12 * j + 132));
  rf_matrix3_copy((float *)(this + 180), (const float *)(a2 + 180));
  rf_vector_copy((float *)(this + 216), v6, (const float *)(a2 + 216));
  rf_vector_copy((float *)(this + 228), v5, (const float *)(a2 + 228));
  rf_vector_copy((float *)(this + 240), v4, (const float *)(a2 + 240));
  *(float *)(this + 252) = *(float *)(a2 + 252);
  *(float *)(this + 256) = *(float *)(a2 + 256);
  *(float *)(this + 260) = *(float *)(a2 + 260);
  *(float *)(this + 264) = *(float *)(a2 + 264);
  *(float *)(this + 268) = *(float *)(a2 + 268);
  *(_DWORD *)(this + 272) = *(_DWORD *)(a2 + 272);
  return this;
}

