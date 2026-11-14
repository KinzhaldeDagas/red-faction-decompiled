// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055EAC0 rf_affine3x4_transform_point
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This float[12] affine,args destination float3,source float3. Computes all three temporary components:out[r]=source.x*M[r]+source.y*M[r+3]+source.z*M[r+6]+M[r+9],r0..2;then copies to destination. Source/destination in-place safe due temporary. Returns destination;no homogeneous divide,normalization,perspective or matrix validity checks.
// [UnrealRed physical spheres 2026-11-12; verified original-byte ASM55EAD9..55EAFD/55EB2D/55EB5D] CSPH affine center transform stores each result component ONLY AFTER summing three row products AND corresponding translation component. There is no intervening binary32 store between rotated dot and translation. Host port must use one float store of sum3products+position, not rounded rotatedXYZ followed by vector addition. Binary64 host products/sums remain an explicit arithmetic adapter to x87 extended precision.
float *__thiscall rf_affine3x4_transform_point(float *this, float *a2, float *a3)
{
  float v5[3]; // [esp+4h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(v5);
  v5[0] = *a3 * *this + a3[1] * *(this + 3) + a3[2] * *(this + 6) + *(this + 9);
  v5[1] = *a3 * *(this + 1) + a3[1] * *(this + 4) + a3[2] * *(this + 7) + *(this + 10);
  v5[2] = *a3 * *(this + 2) + a3[1] * *(this + 5) + a3[2] * *(this + 8) + *(this + 11);
  rf_vector3_copy_return_destination(a2, v5);
  return a2;
}

