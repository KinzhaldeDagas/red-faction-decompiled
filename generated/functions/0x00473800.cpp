// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00473800 rf_item_pickup_maybe_resume_ai_combat
// UNREALRED VERIFIED [event-item-dispatch-20261028]: For entity AI type at+1312 equal4 or7 only, requires life+52 > definition(+660)+68 *0.95 and armor+56 > same definition+72 *0.95 (strict comparisons). Then arms timer+1244 at0ms and calls combat-transition helper0x40B2D0 on embedded AI+672. Triggered by item pickup dispatcher; does not itself grant health/armor.
// UNREALRED VERIFIED [combat-ammo-roles-pickups-20261111]: After successfulnonplayer itempickup only modes4/7 plus STRICTlife>classLife*.95 ANDarmor>classArmor*.95 armdeadlineEntity+4DCat0ms then40B2D0. Doesnotdirectlygranthealth/armor or universallyresumeAI; sourceclass maxima/AIstate/deadline owner are required.
// UNREALRED VERIFIED [combat-native-pickup-dependencies-20261111]: Recovery strict threshold is double bits at6310A8=000000606666ee3f, exactly double(0.95f)=0.949999988079071. ClassMaximumLife/Armor inputs are raw class+44/+48, not clamped host UI maxima. Products are compared without an intervening binary32 store. Both predicates strict >, unordered reject. Reached prefix arms actual AI+23C timer0ms then calls40B2D0; a missing later provider does not undo committed pickup or timer.
void __cdecl rf_item_pickup_maybe_resume_ai_combat(int a1)
{
  int v1; // [esp+0h] [ebp-8h]

  v1 = *(_DWORD *)(a1 + 1312);
  if ( (v1 == 4 || v1 == 7)
    && *(float *)(a1 + 52) > *(float *)(*(_DWORD *)(a1 + 660) + 68) * 0.949999988079071
    && *(float *)(a1 + 56) > *(float *)(*(_DWORD *)(a1 + 660) + 72) * 0.949999988079071 )
  {
    rf_replicator_arm_milliseconds((int *)(a1 + 1244), 0);
    sub_40B2D0((int *)(a1 + 672));
  }
}

