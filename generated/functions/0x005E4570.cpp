// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4570 rf_fmod_float_via_x87_intrinsic
// UNREALRED VERIFIED [texture-upload-20261028]: Loadstwofloatarguments,calls__CIfmod,storesresult32-bitfloatandreloadsST0. Returnsfloat-roundedfloatingremainder,notEuclideanhypotenuse. No zero-divisororfiniteguard.
double __cdecl rf_fmod_float_via_x87_intrinsic(float a1, float a2)
{
  return (float)fmod(a1, a2);
}

