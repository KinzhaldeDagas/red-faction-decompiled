// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556BA0 rf_solid_project_selected_uvs_cylindrically
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): ECX solid plus matrixA,translationA,translationB,matrixB,angularRadius,unusedDWORD; RET24. Transforms selected textured-face corners through A then inverse B as556A70. Detects seam only when face has transformed corners with x>0,z>=0 AND x>0,z<0. For every corner angle=atan2(z,x), adds2pi if negative, then adds another2pi when seam flag AND z>=0. U=angle*angularRadius*globalScale/bitmapWidth, V=localY*globalScale/bitmapHeight. Dimensions queried per corner, initial16; sixth stack arg unused. No UV wrapping/clamping/secondary writes or radius validation.
void __thiscall rf_solid_project_selected_uvs_cylindrically(
        void *this,
        const float *a2,
        const float *a3,
        const float *a4,
        const float *a5,
        float a6,
        unsigned int a7)
{
  int first_dword; // eax
  int v8; // [esp+8h] [ebp-4Ch]
  int v9; // [esp+Ch] [ebp-48h]
  float v11; // [esp+14h] [ebp-40h]
  float v12; // [esp+18h] [ebp-3Ch]
  float Y[2]; // [esp+1Ch] [ebp-38h] BYREF
  float X; // [esp+24h] [ebp-30h]
  float v15; // [esp+28h] [ebp-2Ch]
  int v16; // [esp+2Ch] [ebp-28h] BYREF
  int v17; // [esp+30h] [ebp-24h] BYREF
  float v18[2]; // [esp+34h] [ebp-20h] BYREF
  float v19; // [esp+3Ch] [ebp-18h]
  char v20; // [esp+42h] [ebp-12h]
  char v21; // [esp+43h] [ebp-11h]
  int v22; // [esp+44h] [ebp-10h]
  int j; // [esp+48h] [ebp-Ch]
  char v24; // [esp+4Fh] [ebp-5h]
  int i; // [esp+50h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((char *)this + 216);
    if ( i >= first_dword )
      break;
    v22 = *(_DWORD *)sub_552200((_DWORD *)this + 54, i);
    if ( *(_DWORD *)(v22 + 48) != -1 )
    {
      v20 = 0;
      v21 = 0;
      v24 = 0;
      for ( j = *(_DWORD *)(v22 + 64); j; j = v9 )
      {
        rf_vector3_copy_return_destination(v18, *(float **)j);
        rf_vector_rotate_translate_in_place(v18, (int)a2, (int)a3);
        rf_vector_inverse_translate_rotate_in_place(v18, (int)a4, (int)a5);
        if ( v18[0] <= 0.0 || v19 < 0.0 )
        {
          if ( v18[0] > 0.0 && v19 < 0.0 )
            v24 = 1;
        }
        else
        {
          v21 = 1;
        }
        if ( v21 && v24 )
        {
          v20 = 1;
          break;
        }
        if ( *(_DWORD *)(j + 20) == *(_DWORD *)(v22 + 64) )
          v9 = 0;
        else
          v9 = *(_DWORD *)(j + 20);
      }
      for ( j = *(_DWORD *)(v22 + 64); j; j = v8 )
      {
        rf_vector3_copy_return_destination(Y, *(float **)j);
        rf_vector_rotate_translate_in_place(Y, (int)a2, (int)a3);
        rf_vector_inverse_translate_rotate_in_place(Y, (int)a4, (int)a5);
        v11 = atan2f(X, Y[0]);
        if ( v11 < 0.0 )
          v11 = v11 + 6.283185482025146;
        if ( v20 && X >= 0.0 )
          v11 = v11 + 6.283185482025146;
        v17 = 16;
        v16 = 16;
        rf_bitmap_get_resolved_dimensions(*(_DWORD *)(v22 + 48), &v17, &v16);
        v15 = flt_663E60 / (double)v17;
        v12 = flt_663E60 / (double)v16;
        *(float *)(j + 4) = v11 * a6 * v15;
        *(float *)(j + 8) = Y[1] * v12;
        if ( *(_DWORD *)(j + 20) == *(_DWORD *)(v22 + 64) )
          v8 = 0;
        else
          v8 = *(_DWORD *)(j + 20);
      }
    }
  }
}

