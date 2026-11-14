// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055FEA0 rf_string_to_float_atof_or_zero
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): If buffer4NULL returns floating0, otherwise calls atof on buffer and rounds double result to FLOAT then returns viaST0 as saved double. Stored extent is ignored. Inherits atof whitespace/prefix/locale parsing; no success/end-pointer check or explicit finite/range clamp.
double __thiscall rf_string_to_float_atof_or_zero(const void *this)
{
  if ( !*((_DWORD *)this + 1) )
    return 0.0;
  return (float)atof((const char *)*((_DWORD *)this + 1));
}

