// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060ACFC __isnan
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(double rawBits), int Boolean. INTEGER-only
// IEEE binary64 NaN test, no x87/MXCSR operation, payload mutation or errno. Load DWORD starting stack argument BYTE+6 (reads2 bytes BEYOND8-byte argument, but high16 discarded by
// mask7FF8). If masked topWORD==7FF8 ->1 (quiet NaN). If masked==7FF0 AND highDWORD mask7FFFF or lowDWORD nonzero ->1 (signaling NaN). Otherwise0, including both infinities, finite
// values, signed zeros and subnormals. Sign bit ignored. Does not quiet signaling NaN or consult FP exception masks; extra2 read bytes do not affect result.
int __cdecl _isnan(double X)
{
  return (HIWORD(X) & 0x7FF8) == 0x7FF0 && ((HIDWORD(X) & 0x7FFFF) != 0 || LODWORD(X)) || (HIWORD(X) & 0x7FF8) == 0x7FF8;
}

