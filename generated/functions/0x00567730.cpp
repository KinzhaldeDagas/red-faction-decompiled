// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567730 sub_567730
// UNREALRED VERIFIED [combat-particle-range-20261104]: Native unit sample is float(rand())/32768.0, not /32767. Rand605ADC updates per-thread CRT state by state*214013+2531011 and returns(state>>16)&0x7FFF. Therefore samples range0..32767/32768. This evidence does not establish UnrealFRandomStream sequence parity.
double sub_567730()
{
  float v1; // [esp+4h] [ebp-8h]

  v1 = (float)rand();
  return (float)(v1 / 32768.0);
}

