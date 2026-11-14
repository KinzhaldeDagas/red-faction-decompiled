// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00539580 rf_vector2_subtract_to_output
// UNREALRED VERIFIED [lightmap-shadows-20261028]: Thispointer isfirstXYvector; stackarguments outputXY,secondXY. Computes first-second into localcomponents beforewritingoutput,so aliasing eitherinput is supported. Returns outputpointer. Exactly twofloatcomponents; no allocation.
float *__thiscall rf_vector2_subtract_to_output(float *this, float *a2, float *a3)
{
  float v4; // [esp+8h] [ebp-Ch]
  float v5; // [esp+Ch] [ebp-8h]

  v5 = *(this + 1) - a3[1];
  v4 = *this - *a3;
  rf_vector2_assign_components(a2, v4, v5);
  return a2;
}

