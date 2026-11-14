// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605ACA _srand
// UNREALRED VERIFIED [combat-native-pickup-runtime-20261111]: CRT srand stores supplied uint32 seed at threadData+20 returned by60E343. Shared per-thread state, no per-actor/per-weapon generator. Host session ownership is an explicit adaptation; Unreal FMath/FRandomStream is not this algorithm.
void __cdecl srand(unsigned int Seed)
{
  _getptd()[5] = Seed;
}

