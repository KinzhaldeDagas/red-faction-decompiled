// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004024E0 sub_4024E0
// UNREALRED VERIFIED [combat-native-directed-ai-20261111] Facing predicate uses normalized candidateCommon3C-ownerCommon3C dotted with Entity7F8, row2 of native view matrixbase7E0, compared against Entity840. Authored RFL fullint FOV produces cos(angle*binary32pi/180/2) at481B13; runtime405C60 also writes840. Neither ActorForward nor generic cone clamps silently represent this retained native operand.
// UNREALRED VERIFIED [combat-native-view-fov-20261112]: Input direction is candidate common3C minus owner common3C, each result storedfloat;559200 reciprocal-sqrt normalization has no zero/finite guard.40D110 dot uses RAW owner7F8 row, with final floatstore402516. x87 threshold840<=dot branch tests AH41 and ACCEPTS UNORDERED, so coincident/NaN operands are not SafeNormal/false. Recovering this arithmetic does not prove a host ActorForward provider equals retained native7E0.
bool __cdecl sub_4024E0(int a1, int a2)
{
  float out_vector[3]; // [esp+0h] [ebp-10h] BYREF
  float v4; // [esp+Ch] [ebp-4h]

  rf_vector_subtract((const float *)(a2 + 60), out_vector, (const float *)(a1 + 60));
  rf_vector_normalize_reciprocal_sqrt(out_vector);
  v4 = rf_vector_dot((float *)(a1 + 2040), out_vector);
  return *(float *)(a1 + 2112) <= (double)v4;
}

