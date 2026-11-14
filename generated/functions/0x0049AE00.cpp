// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049AE00 rf_replication_apply_entity_powerup_bits
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native packet19 registry/codec, x87 quantization, powerup linked nodes, entity state masks and action
// arbitration): Cdecl(entity,inBYTE). Find player by entity common handle44; only if found form prior bits from Entity DWORD2068 masks20000,40000,80000 ->bits1,2,4. If no player,
// prior bits assumed0 even when entity flags already set. For each differing desired low3 bit, call corresponding setter/clearer
// (20000:43C610/43C660,40000:43C680/43C6D0,80000:43C6F0/43C710). Set20000/40000 delegates also play native sounds;80000 is direct bit mutation. No membership-list creation/removal,
// input-byte overwrite, runtime/authority guard or NULL entity/input guard. High5 input bits ignored. Return EAX residue, not common success flag. Missing player+desired0 does NOT
// clear pre-existing flags because prior is0.
int __cdecl rf_replication_apply_entity_powerup_bits(int a1, _BYTE *a2)
{
  int result; // eax
  unsigned __int8 v3; // [esp+3h] [ebp-5h]
  _DWORD *v4; // [esp+4h] [ebp-4h]

  v3 = 0;
  v4 = sub_4DD720(*(_DWORD *)(a1 + 44));
  if ( v4 )
  {
    v3 = (*(_DWORD *)(a1 + 2068) & 0x20000) != 0;
    if ( (*(_DWORD *)(a1 + 2068) & 0x40000) != 0 )
      v3 |= 2u;
  }
  if ( v4 && (*(_DWORD *)(a1 + 2068) & 0x80000) != 0 )
    v3 |= 4u;
  if ( ((*a2 ^ v3) & 1) != 0 )
  {
    if ( (*a2 & 1) != 0 )
      rf_entity_set_state814_mask20000_with_sound84(a1);
    else
      rf_entity_clear_state814_mask20000(a1);
  }
  if ( ((*a2 ^ v3) & 2) != 0 )
  {
    if ( (*a2 & 2) != 0 )
      rf_entity_set_state814_mask40000_with_sound86(a1);
    else
      rf_entity_clear_state814_mask40000(a1);
  }
  result = (unsigned __int8)*a2;
  if ( (((unsigned __int8)result ^ v3) & 4) != 0 )
  {
    if ( (*a2 & 4) != 0 )
      return rf_entity_set_state814_mask80000(a1);
    else
      return rf_entity_clear_state814_mask80000(a1);
  }
  return result;
}

