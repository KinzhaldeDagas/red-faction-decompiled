// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00539280 rf_geomod_face_lightmap_generate
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, lightmap clusters, tile mapping, atlas placement, seam blend snapshots, recovered halfplanes and original PE bytes): Thiscall solid,face,density;UNCONDITIONALLY allocates/registers new124-byte descriptor and stores its lowWORD index into face+54 BEFORE configuration. Does not test whether old lightmap index exists or release old descriptor. Builds one-face list,configures536B40,then fills tile RGB24 RAM pixels:ONE rand() per texel,gray=(lowByte(rand)&3F)+32,all three channels same32..95. Row stride=3*pageWidth,uses tile origin16/20 and tile width24/height28. Assigns entire flags byte8=08 (not OR),calls lighting/update/upload helper(descriptor,solid,0). Temporary list storage released then destructor sees NULL. No NULL descriptor/atlas failure checks,old-index rollback or random seed control;lower lighting helper can
// further modify data,so do not assume random fill is final GPU texel.
void __thiscall rf_geomod_face_lightmap_generate(void *this, int a2, float a3)
{
  char v3; // al
  int *v4; // [esp+8h] [ebp-48h]
  int *v6; // [esp+10h] [ebp-40h]
  int v7; // [esp+24h] [ebp-2Ch]
  int v8; // [esp+28h] [ebp-28h]
  int v9[3]; // [esp+2Ch] [ebp-24h] BYREF
  int *v10; // [esp+38h] [ebp-18h]
  int j; // [esp+3Ch] [ebp-14h]
  int i; // [esp+40h] [ebp-10h]
  int v13; // [esp+4Ch] [ebp-4h]

  v6 = (int *)operator new(0x7Cu);
  v13 = 0;
  if ( v6 )
    v4 = rf_lightmap_descriptor124_construct_register(v6, (int)this);
  else
    v4 = nullptr;
  v13 = -1;
  v10 = v4;
  *(_WORD *)(a2 + 54) = *(_WORD *)v4;
  rf_dword_array_construct_capacity(v9, 1);
  v13 = 1;
  rf_pointer_array_append_dword(v9, a2);
  rf_lightmap_descriptor_configure_faces((int)v10, (int)this, v9, (float *)a2, a3);
  rf_pointer_array_release_storage((void **)v9);
  v7 = 3 * *(_DWORD *)(v10[3] + 4) * v10[5];
  for ( i = 0; i < v10[7]; ++i )
  {
    v8 = 3 * v10[4];
    for ( j = 0; j < v10[6]; ++j )
    {
      v3 = rand();
      *(_BYTE *)(v8 + v7 + *(_DWORD *)(v10[3] + 12)) = (v3 & 0x3F) + 32;
      *(_BYTE *)(v8 + v7 + *(_DWORD *)(v10[3] + 12) + 1) = (v3 & 0x3F) + 32;
      *(_BYTE *)(v8 + v7 + *(_DWORD *)(v10[3] + 12) + 2) = (v3 & 0x3F) + 32;
      v8 += 3;
    }
    v7 += 3 * *(_DWORD *)(v10[3] + 4);
  }
  *((_BYTE *)v10 + 8) = 8;
  rf_lightmap_update_lighting_and_upload_rgb555((int)v10, (int)this, 0);
  v13 = -1;
  rf_pointer_array_destroy_backing_storage((void **)v9);
}

