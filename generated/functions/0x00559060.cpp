// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00559060 rf_vector3_negated_copy
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): ECX source plus destination, RET4. Stages negative XYZ then writes all three through component setter and returns output. Exact source/output alias is safe; no normalization or magnitude change.
float *__thiscall rf_vector3_negated_copy(float *this, float *a2)
{
  float v3; // [esp+0h] [ebp-10h]
  float v4; // [esp+4h] [ebp-Ch]
  float v5; // [esp+8h] [ebp-8h]

  v5 = -*(this + 2);
  v4 = -*(this + 1);
  v3 = -*this;
  rf_vector3_set_components_return_destination(a2, v3, v4, v5);
  return a2;
}

