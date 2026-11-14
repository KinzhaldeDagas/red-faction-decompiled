// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057AF30 rf_cstring_format_bracketed_matrix3_unbounded
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Cdecl destination, UNUSED second integer/capacity-like argument, nine consecutive floats, precision. Unbounded sprintf into516-byte local buffer with layout LF TAB [ < x,y,z > LF TAB two-spaces < next3 > LF TAB two-spaces < last3 > SPACE ], using comma-space separators and precision for all nine %.*f conversions. Copies resulting text including NUL into caller destination with no capacity guard. EAX copy cursor is one byte after NUL before cookie helper. No transpose or normalization.
char *__cdecl rf_cstring_format_bracketed_matrix3_unbounded(
        char *out_text,
        int unused_capacity,
        const float *matrix,
        int precision)
{
  char *result; // eax
  char v5; // [esp+6Bh] [ebp-215h]
  char *v7; // [esp+74h] [ebp-20Ch]
  char Buffer[516]; // [esp+78h] [ebp-208h] BYREF

  sprintf(
    Buffer,
    "\n\t[ < %.*f, %.*f, %.*f >\n\t  < %.*f, %.*f, %.*f >\n\t  < %.*f, %.*f, %.*f > ]",
    precision,
    *matrix,
    precision,
    matrix[1],
    precision,
    matrix[2],
    precision,
    matrix[3],
    precision,
    matrix[4],
    precision,
    matrix[5],
    precision,
    matrix[6],
    precision,
    matrix[7],
    precision,
    matrix[8]);
  v7 = Buffer;
  do
  {
    v5 = *v7;
    *out_text = *v7++;
    result = ++out_text;
  }
  while ( v5 );
  return result;
}

