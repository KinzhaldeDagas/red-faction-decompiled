// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A4850 rf_integer_factorial_iterative
// UNREALRED VERIFIED [character-pipeline-20261029]: Signed integer n. Starts accumulator1,multiplies by integers1..n in32-bit signed arithmetic,returns accumulator. n<=0 returns1; no negative-domain rejection or overflow handling (13! exceeds signed32 range). Used by general Bernstein coefficient calculation.
int __cdecl rf_integer_factorial_iterative(int a1)
{
  int v2; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  v2 = 1;
  for ( i = 1; i <= a1; ++i )
    v2 *= i;
  return v2;
}

