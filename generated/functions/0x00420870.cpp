// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00420870 sub_420870
// UNREALRED VERIFIED [combat-speech-providers-20261111]: Writes retained Entity+7D4 reference point. No eyeNode or gameplayclassFlags2 bit0x20 (table name drools slime) =>commonposition+3C. linked_eye bit0x40=>current eye-node world transform. Otherwise rotate cached modelclass+9C/+A8 andaddcommonpos; canonical current138C/pending1390 slots8/9/10 are crouched. If total1394>0 and classes differ: float alpha=elapsed1398/total, currentcrouch reverses alpha=1-alpha, float beta=1-alpha; weighted rotated vectors. No host clamp or camera fallback is native behavior.
float *__cdecl sub_420870(int a1)
{
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float v9; // [esp+0h] [ebp-F0h]
  float *scalar; // [esp+8h] [ebp-E8h]
  float v11; // [esp+Ch] [ebp-E4h]
  bool v12; // [esp+10h] [ebp-E0h]
  bool v13; // [esp+14h] [ebp-DCh]
  float v14[3]; // [esp+18h] [ebp-D8h] BYREF
  float v15[3]; // [esp+24h] [ebp-CCh] BYREF
  float v16[3]; // [esp+30h] [ebp-C0h] BYREF
  float v17[3]; // [esp+3Ch] [ebp-B4h] BYREF
  float v18[3]; // [esp+48h] [ebp-A8h] BYREF
  float v19[3]; // [esp+54h] [ebp-9Ch] BYREF
  float v20[3]; // [esp+60h] [ebp-90h] BYREF
  float copy_result[3]; // [esp+6Ch] [ebp-84h] BYREF
  float sum_result[3]; // [esp+78h] [ebp-78h] BYREF
  float scaled_result[3]; // [esp+84h] [ebp-6Ch] BYREF
  float v24[3]; // [esp+90h] [ebp-60h] BYREF
  float v25[3]; // [esp+9Ch] [ebp-54h] BYREF
  float v26[3]; // [esp+A8h] [ebp-48h] BYREF
  float v27; // [esp+B4h] [ebp-3Ch]
  char v28; // [esp+BBh] [ebp-35h]
  float destination[3]; // [esp+BCh] [ebp-34h] BYREF
  char v30; // [esp+CBh] [ebp-25h]
  char v31[36]; // [esp+CCh] [ebp-24h] BYREF

  if ( *(_DWORD *)(*(_DWORD *)(a1 + 668) + 492) == -1 || (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1832) & 0x20) != 0 )
    return rf_vector_copy((float *)(a1 + 2004), v14, (const float *)(a1 + 60));
  if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1832) & 0x40) != 0 )
  {
    rf_matrix3_construct(v31);
    return (float *)rf_vmesh_compose_prop_world_transform(
                      *(_DWORD *)(a1 + 128),
                      *(_DWORD *)(*(_DWORD *)(a1 + 668) + 492),
                      (float *)(a1 + 72),
                      a1 + 60,
                      (int)v31,
                      (float *)(a1 + 2004));
  }
  else
  {
    v13 = *(_DWORD *)(a1 + 5004) == 8 || *(_DWORD *)(a1 + 5004) == 9 || *(_DWORD *)(a1 + 5004) == 10;
    v30 = v13;
    v12 = *(_DWORD *)(a1 + 5008) == 8 || *(_DWORD *)(a1 + 5008) == 9 || *(_DWORD *)(a1 + 5008) == 10;
    v28 = v12;
    rf_vector3_default_construct_noop(destination);
    if ( *(float *)(a1 + 5012) <= 0.0 || v30 == v28 )
    {
      if ( v30 == 1 )
      {
        v6 = rf_matrix3_rotate_vector((float *)(*(_DWORD *)(a1 + 668) + 168), v20, (float *)(a1 + 72));
        rf_vector_copy(destination, v19, v6);
      }
      else
      {
        v7 = rf_matrix3_rotate_vector((float *)(*(_DWORD *)(a1 + 668) + 156), v18, (float *)(a1 + 72));
        rf_vector_copy(destination, v17, v7);
      }
    }
    else
    {
      v27 = *(float *)(a1 + 5016) / *(float *)(a1 + 5012);
      if ( v30 == 1 )
        v27 = 1.0 - v27;
      v11 = 1.0 - v27;
      v2 = rf_matrix3_rotate_vector((float *)(*(_DWORD *)(a1 + 668) + 156), v24, (float *)(a1 + 72));
      scalar = rf_vector_multiply_scalar(v2, scaled_result, v11);
      v9 = v27;
      v3 = rf_matrix3_rotate_vector((float *)(*(_DWORD *)(a1 + 668) + 168), v26, (float *)(a1 + 72));
      v4 = rf_vector_multiply_scalar(v3, v25, v9);
      v5 = rf_vector_add(v4, sum_result, scalar);
      rf_vector_copy(destination, copy_result, v5);
    }
    v8 = rf_vector_add((const float *)(a1 + 60), v16, destination);
    return rf_vector_copy((float *)(a1 + 2004), v15, v8);
  }
}

