// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00587C20 rf_matrix43_compose_parent_local
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Verified exact layout: four contiguous vector3 rows (rotation rows0..2,translation row3). For each row i and component j: out[3*i+j]=sum(k=0..2, this[3*i+k]*parent[3*k+j])+parent[9+j]*w[i], with constant w={0,0,0,1} at663F3C verified against PE. Computes all12 floats in local temporary before copying48 bytes to output, so output may alias either input. Returns output. Existing parent/local name retained; no quaternion normalization or hidden transpose.
float *__thiscall rf_matrix43_compose_parent_local(float *this, float *a2, float *a3)
{
  float v4; // [esp+8h] [ebp-44h]
  float v5; // [esp+Ch] [ebp-40h]
  float v6; // [esp+10h] [ebp-3Ch]
  int i; // [esp+18h] [ebp-34h]
  float v9[12]; // [esp+1Ch] [ebp-30h] BYREF

  rf_affine3x4_default_construct_noop(v9);
  for ( i = 0; i < 4; ++i )
  {
    v6 = *a3 * *(this + 3 * i) + a3[3] * *(this + 3 * i + 1) + a3[6] * *(this + 3 * i + 2) + a3[9] * flt_663F3C[i];
    v9[3 * i] = v6;
    v5 = a3[1] * *(this + 3 * i) + a3[4] * *(this + 3 * i + 1) + a3[7] * *(this + 3 * i + 2) + a3[10] * flt_663F3C[i];
    v9[3 * i + 1] = v5;
    v4 = a3[2] * *(this + 3 * i) + a3[5] * *(this + 3 * i + 1) + a3[8] * *(this + 3 * i + 2) + a3[11] * flt_663F3C[i];
    v9[3 * i + 2] = v4;
  }
  qmemcpy(a2, v9, 0x30u);
  return a2;
}

