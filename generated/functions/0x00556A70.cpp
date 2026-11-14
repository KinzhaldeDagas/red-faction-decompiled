// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556A70 rf_solid_project_selected_uvs_between_coordinate_frames
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): ECX solid plus(matrixA,translationA,translationB,matrixB), RET16. For each selected face216 with bitmap48!=-1, copies each corner position, rotates/translates by A, then subtracts translationB and inverse rotates by matrixB. Writes primary U=localX*scale/bitmapWidth and V=localY*scale/bitmapHeight, querying bitmap dimensions for EVERY corner with initial16. Positions and secondary UV unchanged. No normal alignment, clamping, size/pointer checks or projection-mode gate.
void __thiscall rf_solid_project_selected_uvs_between_coordinate_frames(
        void *this,
        const float *a2,
        const float *a3,
        const float *a4,
        const float *a5)
{
  int first_dword; // eax
  int v6; // [esp+0h] [ebp-30h]
  float v8; // [esp+8h] [ebp-28h]
  float v9[3]; // [esp+Ch] [ebp-24h] BYREF
  float v10; // [esp+18h] [ebp-18h]
  int v11; // [esp+1Ch] [ebp-14h] BYREF
  int v12; // [esp+20h] [ebp-10h] BYREF
  int v13; // [esp+24h] [ebp-Ch]
  int j; // [esp+28h] [ebp-8h]
  int i; // [esp+2Ch] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((char *)this + 216);
    if ( i >= first_dword )
      break;
    v13 = *(_DWORD *)sub_552200((_DWORD *)this + 54, i);
    if ( *(_DWORD *)(v13 + 48) != -1 )
    {
      for ( j = *(_DWORD *)(v13 + 64); j; j = v6 )
      {
        rf_vector3_copy_return_destination(v9, *(float **)j);
        rf_vector_rotate_translate_in_place(v9, (int)a2, (int)a3);
        rf_vector_inverse_translate_rotate_in_place(v9, (int)a4, (int)a5);
        v12 = 16;
        v11 = 16;
        rf_bitmap_get_resolved_dimensions(*(_DWORD *)(v13 + 48), &v12, &v11);
        v10 = flt_663E60 / (double)v12;
        v8 = flt_663E60 / (double)v11;
        *(float *)(j + 4) = v9[0] * v10;
        *(float *)(j + 8) = v9[1] * v8;
        if ( *(_DWORD *)(j + 20) == *(_DWORD *)(v13 + 64) )
          v6 = 0;
        else
          v6 = *(_DWORD *)(j + 20);
      }
    }
  }
}

