// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005546D0 rf_solid_scale_selected_vertices_about_centroid
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): If selected vertex count204 nonzero, sums all selected XYZ and divides by positive count, then overwrites each selected vertex as mean+scale*(old-mean). Does not finalize incident faces, regenerate UVs, or update bounds/spatial indices. Repeated pointer selections affect average and can scale same vertex repeatedly. Return is incidental loop/count/vector pointer.
void __thiscall rf_solid_scale_selected_vertices_about_centroid(void *this, float scalar)
{
  float **v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float v7; // [esp+8h] [ebp-68h]
  float v9[3]; // [esp+10h] [ebp-60h] BYREF
  float sum_result[3]; // [esp+1Ch] [ebp-54h] BYREF
  float scaled_result[3]; // [esp+28h] [ebp-48h] BYREF
  float out_vector[3]; // [esp+34h] [ebp-3Ch] BYREF
  float copy_result[3]; // [esp+40h] [ebp-30h] BYREF
  float v14[3]; // [esp+4Ch] [ebp-24h] BYREF
  float *lhs; // [esp+58h] [ebp-18h]
  int first_dword; // [esp+5Ch] [ebp-14h]
  int i; // [esp+60h] [ebp-10h]
  float rhs[3]; // [esp+64h] [ebp-Ch] BYREF

  first_dword = rf_receiver_get_first_dword((char *)this + 204);
  if ( first_dword )
  {
    rf_vector3_default_construct_noop(rhs);
    rf_vector3_zero_return_destination(rhs);
    for ( i = 0; i < first_dword; ++i )
    {
      v2 = (float **)sub_552200((_DWORD *)this + 51, i);
      rf_vector_accumulate(rhs, *v2);
    }
    if ( first_dword > 0 )
    {
      v7 = (float)i;
      v3 = rf_vector_divide(rhs, v14, v7);
      rf_vector_copy(rhs, copy_result, v3);
    }
    for ( i = 0; i < first_dword; ++i )
    {
      lhs = *(float **)sub_552200((_DWORD *)this + 51, i);
      v4 = rf_vector_subtract(lhs, out_vector, rhs);
      v5 = rf_vector_multiply_scalar(v4, scaled_result, scalar);
      v6 = rf_vector_add(v5, sum_result, rhs);
      rf_vector_copy(lhs, v9, v6);
    }
  }
}

