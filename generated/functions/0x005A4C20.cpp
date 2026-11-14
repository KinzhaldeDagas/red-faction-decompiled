// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A4C20 rf_catmull_rom32_construct_points
// UNREALRED VERIFIED [character-pipeline-20261029]: Thiscall object. Runs32 vector default constructors at stride12 over first384 bytes,returns this. Does NOT initialize count DWORD+384 or explicitly zero point components; no allocation or endpoint extrapolation.
char *__thiscall rf_catmull_rom32_construct_points(char *this)
{
  rf_vector_construct_no_unwind(this, 0xCu, 32, rf_vector3_default_construct_noop);
  return this;
}

