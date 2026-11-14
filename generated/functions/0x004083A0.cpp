// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004083A0 rf_ai_select_secondary2_with_timing
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One required AI block. Class Flags724 mask0x800 predicate EXACT AL1 arms block+564 inclusive300..500ms then
// secondary2. Otherwise block DWORD+1184==2 AND humanoid EXACT1 arms+1272 inclusive1000..2000 and+564 inclusive3000..5000, then secondary2. Remaining branch consumes rand()%2000,
// adds base3000 ONLY if DWORD+1308==EXACT1 else2000, arms+564, then+1188 at500ms. Primary-flag20-without-secondary predicate EXACT1 calls40A2A0 and exits. Other AL writes secondary2,
// then any-nonzero humanoid and deadline+1276 elapsed EXACT1 admits toggle: any nonzero DWORD+1308 ->write0, arm+1276 inclusive3000..4000. If priorDWORD+1308==0,449550() EAX EXACT0
// OR1 ->write+1308=1 and separately arm+1276,+1272,+564 each1500ms. Other EAX values leave toggle0 and expired+1276 untouched. Lookup449550 maps difficulty0..3 to itself and every
// other raw difficulty to0, so invalid difficulty can still reach the1500ms branch. No own owner dead/inactive, role, target or route admission; does not run secondary2 handler
// immediately. Timers are wrapped game milliseconds; return EAX/AL incidental despite stored unsigned prototype.
void __cdecl rf_ai_select_secondary2_with_timing(int *a1)
{
  int v1; // [esp+4h] [ebp-8h]
  int v2; // [esp+8h] [ebp-4h]

  if ( rf_entity_class_flags724_has_mask800(*a1) )
  {
    rf_timestamp_arm_random_inclusive_milliseconds(a1 + 141, 300, 500);
    rf_ai_secondary_state_write((int)a1, 2);
  }
  else if ( a1[296] == 2 && rf_entity_has_humanoid_flag(*a1) )
  {
    rf_timestamp_arm_random_inclusive_milliseconds(a1 + 318, 1000, 2000);
    rf_timestamp_arm_random_inclusive_milliseconds(a1 + 141, 3000, 5000);
    rf_ai_secondary_state_write((int)a1, 2);
  }
  else
  {
    v2 = rand() % 2000;
    v1 = 2000;
    if ( a1[327] == 1 )
      v1 = 3000;
    rf_replicator_arm_milliseconds(a1 + 141, v2 + v1);
    rf_replicator_arm_milliseconds(a1 + 297, 500);
    if ( rf_ai_primary_flag20_without_secondary((int)a1) )
    {
      sub_40A2A0(a1);
    }
    else
    {
      rf_ai_secondary_state_write((int)a1, 2);
      if ( rf_entity_has_humanoid_flag(*a1) && rf_replicator_has_elapsed(a1 + 319) )
      {
        if ( a1[327] )
        {
          a1[327] = 0;
          rf_timestamp_arm_random_inclusive_milliseconds(a1 + 319, 3000, 4000);
        }
        else if ( (unsigned int)rf_ai_difficulty_get_with_zero_fallback() <= 1 )
        {
          a1[327] = 1;
          rf_replicator_arm_milliseconds(a1 + 319, 1500);
          rf_replicator_arm_milliseconds(a1 + 318, 1500);
          rf_replicator_arm_milliseconds(a1 + 141, 1500);
        }
      }
    }
  }
}

