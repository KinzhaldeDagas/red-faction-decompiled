// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566E80 rf_byte_maximum_unsigned
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): cdecl two BYTE values promoted into stack words. Returns unsigned max(a,b); equality returns second same byte. No multiply, division, interpolation or saturation arithmetic. Used to FLOOR each computed vertex RGB channel at material-derived threshold in566470.
unsigned __int8 __cdecl rf_byte_maximum_unsigned(unsigned __int8 a1, unsigned __int8 a2)
{
  if ( a1 <= (int)a2 )
    return a2;
  else
    return a1;
}

