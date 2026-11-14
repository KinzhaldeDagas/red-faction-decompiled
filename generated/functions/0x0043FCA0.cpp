// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043FCA0 rf_record_float48_divide12_or_one
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl(nullable record pointer), floating ST0 return. NULL yields exact1.0. NonNULL loads FLOAT+48, divides by
// original DOUBLE12.0, explicitly FSTP DWORD/FLD DWORD local, returning FLOAT32-rounded quotient despite double prototype. No clamp, finite/sign/zero-field test, time conversion or
// record mutation; NaN/infinity propagate through native division/environment. Does not dereference NULL or validate nonNULL record type/extent.
double __cdecl rf_record_float48_divide12_or_one(int a1)
{
  if ( !a1 )
    return 1.0;
  return (float)(*(float *)(a1 + 48) / 12.0);
}

