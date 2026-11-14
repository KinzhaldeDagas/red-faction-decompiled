// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00585670 rf_character_instance_initialize
// UNREALRED VERIFIED [animation-mix-decode]: Initializes CharacterInstance matrices, 16 active animation records, root offset, counters, and freeze/alone indices.
int __thiscall rf_character_instance_initialize(int this, int a2)
{
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float v7[3]; // [esp+10h] [ebp-58h] BYREF
  float v8[3]; // [esp+1Ch] [ebp-4Ch] BYREF
  float v9[3]; // [esp+28h] [ebp-40h] BYREF
  float v10[3]; // [esp+34h] [ebp-34h] BYREF
  float v11[3]; // [esp+40h] [ebp-28h] BYREF
  float copy_result[3]; // [esp+4Ch] [ebp-1Ch] BYREF
  float v13[3]; // [esp+58h] [ebp-10h] BYREF
  int i; // [esp+64h] [ebp-4h]

  rf_vector_construct_no_unwind((char *)this, 0x30u, 50, rf_affine3x4_default_construct_noop);
  rf_vector_construct_no_unwind((char *)(this + 2400), 0x30u, 50, rf_affine3x4_default_construct_noop);
  rf_vector3_default_construct_noop((void *)(this + 4800));
  rf_vector_construct_no_unwind(
    (char *)(this + 5012),
    0x30u,
    50,
    (void *(__thiscall *)(void *))rf_character_override_record_construct);
  rf_vector3_default_construct_noop((void *)(this + 7432));
  rf_vector3_default_construct_noop((void *)(this + 7456));
  rf_vector3_default_construct_noop((void *)(this + 7468));
  rf_vector3_default_construct_noop((void *)(this + 7480));
  memset((void *)this, 0, 0x1D5Cu);
  *(_DWORD *)(this + 4816) = 0;
  *(_DWORD *)(this + 7420) = -1;
  *(_DWORD *)(this + 7424) = -1;
  *(_DWORD *)(this + 7496) = -1;
  *(_BYTE *)(this + 7500) = 0;
  *(float *)(this + 7412) = 0.0;
  *(_DWORD *)(this + 7504) = a2;
  memset((void *)(this + 5012), 0, 0x960u);
  memset((void *)(this + 4820), 0, 0xC0u);
  *(_WORD *)(this + 7416) = 1;
  *(_WORD *)(this + 7492) = 0;
  *(float *)(this + 7428) = 0.0;
  v2 = rf_vector3_set_components_return_destination(v13, 0.0, 0.0, 0.0);
  rf_vector_copy((float *)(this + 4800), copy_result, v2);
  *(float *)(this + 7448) = 0.0;
  *(float *)(this + 7452) = *(float *)(this + 7448);
  v3 = rf_vector3_set_components_return_destination(v11, 0.0, 0.0, 0.0);
  rf_vector_copy((float *)(this + 7456), v10, v3);
  rf_vector_copy((float *)(this + 7468), v9, (const float *)(this + 7456));
  v4 = rf_vector3_set_components_return_destination(v8, 0.0, 0.0, 0.0);
  rf_vector_copy((float *)(this + 7480), v7, v4);
  *(_BYTE *)(this + 7444) = 0;
  for ( i = 0; i < 50; ++i )
    rf_identity_orientation_matrix((float *)(this + 48 * i + 5016));
  if ( unk_18CDA28 )
  {
    *(_DWORD *)(*(_DWORD *)(unk_18CDA28 + 7512) + 7508) = this;
    *(_DWORD *)(this + 7512) = *(_DWORD *)(unk_18CDA28 + 7512);
    *(_DWORD *)(unk_18CDA28 + 7512) = this;
    *(_DWORD *)(this + 7508) = unk_18CDA28;
  }
  else
  {
    *(_DWORD *)(this + 7508) = this;
    *(_DWORD *)(this + 7512) = this;
  }
  unk_18CDA28 = this;
  return this;
}

