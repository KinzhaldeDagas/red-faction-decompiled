// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C1190 rf_bolt_emitter_disable
// UNREALRED VERIFIED [world-uid-ownership]: Clears bolt-emitter enabled byte +0x58 and zeros the four per-bolt runtime values at +0x70 with stride 0x44.
float *__thiscall rf_bolt_emitter_disable(float *this)
{
  float *result; // eax
  int i; // [esp+4h] [ebp-4h]

  result = this;
  *((_BYTE *)this + 88) = 0;
  for ( i = 0; i < 4; ++i )
  {
    result = this;
    *(this + 17 * i + 28) = 0.0;
  }
  return result;
}

