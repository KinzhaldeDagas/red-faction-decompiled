// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00507D50 rf_rail_trail_reset_pool16
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weapon contact/decal control flow,ammo registry,rail trail pool,constructor layout and native argument/return ABI,original ECX/stack flow and PE bytes): Clears free head91170C and active head911708; links EXACT16 static records stride80 at911710 into free circular doubly-linked ring through next+72/previous+76. First node self-links and stays head; each following node appended before head, giving next order0..15. No payload/age/UID/vector clearing, allocation, texture load or active-resource teardown. Returns EAX0. XOR followed by JNZ scaffolding is never taken.
int rf_rail_trail_reset_pool16()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  unk_91170C = 0;
  result = 0;
  unk_911708 = 0;
  for ( i = 0; i < 16; ++i )
  {
    if ( unk_91170C )
    {
      unk_91175C[20 * i] = *(_DWORD *)(unk_91170C + 76);
      unk_911758[20 * i] = unk_91170C;
      *(_DWORD *)(*(_DWORD *)(unk_91170C + 76) + 72) = (char *)&unk_911710 + 80 * i;
      *(_DWORD *)(unk_91170C + 76) = (char *)&unk_911710 + 80 * i;
    }
    else
    {
      unk_911758[20 * i] = (int)&unk_911710 + 80 * i;
      unk_91175C[20 * i] = (int)&unk_911710 + 80 * i;
      unk_91170C = (char *)&unk_911710 + 80 * i;
    }
    result = 0;
  }
  return result;
}

