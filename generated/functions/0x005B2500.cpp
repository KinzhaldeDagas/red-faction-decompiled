// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B2500 rf_scene_model_instance_bind_definition
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model152 binding/update/draw, temporal/visibility edges, transform ordering, ribbon bounds and vector-result ABI): Thiscall152-byte state and292-byte definition pointer. Copies definition pivot148 to state center4,clears state flags28 masks20000000h/40000000h/80000000h while preserving low29 bits,sets active144=0,render orientation92 identity,and definition0=argument. Always requests12*definition.vertexCount176 bytes for owned vertices128; if allocation nonnull runs no-op vec3 constructors, leaving vertices unspecified. Nonzero faceCount180 (including negative) requests24*count UV bytes132; zero count setsNULL. Sets attachment translation32=zero,matrix44=identity,aux float148=0. Does not fill geometry/UV values,initialize dimensions16/20,model handle24,render position80 or other untouched fields. No size
// overflow/count/allocation validation or release of prior owned buffers before overwrite. EAX incidental last identity-matrix result, not uniform state/success API. Destroy helper5B26B0 deletes only owned128/132.
float *__thiscall rf_scene_model_instance_bind_definition(float *this, int a2)
{
  float *v2; // eax
  float *result; // eax
  void *v4; // [esp+10h] [ebp-48h]
  float v6[3]; // [esp+18h] [ebp-40h] BYREF
  float v7[3]; // [esp+24h] [ebp-34h] BYREF
  void *v8; // [esp+30h] [ebp-28h]
  void *v9; // [esp+34h] [ebp-24h]
  void *v10; // [esp+38h] [ebp-20h]
  int v11; // [esp+3Ch] [ebp-1Ch]
  float copy_result[3]; // [esp+40h] [ebp-18h] BYREF
  int v13; // [esp+54h] [ebp-4h]

  rf_vector_copy(this + 1, copy_result, (const float *)(a2 + 148));
  *((_DWORD *)this + 7) &= ~0x20000000u;
  *((_DWORD *)this + 7) &= ~0x40000000u;
  *((_BYTE *)this + 144) = 0;
  *((_DWORD *)this + 7) &= ~0x80000000;
  rf_identity_orientation_matrix(this + 23);
  *(_DWORD *)this = a2;
  v11 = *(_DWORD *)(a2 + 176);
  v9 = operator new(12 * v11);
  v13 = 0;
  if ( v9 )
  {
    rf_vector_construct_no_unwind((char *)v9, 0xCu, v11, rf_vector3_default_construct_noop);
    v4 = v9;
  }
  else
  {
    v4 = nullptr;
  }
  v10 = v4;
  v13 = -1;
  *((_DWORD *)this + 32) = v4;
  if ( *(_DWORD *)(a2 + 180) )
  {
    v8 = operator new(24 * *(_DWORD *)(a2 + 180));
    *((_DWORD *)this + 33) = v8;
  }
  else
  {
    *(this + 33) = 0.0;
  }
  v2 = rf_vector3_set_components_return_destination(v7, 0.0, 0.0, 0.0);
  rf_vector_copy(this + 8, v6, v2);
  result = rf_identity_orientation_matrix(this + 11);
  *(this + 37) = 0.0;
  return result;
}

