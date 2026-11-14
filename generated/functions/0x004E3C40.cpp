// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E3C40 rf_cockpit_digit_frame_offset
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): Cdecl(signed value,F32 multiplier), returns signed integer frame offset. Negative value immediately returns1. Otherwise x87 integer value*F32 multiplier +stored DOUBLE epsilon6316F8, round F32 before floor_float, FTOL conversion, SIGNED remainder10 +1. Used with .001/.01/.1/1 decimal positions; not a decimal-string conversion. No clamp for negative/nonfinite multiplier or conversion overflow; negative multiplier can produce offsets outside1..10. All actual digit callers use positive finite multipliers.
int __cdecl rf_cockpit_digit_frame_offset(int a1, float a2)
{
  float value; // [esp+4h] [ebp-8h]

  if ( a1 < 0 )
    return 1;
  value = (double)a1 * a2 + 0.00009999999747378752;
  return (int)rf_floor_float(value) % 10 + 1;
}

