// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041C860 rf_vector_subtract_in_place
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, glare visibility/reflection and cached-query initialization, native flags/x87 gates and static ownership): Thiscall destination plus one three-float source pointer, RET4. Sequential x87 load/subtract/store for X,Y,Z, each rounded to binary32 before next component. Returns original receiver bits. Exact source==destination subtracts each value from itself (finite components zero; nonfinite follows x87); partial overlap follows native component order. No temporaries copying whole source, allocation or null/finite validation.
float *__thiscall rf_vector_subtract_in_place(float *this, float *a2)
{
  *this = *this - *a2;
  *(this + 1) = *(this + 1) - a2[1];
  *(this + 2) = *(this + 2) - a2[2];
  return this;
}

