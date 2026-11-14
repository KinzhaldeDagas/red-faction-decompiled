// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B1A00 rf_aabb_transform_matrix_translate
// UNREALRED VERIFIED [renderer-lighting-20261028]: Sixarguments matrix3,translation,inputmin,inputmax,outputmin,outputmax. Initializes both outputs totranslation. For each outputaxis(row) and inputcomponent,computes matrixelement*inputmin and*inputmax,adds smaller tooutputmincomponent andlarger tooutputmaxcomponent. Transforms axisaligned bounds including rotation/scaling/shear without enumerating8corners. No matrix or min<=max validation. Output initialization precedes reading allinputbounds,so source/outputalias unsafe. Return loopartifact3,not bounds pointer/success despite currentfloatpointertype.
float *__cdecl rf_aabb_transform_matrix_translate(
        char *a1,
        float *source,
        char *a3,
        char *a4,
        float *destination,
        float *a6)
{
  float *result; // eax
  char *v7; // esi
  char *v8; // esi
  double v9; // st7
  char *v10; // esi
  char *v11; // esi
  double v12; // st7
  char *v13; // esi
  char *v14; // esi
  double v15; // st7
  float v16[3]; // [esp+4h] [ebp-24h] BYREF
  float copy_result[3]; // [esp+10h] [ebp-18h] BYREF
  int i; // [esp+1Ch] [ebp-Ch]
  float v19; // [esp+20h] [ebp-8h]
  float v20; // [esp+24h] [ebp-4h]

  rf_vector_copy(destination, copy_result, source);
  result = rf_vector_copy(a6, v16, source);
  for ( i = 0; i < 3; ++i )
  {
    v7 = rf_vector_component_address_unchecked(a1, i);
    v20 = *(float *)v7 * *(float *)rf_vector_component_address_unchecked(a3, i);
    v8 = rf_vector_component_address_unchecked(a1, i);
    v19 = *(float *)v8 * *(float *)rf_vector_component_address_unchecked(a4, i);
    if ( v19 <= (double)v20 )
    {
      *destination = *destination + v19;
      result = a6;
      v9 = *a6 + v20;
    }
    else
    {
      *destination = *destination + v20;
      v9 = *a6 + v19;
      result = a6;
    }
    *a6 = v9;
  }
  for ( i = 0; i < 3; ++i )
  {
    v10 = rf_vector_component_address_unchecked(a1 + 12, i);
    v20 = *(float *)v10 * *(float *)rf_vector_component_address_unchecked(a3, i);
    v11 = rf_vector_component_address_unchecked(a1 + 12, i);
    v19 = *(float *)v11 * *(float *)rf_vector_component_address_unchecked(a4, i);
    if ( v19 <= (double)v20 )
    {
      result = destination;
      destination[1] = destination[1] + v19;
      v12 = a6[1] + v20;
    }
    else
    {
      destination[1] = destination[1] + v20;
      result = a6;
      v12 = a6[1] + v19;
    }
    a6[1] = v12;
  }
  for ( i = 0; i < 3; ++i )
  {
    v13 = rf_vector_component_address_unchecked(a1 + 24, i);
    v20 = *(float *)v13 * *(float *)rf_vector_component_address_unchecked(a3, i);
    v14 = rf_vector_component_address_unchecked(a1 + 24, i);
    v19 = *(float *)v14 * *(float *)rf_vector_component_address_unchecked(a4, i);
    if ( v19 <= (double)v20 )
    {
      destination[2] = destination[2] + v19;
      v15 = a6[2] + v20;
    }
    else
    {
      destination[2] = destination[2] + v20;
      v15 = a6[2] + v19;
    }
    a6[2] = v15;
    result = (float *)(i + 1);
  }
  return result;
}

