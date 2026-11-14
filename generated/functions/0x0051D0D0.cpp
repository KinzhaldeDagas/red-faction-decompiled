// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051D0D0 rf_solid_triangulate_face_fan_from_corner
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): Corrected saved STDCALL ABI to THISCALL solidECX,face,startCorner,selectDerived byte (RET12). If faceNULL or corner count<=3,no action. Otherwise allocates n-2 new face links using source flags/context,uses supplied startCorner or source head,appends each triangle(anchor,current,next) with ALL FOUR source UV floats preserved. Finalizes/attaches each through51D300 with source face and selectDerived. Removes/destroys original unconditionally after finalize loop,even if derived face finalization rejected/deleted individual triangles. Does not test convexity,triangulation quality or allocation failures;no rollback. Not a face destructor or scalar cdecl3-argument function.
void __thiscall rf_solid_triangulate_face_fan_from_corner(void *this, void *a2, void *a3, unsigned __int8 a4)
{
  _DWORD **v4; // eax
  _DWORD **v5; // eax
  _DWORD **v6; // eax
  int *v7; // eax
  int v8; // [esp-4h] [ebp-54h]
  int v9; // [esp-4h] [ebp-54h]
  int v10; // [esp-4h] [ebp-54h]
  float v11; // [esp+0h] [ebp-50h]
  float v12; // [esp+0h] [ebp-50h]
  float v13; // [esp+0h] [ebp-50h]
  float v14; // [esp+4h] [ebp-4Ch]
  float v15; // [esp+4h] [ebp-4Ch]
  float v16; // [esp+4h] [ebp-4Ch]
  float v17; // [esp+8h] [ebp-48h]
  float v18; // [esp+8h] [ebp-48h]
  float v19; // [esp+8h] [ebp-48h]
  float v20; // [esp+Ch] [ebp-44h]
  float v21; // [esp+Ch] [ebp-44h]
  float v22; // [esp+Ch] [ebp-44h]
  void *v24[3]; // [esp+18h] [ebp-38h] BYREF
  int v25; // [esp+24h] [ebp-2Ch]
  int v26; // [esp+28h] [ebp-28h]
  unsigned int *link; // [esp+2Ch] [ebp-24h]
  char v28[12]; // [esp+30h] [ebp-20h] BYREF
  int i; // [esp+3Ch] [ebp-14h]
  int v30; // [esp+40h] [ebp-10h]
  int v31; // [esp+4Ch] [ebp-4h]

  if ( a2 )
  {
    v26 = rf_geomod_face_corner_count(a2);
    if ( v26 > 3 )
    {
      rf_dword_array_construct_capacity(v24, 0);
      v31 = 0;
      v25 = v26 - 2;
      for ( i = 0; i < v25; ++i )
      {
        link = rf_solid_face_allocate_link(this, (const unsigned int *)a2 + 10);
        rf_pointer_array_append_dword(v24, (int)link);
      }
      if ( !a3 )
        a3 = *((void **)a2 + 16);
      v30 = *((_DWORD *)a3 + 5);
      for ( i = 0; i < v25; ++i )
      {
        v20 = *((float *)a3 + 4);
        v17 = *((float *)a3 + 3);
        v14 = *((float *)a3 + 2);
        v11 = *((float *)a3 + 1);
        v8 = *(_DWORD *)a3;
        v4 = (_DWORD **)sub_552200(v24, i);
        rf_geomod_face_corner_append(*v4, v8, v11, v14, v17, v20);
        v21 = *(float *)(v30 + 16);
        v18 = *(float *)(v30 + 12);
        v15 = *(float *)(v30 + 8);
        v12 = *(float *)(v30 + 4);
        v9 = *(_DWORD *)v30;
        v5 = (_DWORD **)sub_552200(v24, i);
        rf_geomod_face_corner_append(*v5, v9, v12, v15, v18, v21);
        v30 = *(_DWORD *)(v30 + 20);
        v22 = *(float *)(v30 + 16);
        v19 = *(float *)(v30 + 12);
        v16 = *(float *)(v30 + 8);
        v13 = *(float *)(v30 + 4);
        v10 = *(_DWORD *)v30;
        v6 = (_DWORD **)sub_552200(v24, i);
        rf_geomod_face_corner_append(*v6, v10, v13, v16, v19, v22);
      }
      for ( i = 0; i < v25; ++i )
      {
        v7 = (int *)sub_552200(v24, i);
        rf_solid_finalize_derived_face_attach_and_select(this, *v7, (int)a2, a4);
      }
      rf_dword_array_construct_capacity(v28, 0);
      LOBYTE(v31) = 1;
      rf_solid_face_remove_destroy((int *)this, a2, 0);
      LOBYTE(v31) = 0;
      rf_pointer_array_destroy_backing_storage((void **)v28);
      v31 = -1;
      rf_pointer_array_destroy_backing_storage(v24);
    }
  }
}

