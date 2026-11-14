// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00558F90 rf_vector3_normalized_copy_or_unit_x
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): ECX source plus destination, RET4. Computes float length; ordered length>0 writes source/length, otherwise writes(1,0,0), including zero or unordered NaN length. Does not reject infinite length separately. Returns output; all components staged before stores permit exact source/output alias.
float *__thiscall rf_vector3_normalized_copy_or_unit_x(float *this, float *a2)
{
  float v3; // [esp+Ch] [ebp-1Ch]
  float v4; // [esp+10h] [ebp-18h]
  float v5; // [esp+14h] [ebp-14h]
  float v6; // [esp+18h] [ebp-10h]
  float v8; // [esp+20h] [ebp-8h]
  float v9; // [esp+24h] [ebp-4h]

  v6 = *this * *this + *(this + 1) * *(this + 1) + *(this + 2) * *(this + 2);
  v9 = rf_sqrt_float(v6);
  if ( v9 > 0.0 )
  {
    v8 = 1.0 / v9;
    v5 = *(this + 2) * v8;
    v4 = *(this + 1) * v8;
    v3 = *this * v8;
    rf_vector3_set_components_return_destination(a2, v3, v4, v5);
  }
  else
  {
    rf_vector3_set_components_return_destination(a2, 1.0, 0.0, 0.0);
  }
  return a2;
}

