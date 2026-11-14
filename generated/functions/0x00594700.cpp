// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00594700 rf_random_seed_and_discard_two
// UNREALRED VERIFIED [system-progress-20261028]: Unsigned seed. Value0xFFFFFFFF uses low32 of0x594740(NULL) time64; otherwise passes seed to srand. Calls rand three times and returns THIRD result, discarding first two. Mutates global CRT PRNG state; no per-object generator or cryptographic behavior.
// UNREALRED VERIFIED [combat-native-pickup-runtime-20261111]: Engine4F1440 passes FFFFFFFF at4F15BD/call4F15BF. Sentinel resolves to LOW32 of594740 time64(NULL); srand then THREE rand draws (third returned, caller ignores). Non-sentinel seed passes directly. Never reseed per actor, pickup, resource-cache or level. Host GameInstance startup mapping must be reported separately.
int __cdecl rf_random_seed_and_discard_two(unsigned int Seed)
{
  unsigned int v1; // eax

  if ( Seed == -1 )
  {
    v1 = rf_system_time64_forward(nullptr);
    srand(v1);
  }
  else
  {
    srand(Seed);
  }
  rand();
  rand();
  return rand();
}

