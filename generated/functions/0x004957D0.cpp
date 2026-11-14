// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004957D0 rf_player_state3740_assign
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Thiscall embedded player state (Player+228),source stack,RET4,returns receiver. First assigns3664-byte prefix495CD0;copies21
// BYTES3664..3684;DWORDs3688/3692/3696,FLOAT3700,DWORD3704;32 bytes3708..3739. Padding3685..3687 untouched. Does not construct/destroy receiver,normalize flags or copy pointer
// targets independently. Parent copy uses exact3740-byte span before next member3968.
int __thiscall rf_player_state3740_assign(int this, int a2)
{
  unsigned int i; // [esp+4h] [ebp-4h]

  rf_player_string_state3664_assign((char *)this, a2);
  *(_BYTE *)(this + 3664) = *(_BYTE *)(a2 + 3664);
  *(_BYTE *)(this + 3665) = *(_BYTE *)(a2 + 3665);
  *(_BYTE *)(this + 3666) = *(_BYTE *)(a2 + 3666);
  *(_BYTE *)(this + 3667) = *(_BYTE *)(a2 + 3667);
  *(_BYTE *)(this + 3668) = *(_BYTE *)(a2 + 3668);
  *(_BYTE *)(this + 3669) = *(_BYTE *)(a2 + 3669);
  *(_BYTE *)(this + 3670) = *(_BYTE *)(a2 + 3670);
  *(_BYTE *)(this + 3671) = *(_BYTE *)(a2 + 3671);
  *(_BYTE *)(this + 3672) = *(_BYTE *)(a2 + 3672);
  *(_BYTE *)(this + 3673) = *(_BYTE *)(a2 + 3673);
  *(_BYTE *)(this + 3674) = *(_BYTE *)(a2 + 3674);
  *(_BYTE *)(this + 3675) = *(_BYTE *)(a2 + 3675);
  *(_BYTE *)(this + 3676) = *(_BYTE *)(a2 + 3676);
  *(_BYTE *)(this + 3677) = *(_BYTE *)(a2 + 3677);
  *(_BYTE *)(this + 3678) = *(_BYTE *)(a2 + 3678);
  *(_BYTE *)(this + 3679) = *(_BYTE *)(a2 + 3679);
  *(_BYTE *)(this + 3680) = *(_BYTE *)(a2 + 3680);
  *(_BYTE *)(this + 3681) = *(_BYTE *)(a2 + 3681);
  *(_BYTE *)(this + 3682) = *(_BYTE *)(a2 + 3682);
  *(_BYTE *)(this + 3683) = *(_BYTE *)(a2 + 3683);
  *(_BYTE *)(this + 3684) = *(_BYTE *)(a2 + 3684);
  *(_DWORD *)(this + 3688) = *(_DWORD *)(a2 + 3688);
  *(_DWORD *)(this + 3692) = *(_DWORD *)(a2 + 3692);
  *(_DWORD *)(this + 3696) = *(_DWORD *)(a2 + 3696);
  *(float *)(this + 3700) = *(float *)(a2 + 3700);
  *(_DWORD *)(this + 3704) = *(_DWORD *)(a2 + 3704);
  for ( i = 0; i < 0x20; ++i )
    *(_BYTE *)(i + this + 3708) = *(_BYTE *)(i + a2 + 3708);
  return this;
}

