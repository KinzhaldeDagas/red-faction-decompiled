// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00559200 rf_vector_normalize_reciprocal_sqrt
// UNREALRED VERIFIED [trigger-use-20261021] Reciprocal-sqrt normalization has no zero-length guard. At mutual Use target40DA80, coincident finite positions can yield NaN dot values whose x87 unordered branches admit. This is distinct from host SafeNormal returning zero.
// UNREALRED VERIFIED [combat-selected-drop-20261111]: 52F1B0 edge-normal producer uses this reciprocal-sqrt normalization, NOT559300. Formsfloat squaredsum, calls40CFF0->40D010 float-rounded sqrt, storesfloat reciprocal, thenfloat componentproducts. No zero/finite fallback; zero vector can becomeNaN. Keep this distinct from safe/unitX normalization used elsewhere.
float *__thiscall rf_vector_normalize_reciprocal_sqrt(float *this)
{
  float v2; // [esp+4h] [ebp-Ch]
  float v4; // [esp+Ch] [ebp-4h]

  v2 = *this * *this + *(this + 1) * *(this + 1) + *(this + 2) * *(this + 2);
  v4 = 1.0 / rf_sqrt_float(v2);
  *this = *this * v4;
  *(this + 1) = *(this + 1) * v4;
  *(this + 2) = *(this + 2) * v4;
  return this;
}

