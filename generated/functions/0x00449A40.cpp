// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00449A40 rf_vector3_add_scalar_to_components
// UNREALRED VERIFIED [decal-projection-20261028]: Writes output=(this.x+s,this.y+s,this.z+s) through0x40CF70 and returns output. Captures input components before assignment; no normalization or allocation.
float *__thiscall rf_vector3_add_scalar_to_components(float *this, float *a2, float a3)
{
  float v4; // [esp+Ch] [ebp-10h]
  float v5; // [esp+10h] [ebp-Ch]
  float v6; // [esp+14h] [ebp-8h]

  v6 = *(this + 2) + a3;
  v5 = *(this + 1) + a3;
  v4 = *this + a3;
  rf_vector3_set_components_return_destination(a2, v4, v5, v6);
  return a2;
}

