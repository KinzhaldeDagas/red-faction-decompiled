// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005503F0 rf_lightmap_build_face_corner_smoothed_normals
// UNREALRED VERIFIED [lightmap-pixels-20261028]: Arguments pointercollectionoffaces,outputallocatedarraypointer. Allocates12*facecountbytes,zerosarray; each12-byte entry becomes vectorarray foroneface. Allocationfailure returns0; successful returnfacecount. Perfacecorner starts with facenormalXYZ,walks allfaces incidentto cornerworldvertex collection+32,and adds anotherfacenormal only if distinct,currentneighborDWORD+60nonzero,and dotnormals>0. Averages byincludedcount,normalizes reciprocal-sqrt helper,appends3-floatnormal tothatfaceentry. Sharedvertex sharpedges withdot<=0excluded. No normal/index/capacity or innerallocationfailure guard. Caller must free eachvectorarray storage andouter mallocblock; facevertices not modified.
int __cdecl rf_lightmap_build_face_corner_smoothed_normals(_DWORD *a1, void **a2)
{
  int first_dword; // eax
  int result; // eax
  int v4; // eax
  int v5; // eax
  float v6[3]; // [esp-8h] [ebp-44h] BYREF
  float v7; // [esp+4h] [ebp-38h]
  _DWORD *v8; // [esp+8h] [ebp-34h]
  float v9; // [esp+10h] [ebp-2Ch]
  float *v10; // [esp+14h] [ebp-28h]
  int v11; // [esp+18h] [ebp-24h]
  int k; // [esp+1Ch] [ebp-20h]
  float v13[3]; // [esp+20h] [ebp-1Ch] BYREF
  _DWORD *v14; // [esp+2Ch] [ebp-10h]
  float *v15; // [esp+30h] [ebp-Ch]
  _DWORD *j; // [esp+34h] [ebp-8h]
  int i; // [esp+38h] [ebp-4h]

  first_dword = rf_receiver_get_first_dword(a1);
  *a2 = malloc(12 * first_dword);
  if ( !*a2 )
    return 0;
  v4 = rf_receiver_get_first_dword(a1);
  memset(*a2, 0, 12 * v4);
  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(a1);
    if ( i >= result )
      break;
    v15 = *(float **)sub_552200(a1, i);
    v14 = (char *)*a2 + 12 * i;
    for ( j = *((_DWORD **)v15 + 16); j; j = v8 )
    {
      rf_vector3_copy_return_destination(v13, v15);
      v11 = 1;
      for ( k = 0; ; ++k )
      {
        v5 = rf_receiver_get_first_dword((void *)(*j + 32));
        if ( k >= v5 )
          break;
        v10 = *(float **)sub_552200((_DWORD *)(*j + 32), k);
        if ( v10 != v15 && *((_DWORD *)v10 + 15) )
        {
          v9 = rf_vector_dot(v15, v10);
          if ( v9 > 0.0 )
          {
            rf_vector_accumulate(v13, v10);
            ++v11;
          }
        }
      }
      v7 = 1.0 / (double)v11;
      rf_vector3_scale_in_place_return_self(v13, v7);
      rf_vector_normalize_reciprocal_sqrt(v13);
      rf_vector3_copy_return_destination(v6, v13);
      rf_vector_array12_append_by_value(v14, v6[0], SLODWORD(v6[1]), SLODWORD(v6[2]));
      if ( j[5] == *((_DWORD *)v15 + 16) )
        v8 = nullptr;
      else
        v8 = (_DWORD *)j[5];
    }
  }
  return result;
}

