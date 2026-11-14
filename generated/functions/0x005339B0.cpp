// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005339B0 sub_5339B0
// UNREALRED VERIFIED [finite-split-20261028] Emits 24-byte finite intersection records at workspace 0xD4B928: shared/current vertex pointer +0, crossing edge other endpoint +4 (zero for existing coplanar vertex), xyz +8/+0xC/+0x10, line scalar +0x14. Records include already-coplanar vertices and strict side-changing edges. Common capacity 128. 0x52BEE0 allocates/propagates crossing vertices before division, sorts scalar records and deduplicates shared VERTEX POINTER identity.
int __thiscall sub_5339B0(_DWORD *this, _DWORD *a2, _DWORD *a3, float *a4, float *rhs, _DWORD *a6, int a7, int a8)
{
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *v14; // eax
  void *v16; // [esp+Ch] [ebp-170h]
  int v17; // [esp+14h] [ebp-168h]
  float v19[3]; // [esp+1Ch] [ebp-160h] BYREF
  float v20[3]; // [esp+28h] [ebp-154h] BYREF
  float v21[3]; // [esp+34h] [ebp-148h] BYREF
  float v22[3]; // [esp+40h] [ebp-13Ch] BYREF
  float v23[3]; // [esp+4Ch] [ebp-130h] BYREF
  float v24[3]; // [esp+58h] [ebp-124h] BYREF
  float v25[3]; // [esp+64h] [ebp-118h] BYREF
  float scaled_result[3]; // [esp+70h] [ebp-10Ch] BYREF
  float v27[3]; // [esp+7Ch] [ebp-100h] BYREF
  float v28[3]; // [esp+88h] [ebp-F4h] BYREF
  float v29[3]; // [esp+94h] [ebp-E8h] BYREF
  float out_vector[3]; // [esp+A0h] [ebp-DCh] BYREF
  float copy_result[3]; // [esp+ACh] [ebp-D0h] BYREF
  float v32; // [esp+B8h] [ebp-C4h]
  float v33; // [esp+BCh] [ebp-C0h]
  float v34; // [esp+C0h] [ebp-BCh]
  char v35; // [esp+C7h] [ebp-B5h]
  float v36; // [esp+C8h] [ebp-B4h]
  float v37; // [esp+CCh] [ebp-B0h]
  int v38; // [esp+D0h] [ebp-ACh]
  float v39; // [esp+D4h] [ebp-A8h]
  float scalar; // [esp+D8h] [ebp-A4h]
  float v41; // [esp+DCh] [ebp-A0h]
  float destination[3]; // [esp+E0h] [ebp-9Ch] BYREF
  float vector[3]; // [esp+ECh] [ebp-90h] BYREF
  int v44; // [esp+F8h] [ebp-84h]
  float v45; // [esp+FCh] [ebp-80h]
  int v46; // [esp+100h] [ebp-7Ch]
  float v47[3]; // [esp+104h] [ebp-78h] BYREF
  float v48; // [esp+110h] [ebp-6Ch]
  float *v49; // [esp+114h] [ebp-68h] BYREF
  float *v50; // [esp+118h] [ebp-64h]
  float lhs[3]; // [esp+11Ch] [ebp-60h] BYREF
  float v52; // [esp+128h] [ebp-54h]
  _BYTE v53[12]; // [esp+12Ch] [ebp-50h] BYREF
  float *v54; // [esp+138h] [ebp-44h]
  float *source; // [esp+13Ch] [ebp-40h]
  _BYTE v56[12]; // [esp+140h] [ebp-3Ch] BYREF
  _BYTE v57[12]; // [esp+14Ch] [ebp-30h] BYREF
  int v58; // [esp+158h] [ebp-24h]
  int v59; // [esp+15Ch] [ebp-20h]
  int i; // [esp+160h] [ebp-1Ch]
  int v61; // [esp+164h] [ebp-18h]
  int v62; // [esp+168h] [ebp-14h]
  int v63; // [esp+16Ch] [ebp-10h]
  char v64; // [esp+173h] [ebp-9h]
  int v65; // [esp+174h] [ebp-8h]
  char v66; // [esp+17Bh] [ebp-1h]

  v65 = 0;
  v59 = 0;
  v63 = 0;
  v62 = 0;
  v66 = 0;
  v64 = 0;
  *a3 = -1;
  *a2 = -1;
  i = *(this + 16);
  v58 = rf_geomod_point_classify_against_face_plane(*(const float **)i, a4);
  for ( i = *(this + 16); i; i = v17 )
  {
    rf_vector3_default_construct_noop(v56);
    rf_vector3_default_construct_noop(v57);
    rf_vector3_default_construct_noop(v53);
    source = *(float **)i;
    v54 = **(float ***)(i + 20);
    v61 = rf_geomod_point_classify_against_face_plane(v54, a4);
    switch ( v58 )
    {
      case 1:
        ++v59;
        break;
      case 2:
        ++v63;
        break;
      case 3:
        ++v65;
        break;
    }
    ++v62;
    if ( v58 == 2 || rf_geomod_plane_classes_differ_excluding_coplanar(v58, v61) )
    {
      rf_geomod_intersection24_construct_noop((char *)&v49);
      if ( v58 == 2 )
      {
        v49 = source;
        v50 = nullptr;
        rf_vector_copy(lhs, copy_result, source);
        v8 = rf_vector_subtract(lhs, out_vector, rhs);
        v52 = rf_vector_dot(v8, rhs + 3);
      }
      else
      {
        v44 = 0;
        v46 = 2;
        rf_vector3_default_construct_noop(v47);
        while ( 1 )
        {
          rf_force_sample44_construct_vectors_noop((char *)destination);
          rf_vector_copy(destination, v29, source);
          v9 = rf_vector_subtract(v54, v28, source);
          rf_vector_copy(vector, v27, v9);
          v48 = rf_vector_dot(vector, a4);
          v45 = rf_vector_dot(destination, a4) + a4[3];
          scalar = v45 / v48;
          v10 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
          v11 = rf_vector_subtract(destination, v25, v10);
          rf_vector_copy(v47, v24, v11);
          v41 = rf_vector_dot(v47, a4) + a4[3];
          if ( v41 >= -0.00009999999747378752 && v41 <= 0.00009999999747378752 )
            break;
          v39 = -1.0;
          v34 = 0.0;
          v36 = rf_geomod_line_minus_parameter_plane_residual(-1.0, destination, (int)a4);
          v37 = rf_geomod_line_minus_parameter_plane_residual(v34, destination, (int)a4);
          v33 = scalar;
          v38 = 0;
          v35 = 0;
          while ( v38 < 64 )
          {
            ++v38;
            v32 = rf_geomod_line_minus_parameter_plane_residual(v33, destination, (int)a4);
            if ( v32 >= -0.00009999999747378752 && v32 <= 0.00009999999747378752 )
            {
              v12 = rf_vector_multiply_scalar(vector, v23, v33);
              v13 = rf_vector_subtract(destination, v22, v12);
              rf_vector_copy(v47, v21, v13);
              v41 = v32;
              scalar = v33;
              v35 = 1;
              break;
            }
            if ( v36 * v32 >= 0.0 )
            {
              if ( v32 * v37 < 0.0 )
              {
                v39 = v33;
                v36 = v32;
              }
            }
            else
            {
              v34 = v33;
              v37 = v32;
            }
            v33 = (v39 + v34) * 0.5;
          }
          if ( v35 )
            break;
          ++v44;
          v46 += 64;
          if ( v44 > 3 )
            goto LABEL_43;
        }
        v49 = source;
        v50 = v54;
        rf_vector_copy(lhs, v20, v47);
        v14 = rf_vector_subtract(lhs, v19, rhs);
        v52 = rf_vector_dot(v14, rhs + 3);
      }
      if ( !v66 || *(float *)(a8 + 24 * *a2 + 20) > (double)v52 )
      {
        v66 = 1;
        *a2 = *a6;
      }
      if ( !v64 || *(float *)(a8 + 24 * *a3 + 20) < (double)v52 )
      {
        v64 = 1;
        *a3 = *a6;
      }
      if ( *a6 < a7 )
      {
        v16 = (void *)(a8 + 24 * (*a6)++);
        sub_536030(v16, (int)&v49);
      }
    }
LABEL_43:
    v58 = v61;
    if ( *(_DWORD *)(i + 20) == *(this + 16) )
      v17 = 0;
    else
      v17 = *(_DWORD *)(i + 20);
  }
  if ( v63 == v62 )
    return 0;
  if ( v59 == v62 || v65 == v62 )
    return 1;
  if ( v59 && v65 )
    return 3;
  return 2;
}

