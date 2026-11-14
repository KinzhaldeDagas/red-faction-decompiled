// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004457E0 rf_entity_transform_motion_vector_by_selected_rows
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion integration, selected-row transforms, angular/tensor updates, contact velocity response and x87 gates): Cdecl(outVector,entity,inputVector),THREE stack pointers,caller pops12,returns outVector EAX. Corrects saved two-argument integer prototype; all three native callers4D6B52/4D6EAA/4D8316 supply third vector. Builds temporary3x3 matrix by independently selecting EACH row using current movement descriptor entity2136 DWORD8/12/16. Selector1 copies corresponding row of entity2016;2 copies corresponding row of current entity252;3 copies corresponding row through entity2140;every other selector zeroes that row. No fallthrough or normalization. Reads inputVector through ECX at final559150; output is linear combination of selected rows weighted by inputXYZ. Writes all output components; constructor itself is
// no-op but every row is assigned. No own NULL/entity-class/descriptor/external-row pointer validation,finite or orthonormality check; zero/incoherent bases allowed.
float *__cdecl rf_entity_transform_motion_vector_by_selected_rows(
        float *out_vector,
        int entity,
        const float *input_vector)
{
  int v4; // [esp+0h] [ebp-9Ch]
  int v5; // [esp+4h] [ebp-98h]
  int v6; // [esp+8h] [ebp-94h]
  float v7[3]; // [esp+Ch] [ebp-90h] BYREF
  float v8[3]; // [esp+18h] [ebp-84h] BYREF
  float v9[3]; // [esp+24h] [ebp-78h] BYREF
  float v10[3]; // [esp+30h] [ebp-6Ch] BYREF
  float v11[3]; // [esp+3Ch] [ebp-60h] BYREF
  float v12[3]; // [esp+48h] [ebp-54h] BYREF
  float v13[3]; // [esp+54h] [ebp-48h] BYREF
  float v14[3]; // [esp+60h] [ebp-3Ch] BYREF
  float copy_result[3]; // [esp+6Ch] [ebp-30h] BYREF
  float destination[3]; // [esp+78h] [ebp-24h] BYREF
  float v17[3]; // [esp+84h] [ebp-18h] BYREF
  float v18[3]; // [esp+90h] [ebp-Ch] BYREF

  rf_matrix3_construct((char *)destination);
  v6 = *(_DWORD *)(*(_DWORD *)(entity + 2136) + 8);
  switch ( v6 )
  {
    case 1:
      rf_vector_copy(destination, copy_result, (const float *)(entity + 2016));
      break;
    case 2:
      rf_vector_copy(destination, v14, (const float *)(entity + 252));
      break;
    case 3:
      rf_vector_copy(destination, v13, *(const float **)(entity + 2140));
      break;
    default:
      rf_vector3_zero_return_destination(destination);
      break;
  }
  v5 = *(_DWORD *)(*(_DWORD *)(entity + 2136) + 12);
  switch ( v5 )
  {
    case 1:
      rf_vector_copy(v17, v12, (const float *)(entity + 2028));
      break;
    case 2:
      rf_vector_copy(v17, v11, (const float *)(entity + 264));
      break;
    case 3:
      rf_vector_copy(v17, v10, (const float *)(*(_DWORD *)(entity + 2140) + 12));
      break;
    default:
      rf_vector3_zero_return_destination(v17);
      break;
  }
  v4 = *(_DWORD *)(*(_DWORD *)(entity + 2136) + 16);
  switch ( v4 )
  {
    case 1:
      rf_vector_copy(v18, v9, (const float *)(entity + 2040));
      break;
    case 2:
      rf_vector_copy(v18, v8, (const float *)(entity + 276));
      break;
    case 3:
      rf_vector_copy(v18, v7, (const float *)(*(_DWORD *)(entity + 2140) + 24));
      break;
    default:
      rf_vector3_zero_return_destination(v18);
      break;
  }
  rf_matrix3_rotate_vector((float *)input_vector, out_vector, destination);
  return out_vector;
}

