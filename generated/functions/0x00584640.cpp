// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00584640 rf_quaternion_s16_relative_unit_log
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Recovered packed counterpart:conjugate A,integer-ratio normalization583530,Hamilton fixed-point product with B,unit-log583650,copy to output,return output. Thus inherits signed32 squared-sum overflow,IDIV-zero and integer-quotient normalization loss,plus16-bit wrap/truncation. No exponentiation or additional float normalization;local temporaries before final output.
__int16 *__cdecl rf_quaternion_s16_relative_unit_log(__int16 *a1, const __int16 *a2, const __int16 *a3)
{
  __int16 *v3; // eax
  _WORD *v4; // eax
  _WORD v6[4]; // [esp+0h] [ebp-20h] BYREF
  _WORD v7[4]; // [esp+8h] [ebp-18h] BYREF
  __int16 v8[4]; // [esp+10h] [ebp-10h] BYREF
  __int16 v9[4]; // [esp+18h] [ebp-8h] BYREF

  rf_quaternion_s16_conjugate_to_destination((__int16 *)a2, v8);
  rf_quaternion_s16_normalized_to_destination_integer_ratio(v8, v9);
  v3 = rf_quaternion_s16_hamilton_product_to_destination(v9, v7, (__int16 *)a3);
  v4 = rf_quaternion_s16_unit_log_to_destination(v3, v6);
  rf_short_quaternion_copy_words_return_this(v8, v4);
  rf_short_quaternion_assign_words_return_this(a1, v8);
  return a1;
}

