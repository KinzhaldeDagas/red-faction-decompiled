// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580750 rf_volume_box_create_identity_orientation
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Allocates136-byte volume,tag2,RGB bytes1..3,strength float4,center8,dimensions60. Copies supplied matrix into24..59,THEN IMMEDIATELY overwrites it with identity via40D520/55BEA0;authored orientation therefore ignored for created boxes. Appends pointer to owned array18CCFF4,returns pointer. Cached fields uninitialized until preparation,no dimension checks;NULL allocation still dereferenced. Preserve actual identity-overwrite behavior.
float *__cdecl rf_volume_box_create_identity_orientation(
        float *source,
        float *a2,
        float *a3,
        float a4,
        char a5,
        char a6,
        char a7)
{
  char *v8; // [esp+4h] [ebp-34h]
  float v9[3]; // [esp+8h] [ebp-30h] BYREF
  float copy_result[3]; // [esp+14h] [ebp-24h] BYREF
  void *v11; // [esp+20h] [ebp-18h]
  char *v12; // [esp+24h] [ebp-14h]
  char *v13; // [esp+28h] [ebp-10h]
  int v14; // [esp+34h] [ebp-4h]

  v11 = operator new(0x88u);
  v14 = 0;
  if ( v11 )
    v8 = rf_volume136_construct_members_noop((char *)v11);
  else
    v8 = nullptr;
  v12 = v8;
  v14 = -1;
  v13 = v8;
  *v8 = 2;
  rf_vector_copy((float *)v13 + 2, copy_result, source);
  rf_matrix3_copy((float *)v13 + 6, a2);
  rf_identity_orientation_matrix((float *)v13 + 6);
  rf_vector_copy((float *)v13 + 15, v9, a3);
  *((float *)v13 + 1) = a4;
  v13[1] = a5;
  v13[2] = a6;
  v13[3] = a7;
  rf_pointer_array_append_dword(unk_18CCFF4, (int)v13);
  return (float *)v13;
}

