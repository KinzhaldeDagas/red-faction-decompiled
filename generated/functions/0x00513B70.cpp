// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00513B70 rf_plane_copy
// UNREALRED VERIFIED [combat-native-planes-20261104]: Copies three raw normal floats and the fourth scalar verbatim, returns destination. Copying an authored non-unit normal is intentional; normalizing XYZ without scaling scalar changes the plane. Static and moving geometry use the same geometry finalizer/copy contract.
float *__thiscall rf_plane_copy(float *this, float *source)
{
  float copy_result[3]; // [esp+4h] [ebp-Ch] BYREF

  rf_vector_copy(this, copy_result, source);
  *(this + 3) = source[3];
  return this;
}

