// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040CF10 rf_vector_subtract
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, SFXO/CHNE model wire layout, signed vertex unpacking, vector-return ABI, shared pools and key/geometry conversions): Verified thiscall ABI: ECX const left vector, first stack argument output float[3], second const right vector, RET8; returns OUTPUT POINTER EAX, not integer. Computes each left-minus-right component with explicit32-bit float stores before calling three-component setter on output. All three differences evaluated before output write, allowing output alias with either input. Does not mutate inputs except via alias, normalize, allocate or return scalar length. Corrected old int return/output-integer inference; typed output is needed to understand CHNE radius locals. Several decompiler dummy ECX values around subsequent float argument-stack reservations are unused temporary artifacts, not radius input
// pointers.
float *__thiscall rf_vector_subtract(const float *lhs, float *out_vector, const float *rhs)
{
  float v4; // [esp+Ch] [ebp-10h]
  float v5; // [esp+10h] [ebp-Ch]
  float v6; // [esp+14h] [ebp-8h]

  v6 = *(lhs + 2) - rhs[2];
  v5 = *(lhs + 1) - rhs[1];
  v4 = *lhs - *rhs;
  rf_vector3_set_components_return_destination(out_vector, v4, v5, v6);
  return out_vector;
}

