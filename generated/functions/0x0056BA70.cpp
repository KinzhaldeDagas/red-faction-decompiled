// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056BA70 sub_56BA70
// UNREALRED VERIFIED [finite-pair-parallel-20261028] Builds normalized plane-intersection direction only when max(float(cross.x*cross.x),float(cross.y*cross.y),float(cross.z*cross.z)) strictly exceeds double(float(1e-8)) at0x6408F8 (branches0x56BB50/0x56BBDE/0x56BC54). Component squares are stored as floats before the threshold comparison. A below/equal-threshold near-parallel pair returns false; caller0x52BEFD exits at0x52BF10 before finite intersection records. Endpoint/expanded-bound overlap cannot override this native scheduling guard.
char __cdecl sub_56BA70(float *a1, float *a2, float *a3)
{
  float *v3; // eax
  float v5; // [esp+10h] [ebp-44h]
  float v6; // [esp+14h] [ebp-40h]
  float v7; // [esp+18h] [ebp-3Ch]
  float v8; // [esp+1Ch] [ebp-38h]
  float v9; // [esp+20h] [ebp-34h]
  float v10; // [esp+24h] [ebp-30h]
  float v11; // [esp+28h] [ebp-2Ch]
  float copy_result[3]; // [esp+2Ch] [ebp-28h] BYREF
  float v13[3]; // [esp+38h] [ebp-1Ch] BYREF
  float v14; // [esp+44h] [ebp-10h]
  int v15; // [esp+50h] [ebp-4h]

  if ( (dword_180922C & 1) == 0 )
  {
    dword_180922C |= 1u;
    rf_vector3_default_construct_noop(&flt_1809220);
    v15 = -1;
  }
  v3 = rf_vector_cross(a1, v13, a2);
  rf_vector_copy(a3 + 3, copy_result, v3);
  flt_1809220 = a3[3] * a3[3];
  unk_1809224 = a3[4] * a3[4];
  unk_1809228 = a3[5] * a3[5];
  if ( unk_1809224 >= (double)unk_1809228
    || flt_1809220 >= (double)unk_1809228
    || unk_1809228 <= 0.00000000999999993922529 )
  {
    if ( flt_1809220 >= (double)unk_1809224 || unk_1809224 <= 0.00000000999999993922529 )
    {
      if ( flt_1809220 <= 0.00000000999999993922529 )
        return 0;
      v14 = 1.0 / a3[3];
      v7 = a2[1] * a1[3] - a1[1] * a2[3];
      v6 = a1[2] * a2[3] - a2[2] * a1[3];
      rf_vector3_set_components_thiscall(a3, 0.0, v6, v7);
    }
    else
    {
      v14 = 1.0 / a3[4];
      v9 = *a1 * a2[3] - *a2 * a1[3];
      v8 = a2[2] * a1[3] - a1[2] * a2[3];
      rf_vector3_set_components_thiscall(a3, v8, 0.0, v9);
    }
  }
  else
  {
    v14 = 1.0 / a3[5];
    v11 = *a2 * a1[3] - *a1 * a2[3];
    v10 = a1[1] * a2[3] - a2[1] * a1[3];
    rf_vector3_set_components_thiscall(a3, v10, v11, 0.0);
  }
  rf_vector3_scale_in_place_return_self(a3, v14);
  v5 = flt_1809220 + unk_1809224 + unk_1809228;
  v14 = 1.0 / rf_sqrt_float(v5);
  rf_vector3_scale_in_place_return_self(a3 + 3, v14);
  return 1;
}

