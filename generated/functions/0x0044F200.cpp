// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044F200 rf_hud_store_scalar66188C_divided_by255
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Cdecl one FLOAT32 argument, void. Load input, divide by original PE DOUBLE255.0, FSTP DWORD local (explicit FLOAT32 rounding),
// reload that FLOAT32 and store to global FLOAT66188C. Second store preserves already-rounded value; no incoming ST0 parameter or floating return. No clamp to0..1, byte/integer
// conversion, sign/finite/NaN check, alpha multiplication, timer or delegate. Negative/out-of-range/infinite/NaN inputs retain native arithmetic behavior under current FPU
// environment; global scalar updated unconditionally on normal completion.
void __cdecl rf_hud_store_scalar66188C_divided_by255(float a1)
{
  float v1; // [esp+0h] [ebp-4h]

  v1 = a1 / 255.0;
  flt_66188C = v1;
}

