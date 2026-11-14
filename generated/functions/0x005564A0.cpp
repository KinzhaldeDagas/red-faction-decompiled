// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005564A0 rf_geomod_generated_uv_project
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): Mode663E50:1 no-op;2 only assigns face bitmap48 from663E54;3 builds orientation from plane normal, projects vertex minus plane point onto first basis and NEGATED second basis, writing primary corner U4/V8. Mode3 queries dimensions of OLD face bitmap before replacing bitmap with default663E54, a significant ordering quirk. Mode4 selects dominant projection axes, chooses default bitmap except dominantY uses663E58 for negative normalY or663E5C for nonnegative normalY if handle>=0, assigns bitmap BEFORE querying dimensions, then U/V=selected world components*(663E60/width,height). Dimension locals start16. Does not change secondary UV12/16; no texture bounds/size checks. Unrecognized modes leave face
// unchanged.
void __stdcall rf_geomod_generated_uv_project(int a1)
{
  const float *v1; // eax
  double v2; // st7
  float *v3; // eax
  double v4; // st7
  int v5; // [esp+0h] [ebp-8Ch]
  int v6; // [esp+4h] [ebp-88h]
  float v7[3]; // [esp+10h] [ebp-7Ch] BYREF
  _BYTE v8[12]; // [esp+1Ch] [ebp-70h] BYREF
  int v9; // [esp+28h] [ebp-64h] BYREF
  float v10; // [esp+2Ch] [ebp-60h]
  int v11; // [esp+30h] [ebp-5Ch] BYREF
  int v12; // [esp+34h] [ebp-58h] BYREF
  float v13; // [esp+38h] [ebp-54h]
  int v14; // [esp+3Ch] [ebp-50h] BYREF
  int v15; // [esp+40h] [ebp-4Ch]
  int v16; // [esp+44h] [ebp-48h] BYREF
  float out_vector[3]; // [esp+48h] [ebp-44h] BYREF
  float v18[3]; // [esp+54h] [ebp-38h] BYREF
  float v19[6]; // [esp+60h] [ebp-2Ch] BYREF
  float v20; // [esp+78h] [ebp-14h]
  float v21; // [esp+7Ch] [ebp-10h]
  int v22; // [esp+80h] [ebp-Ch] BYREF
  int v23; // [esp+84h] [ebp-8h] BYREF
  int i; // [esp+88h] [ebp-4h]

  if ( dword_663E50 != 1 )
  {
    switch ( dword_663E50 )
    {
      case 2:
        *(_DWORD *)(a1 + 48) = dword_663E54;
        break;
      case 3:
        rf_matrix3_construct((char *)v18);
        rf_orientation_matrix_from_direction(v18, a1);
        v23 = 16;
        v22 = 16;
        rf_bitmap_get_resolved_dimensions(*(_DWORD *)(a1 + 48), &v23, &v22);
        v21 = flt_663E60 / (double)v23;
        v20 = flt_663E60 / (double)v22;
        for ( i = *(_DWORD *)(a1 + 64); i; i = v6 )
        {
          v1 = (const float *)rf_plane_point_from_negative_offset_normal((float *)a1, (int)v8);
          rf_vector_subtract(*(const float **)i, out_vector, v1);
          v2 = rf_vector_dot(out_vector, v18);
          *(float *)(i + 4) = v2 * v21;
          v3 = rf_vector_negate(v19, v7);
          v4 = rf_vector_dot(out_vector, v3);
          *(float *)(i + 8) = v4 * v20;
          if ( *(_DWORD *)(i + 20) == *(_DWORD *)(a1 + 64) )
            v6 = 0;
          else
            v6 = *(_DWORD *)(i + 20);
        }
        *(_DWORD *)(a1 + 48) = dword_663E54;
        break;
      case 4:
        rf_face_projection_axes_select((float *)a1, &v11, &v12, &v9);
        v15 = dword_663E54;
        if ( v11 == 1 )
        {
          if ( *(float *)(a1 + 4) >= 0.0 )
          {
            if ( dword_663E5C > -1 )
              v15 = dword_663E5C;
          }
          else if ( dword_663E58 > -1 )
          {
            v15 = dword_663E58;
          }
        }
        *(_DWORD *)(a1 + 48) = v15;
        v16 = 16;
        v14 = 16;
        rf_bitmap_get_resolved_dimensions(*(_DWORD *)(a1 + 48), &v16, &v14);
        v13 = flt_663E60 / (double)v16;
        v10 = flt_663E60 / (double)v14;
        for ( i = *(_DWORD *)(a1 + 64); i; i = v5 )
        {
          *(float *)(i + 4) = *(float *)(*(_DWORD *)i + 4 * v12) * v13;
          *(float *)(i + 8) = *(float *)(*(_DWORD *)i + 4 * v9) * v10;
          if ( *(_DWORD *)(i + 20) == *(_DWORD *)(a1 + 64) )
            v5 = 0;
          else
            v5 = *(_DWORD *)(i + 20);
        }
        break;
    }
  }
}

