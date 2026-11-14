// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00401470 sub_401470
// UNREALRED VERIFIED [combat-fire-exhaustion-20260930] Requires weapon ownership and a nonnegative weapon ammo index. Raw operands use that ammo index for BOTH inventory+0x0C and inventory+0x8C counts; either signed count>0 admits. Do not silently substitute candidate weapon-indexed loaded ammo for the second access. This differs from total-ammo helper 0x436310 and requires exact representation when implementing the selector.
bool __cdecl sub_401470(int a1, unsigned int a2)
{
  int v4; // [esp+4h] [ebp-4h]

  if ( !sub_403D00(a1, a2) )
    return 0;
  v4 = dword_912024[340 * a2];
  if ( v4 < 0 )
    return 0;
  return *(int *)(a1 + 4 * v4 + 12) > 0 || *(int *)(a1 + 4 * v4 + 140) > 0;
}

