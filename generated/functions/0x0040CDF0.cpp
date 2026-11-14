// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040CDF0 rf_vector_copy
// UNREALRED VERIFIED [trigger-attachment-20261020] In attachment callers the destination common position is in ECX; source and caller result object are stack arguments. 504623 sets ECX=trigger+0x3C before this call. The temporary shown in decompiled call syntax is not the persistent destination. This routine writes three floats to its this pointer.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model152 binding/update/draw, temporal/visibility edges, transform ordering, ribbon bounds and vector-result ABI): Verified thiscall vector assignment with caller result object: ECX persistent destination,first stack float[3] copy-result,second const float[3] source,RET8,EAX=copy-result pointer. Sequentially copies source X/Y/Z into destination,THEN copies destination into caller result via40CE30. Result object is not the persistent destination and return is pointer,not integer. Exact alias is allowed by sequence; arbitrary partial overlap not guaranteed because copy is sequential rather than snapshot. No allocation/normalization/NULL checks. Corrected old integer result/first-output types while preserving source byte operations.
float *__thiscall rf_vector_copy(float *destination, float *copy_result, const float *source)
{
  *destination = *source;
  *(destination + 1) = source[1];
  *(destination + 2) = source[2];
  rf_vector3_copy_return_destination(copy_result, destination);
  return copy_result;
}

