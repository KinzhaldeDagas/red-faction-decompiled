// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00524030 rf_world_decal_recreate_from_current_fields
// UNREALRED VERIFIED [decal-projection-20261028]: Copies context+72,owner pointers+64/+68,position+0,matrix+12,dimensions+48,bitmap+60,alpha+76,flags+80,extra+84,scalar+88 to locals. Fully removes/recycles original through0x524100 BEFORE calling creator0x521AF0 with copied fields. Returns replacement ornull; may reuse old slot, no rollback/restoration if creation fails. Polygon geometry rebuilt rather than copied.
float *__cdecl rf_world_decal_recreate_from_current_fields(int a1)
{
  int v2[3]; // [esp+4h] [ebp-5Ch] BYREF
  int v3; // [esp+10h] [ebp-50h]
  int v4; // [esp+14h] [ebp-4Ch]
  int v5[3]; // [esp+18h] [ebp-48h] BYREF
  float v6; // [esp+24h] [ebp-3Ch]
  int v7; // [esp+28h] [ebp-38h]
  int v8[9]; // [esp+2Ch] [ebp-34h] BYREF
  int v9; // [esp+50h] [ebp-10h]
  char v10[4]; // [esp+54h] [ebp-Ch]
  int v11; // [esp+58h] [ebp-8h]
  int v12; // [esp+5Ch] [ebp-4h]

  v9 = *(_DWORD *)(a1 + 72);
  v3 = *(_DWORD *)(a1 + 64);
  v7 = *(_DWORD *)(a1 + 68);
  rf_vector3_copy_return_destination((float *)v2, (float *)a1);
  rf_matrix3_copy_construct((int)v8, (const void *)(a1 + 12));
  rf_vector3_copy_return_destination((float *)v5, (float *)(a1 + 48));
  v4 = *(_DWORD *)(a1 + 60);
  *(_DWORD *)v10 = *(unsigned __int8 *)(a1 + 76);
  v11 = *(_DWORD *)(a1 + 80);
  v12 = *(_DWORD *)(a1 + 84);
  v6 = *(float *)(a1 + 88);
  rf_world_decal_remove_spatial_links_and_recycle((_DWORD *)a1);
  return rf_world_decal_create_volume_and_project(
           v9,
           v3,
           v7,
           (float *)v2,
           (float *)v8,
           (float *)v5,
           v4,
           v10[0],
           v11,
           v12,
           v6);
}

