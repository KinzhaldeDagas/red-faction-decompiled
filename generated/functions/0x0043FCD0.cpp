// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043FCD0 sub_43FCD0
// UNREALRED VERIFIED [indirect-source-20261029] Returns the fire record source handle at+0x34.421BA0 uses it for Entity+0x144C death-source metadata when damage type4 has supplied source -1 and an active fire record. This getter does not itself write multiplayer attacker credit.
int __cdecl sub_43FCD0(int a1)
{
  return *(_DWORD *)(a1 + 52);
}

