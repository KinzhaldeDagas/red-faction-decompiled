// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054D700 rf_lightmap_uv_to_world_dispatch
// UNREALRED VERIFIED [lightmap-pixels-20261028]: Arguments lightmaprecord,normalizedatlasU,V,outputXYZ. Computes (U-recordfloat+84)/scale+76 and(V-recordfloat+88)/scale+80,then invokes selected mappingmember callback from table0x1425E98 indexed16*recordDWORD+92,with thisadjustmenttable0x1425E9C. Returns callbackresult. No selectorbound,zero-scale or outputvalidation; does not multiply atlasdimensions itself.
int __cdecl rf_lightmap_uv_to_world_dispatch(int a1, float a2, float a3, int a4)
{
  float v5; // [esp+18h] [ebp+Ch]
  float v6; // [esp+18h] [ebp+Ch]
  float v7; // [esp+1Ch] [ebp+10h]
  float v8; // [esp+1Ch] [ebp+10h]

  v5 = a2 - *(float *)(a1 + 84);
  v6 = v5 / *(float *)(a1 + 76);
  v7 = a3 - *(float *)(a1 + 88);
  v8 = v7 / *(float *)(a1 + 80);
  return ((int (__thiscall *)(int, _DWORD, _DWORD, int))unk_1425E98[4 * *(_DWORD *)(a1 + 92)])(
           unk_1425E9C[4 * *(_DWORD *)(a1 + 92)] + a1,
           LODWORD(v6),
           LODWORD(v8),
           a4);
}

