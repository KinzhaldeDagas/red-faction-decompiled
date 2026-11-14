// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CD960 rf_particle_emitter_choose_alternate_duration
// UNREALRED VERIFIED [vfx-particle-lifecycle] Samples the current on or off base time plus or minus its variance and clamps the selected duration to at least 0.1 seconds.
void __thiscall rf_particle_emitter_choose_alternate_duration(int this)
{
  double v1; // [esp+0h] [ebp-24h]
  double v2; // [esp+8h] [ebp-1Ch]
  double v3; // [esp+10h] [ebp-14h]
  double v4; // [esp+18h] [ebp-Ch]

  if ( *(_BYTE *)(this + 320) )
  {
    v4 = *(float *)(this + 296) - *(float *)(this + 300);
    v3 = *(float *)(this + 300) * 2.0;
    *(float *)(this + 312) = sub_567730() * v3 + v4;
  }
  else
  {
    v2 = *(float *)(this + 304) - *(float *)(this + 308);
    v1 = *(float *)(this + 308) * 2.0;
    *(float *)(this + 312) = sub_567730() * v1 + v2;
  }
  if ( *(float *)(this + 312) < 0.1000000014901161 )
    *(float *)(this + 312) = 0.1;
}

