// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00609681 __difftime64
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(two signed64 epoch values),double result x87
// ST0. Reject either negative ->errno22,return+0.0, no invalid callback. Otherwise subtract second fromfirst in64bits and FILD signed64 result; no max-year check or timezone
// conversion. Difference may negative; subtraction of two nonnegative signed64 values cannot exceed signed range. No output pointer, allocation, doserrno or errno reset on success.
double __cdecl _difftime64(__time64_t Time1, __time64_t Time2)
{
  if ( Time2 >= 0 && Time1 >= 0 )
    return (double)(Time1 - Time2);
  *_errno() = 22;
  return 0.0;
}

