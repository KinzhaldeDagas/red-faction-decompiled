// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055E420 rf_affine3x4_multiply_second_by_first
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This destination float[12],args A float[12],B float[12]. For each column i0..3 and row r0..2,temp[3*i+r]=B[r]*A[3*i]+B[3+r]*A[3*i+1]+B[6+r]*A[3*i+2]+B[9+r]*h[i],with original verified h table0x663E80=(0,0,0,1). Then copies48-byte temp to destination;safe when destination aliasesA/B. In column-vector convention computes B*A,including B.rotation*A.translation+B.translation. No normalization,perspective or singularity checks. Return incidental integer4 after loop,not a matrix pointer.
void *__thiscall rf_affine3x4_multiply_second_by_first(float *this, int a2, float *a3)
{
  void *result; // eax
  float v4; // [esp+8h] [ebp-44h]
  float v5; // [esp+Ch] [ebp-40h]
  float v6; // [esp+10h] [ebp-3Ch]
  int i; // [esp+18h] [ebp-34h]
  float v9[12]; // [esp+1Ch] [ebp-30h] BYREF

  result = rf_affine3x4_default_construct_noop(v9);
  for ( i = 0; i < 4; ++i )
  {
    v6 = *a3 * *(float *)(a2 + 12 * i)
       + a3[3] * *(float *)(a2 + 12 * i + 4)
       + a3[6] * *(float *)(a2 + 12 * i + 8)
       + a3[9] * flt_663E80[i];
    v9[3 * i] = v6;
    v5 = a3[1] * *(float *)(a2 + 12 * i)
       + a3[4] * *(float *)(a2 + 12 * i + 4)
       + a3[7] * *(float *)(a2 + 12 * i + 8)
       + a3[10] * flt_663E80[i];
    v9[3 * i + 1] = v5;
    v4 = a3[2] * *(float *)(a2 + 12 * i)
       + a3[5] * *(float *)(a2 + 12 * i + 4)
       + a3[8] * *(float *)(a2 + 12 * i + 8)
       + a3[11] * flt_663E80[i];
    v9[3 * i + 2] = v4;
    result = (void *)(i + 1);
  }
  qmemcpy(this, v9, 0x30u);
  return result;
}

