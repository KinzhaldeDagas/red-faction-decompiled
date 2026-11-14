// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047FC70 rf_rfl_push_regions_section_load
// UNREALRED VERIFIED [combat-particle-wind-20261029]: Section1100 records read UID,string,position,matrix file vectors forward/right/up,string,discarded normalized bool,shape. Shape1 reads radius only for version>=103 (else1), shape2/3 read full dimensions. Then read strength float and raw uint32 flags; initialize enabled+0x68=1 independently of serialized bool. Matrix stream helper59FBC0 writes file vectors at runtime+48,+24,+36; retain raw axes for containment/force. Float decompiler defaults are not evidence of discarded reads: disassembly stores x87 returned radius/strength.
void *__cdecl rf_rfl_push_regions_section_load(_DWORD *a1)
{
  void *result; // eax
  int v2; // eax
  int v3; // eax
  double float_versioned; // st7
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  double v10; // st7
  float *v11; // eax
  double v12; // st7
  double v13; // st7
  int uint32_versioned; // eax
  int v15; // [esp+8h] [ebp-D0h]
  char *v16; // [esp+Ch] [ebp-CCh]
  float v17[3]; // [esp+10h] [ebp-C8h] BYREF
  int v18[3]; // [esp+1Ch] [ebp-BCh] BYREF
  float v19[3]; // [esp+28h] [ebp-B0h] BYREF
  float sum_result[3]; // [esp+34h] [ebp-A4h] BYREF
  float v21[3]; // [esp+40h] [ebp-98h] BYREF
  float out_vector[3]; // [esp+4Ch] [ebp-8Ch] BYREF
  float v23[3]; // [esp+58h] [ebp-80h] BYREF
  int v24[3]; // [esp+64h] [ebp-74h] BYREF
  float v25[3]; // [esp+70h] [ebp-68h] BYREF
  int v26[3]; // [esp+7Ch] [ebp-5Ch] BYREF
  float copy_result[3]; // [esp+88h] [ebp-50h] BYREF
  int v28[3]; // [esp+94h] [ebp-44h] BYREF
  void *v29; // [esp+A0h] [ebp-38h]
  char *v30; // [esp+A4h] [ebp-34h]
  float v31[3]; // [esp+A8h] [ebp-30h] BYREF
  char *v32; // [esp+B4h] [ebp-24h]
  float rhs[3]; // [esp+B8h] [ebp-20h] BYREF
  int i; // [esp+C4h] [ebp-14h]
  int int32_versioned; // [esp+C8h] [ebp-10h]
  int v36; // [esp+D4h] [ebp-4h]

  int32_versioned = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  result = rf_vector3_default_construct_noop(rhs);
  for ( i = 0; i < int32_versioned; ++i )
  {
    v29 = operator new(0x6Cu);
    v36 = 0;
    if ( v29 )
      v16 = rf_push_region_construct_noop((char *)v29);
    else
      v16 = nullptr;
    v30 = v16;
    v36 = -1;
    v32 = v16;
    v2 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    *((_DWORD *)v32 + 1) = v2;
    rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    rf_binary_stream_read_vector3_versioned(a1, (float *)v32 + 3, 0, unk_1C8FBDC);
    rf_binary_stream_read_matrix3_vectors_201_versioned(v32 + 24, 0, (int)unk_1C8FC18);
    rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    rf_binary_stream_read_bool_versioned(a1, 0, 1);
    v3 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    *(_DWORD *)v32 = v3;
    v15 = *(_DWORD *)v32;
    if ( *(_DWORD *)v32 == 1 )
    {
      float_versioned = rf_binary_stream_read_float_versioned(a1, 103, 1.0);
      *((float *)v32 + 15) = float_versioned;
      v5 = rf_vector3_subtract_scalar_from_components((float *)v32 + 3, (float *)v28, *((float *)v32 + 15));
      rf_vector_copy((float *)v32 + 16, copy_result, v5);
      v6 = rf_vector3_add_scalar_to_components((float *)v32 + 3, (float *)v26, *((float *)v32 + 15));
      rf_vector_copy((float *)v32 + 19, v25, v6);
      *((float *)v32 + 15) = *((float *)v32 + 15) * *((float *)v32 + 15);
    }
    else if ( v15 == 2 )
    {
      rf_binary_stream_read_vector3_versioned(a1, (float *)v32 + 22, 0, unk_1C8FBDC);
      v7 = rf_vector_divide((float *)v32 + 22, (float *)v24, 2.0);
      rf_vector_copy(rhs, v23, v7);
      v8 = rf_vector_subtract((const float *)v32 + 3, out_vector, rhs);
      rf_vector_copy((float *)v32 + 16, v21, v8);
      v9 = rf_vector_add((const float *)v32 + 3, sum_result, rhs);
      rf_vector_copy((float *)v32 + 19, v19, v9);
      v10 = rf_vector_length_squared(rhs);
      *((float *)v32 + 15) = v10;
    }
    else if ( v15 == 3 )
    {
      rf_binary_stream_read_vector3_versioned(a1, (float *)v32 + 22, 0, unk_1C8FBDC);
      v11 = rf_vector_divide((float *)v32 + 22, (float *)v18, 2.0);
      rf_vector_copy(rhs, v17, v11);
      rf_vector_negate(rhs, v31);
      rf_aabb_transform_matrix_translate(
        (int)(v32 + 24),
        (float *)v32 + 3,
        (int)v31,
        (int)rhs,
        (float *)v32 + 16,
        (float *)v32 + 19);
      v12 = rf_vector_length_squared(rhs);
      *((float *)v32 + 15) = v12;
    }
    v13 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    *((float *)v32 + 25) = v13;
    uint32_versioned = rf_binary_stream_read_uint32_versioned(a1, 0, 0);
    *((_DWORD *)v32 + 2) = uint32_versioned;
    v32[104] = 1;
    rf_pointer_array_append_dword(rf_push_region_registry, (int)v32);
    result = (void *)(i + 1);
  }
  return result;
}

