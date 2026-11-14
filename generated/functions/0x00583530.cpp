// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00583530 rf_quaternion_s16_normalized_to_destination_integer_ratio
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Signed16 components sign-extended,squared and summed with32-bit IMUL/ADD wrap. Executes signed IDIV:quotient=268402689(16383^2)/sumSquares BEFORE float conversion,then sqrt(float(quotient));truncates scaled source components tointeger,stores low16bits via setter,returns output. Integer quantization intentional to annotation:positive sum>16383^2 gives quotient0 and zero output,not gradual floating rescale. Sum0 triggers processor divide error;overflowed signed sums can yield0/negative quotient. No saturation/finite guard. Original signed IDIV at583587 independently verified;do not rewrite as float division.
_WORD *__thiscall rf_quaternion_s16_normalized_to_destination_integer_ratio(__int16 *this, _WORD *a2)
{
  float v3; // [esp+0h] [ebp-20h]
  float v5; // [esp+1Ch] [ebp-4h]

  v3 = (float)(268402689
             / (*(this + 3) * *(this + 3) + *(this + 2) * *(this + 2) + *(this + 1) * *(this + 1) + *this * *this));
  v5 = rf_sqrt_float(v3);
  rf_short_quaternion_set_components(
    a2,
    (int)((double)*this * v5),
    (int)((double)*(this + 1) * v5),
    (int)((double)*(this + 2) * v5),
    (int)((double)*(this + 3) * v5));
  return a2;
}

