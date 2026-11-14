// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004344D0 sub_4344D0
// UNREALRED VERIFIED [combat-panic-movement-20261111]: Native speed transaction. Entity+75C carried-body handle !=-1 forces request0. Class Flags bit800 is exact fighter. For fighter, first store Entity+8C = requested!=0 ? double(class Acceleration+5C)*Entity+98/double(class MaxVel+50) :3000. Physics scalar role is not named here. Then requested2 stores speedmode+8C4=2 and speed+8C0=float(double(MaxVel)*fastfactor+58); any other nonzero stores mode1 and SPMaxVel or any-nonzero MP9; zero stores mode0 and SPfloat(double(MaxVel)*slowfactor+54) or any-nonzero MP7. These stored speeds are raw RF distances/second, independent of animation presence. Preserve physics write before mode/speed and do not clamp source zero/negative numbers.
// UNREALRED VERIFIED [combat-native-pickup-dependencies-20261111]: This is ordinary current speed Entity+8C0 producer used by40AEB0. It is NOT only initialized in NanoShield special branch or assumed allocationzero. After carry override, zero request writes current mode0 and SP MaxVel*slowFactor or MP7; request2 mode2 MaxVel*fastFactor; other nonzero mode1 SP MaxVel or MP9. Native float stores at4345C4/E7/434617/640/657. Current movement owner may supply this operand only with its source/lifetime/phase proven.
float *__thiscall sub_4344D0(int this, int a2)
{
  float *result; // eax

  if ( *(_DWORD *)(this + 1884) != -1 )
    a2 = 0;
  if ( rf_entity_class_flags724_has_mask800(this) )
  {
    if ( a2 )
      *(float *)(this + 140) = *(float *)(*(_DWORD *)(this + 660) + 92)
                             * *(float *)(this + 152)
                             / (*(float *)(*(_DWORD *)(this + 660) + 80)
                              * 1.0);
    else
      *(float *)(this + 140) = 3000.0;
  }
  if ( a2 )
  {
    if ( a2 == 2 )
    {
      *(_DWORD *)(this + 2244) = 2;
      result = *(float **)(this + 660);
      *(float *)(this + 2240) = result[20] * result[22];
    }
    else
    {
      *(_DWORD *)(this + 2244) = 1;
      result = (float *)rf_multiplayer_runtime_mode;
      if ( rf_multiplayer_runtime_mode )
      {
        *(float *)(this + 2240) = flt_661314;
      }
      else
      {
        result = *(float **)(this + 660);
        *(float *)(this + 2240) = result[20];
      }
    }
  }
  else
  {
    result = (float *)this;
    *(_DWORD *)(this + 2244) = 0;
    if ( rf_multiplayer_runtime_mode )
    {
      *(float *)(this + 2240) = flt_661318;
    }
    else
    {
      result = *(float **)(this + 660);
      *(float *)(this + 2240) = result[20] * result[21];
    }
  }
  return result;
}

