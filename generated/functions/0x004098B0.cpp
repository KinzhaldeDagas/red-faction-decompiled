// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004098B0 rf_ai_resolve_maximum_attack_range
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): Corrected return ABI: cdecl one AI-block pointer, floating result in ST0, previously falsely stored void. If selected-weapon predicate40B6D0
// is AL0, stationary-class predicate40D380(owner)==EXACT1, and first-associated child handle435170(owner) resolves as entity, recursively returns4098B0(child+672). No cycle/depth
// guard. Otherwise calls attack-range resolver(block,0), rounds SECONDARY result to float32 in reserved stack slot, then resolver(block,1), rounds PRIMARY result to float32 in next
// slot; invokes40D600 with stack(first=primary,second=secondary). Returns secondary when secondary>=primary OR UNORDERED, else primary. Thus order and NaN choice matter; no added100
// minimum here. Native caller40477A stores returnedST0 over consumed block argument then calls maximum(result,100), proving nonvoid x87 result and separate caller-side100 floor. No
// incoming x87 operand, direct ammo/ownership mutation or duration conversion.
double __cdecl rf_ai_resolve_maximum_attack_range(int *a1)
{
  float v2; // [esp+0h] [ebp-10h]
  float v3; // [esp+4h] [ebp-Ch]
  int v4; // [esp+8h] [ebp-8h]
  int v5; // [esp+Ch] [ebp-4h]

  if ( !sub_40B6D0(a1) && sub_40D380(*a1) )
  {
    v4 = sub_435170(*a1);
    v5 = rf_entity_resolve_handle(v4);
    if ( v5 )
      return rf_ai_resolve_maximum_attack_range((int *)(v5 + 672));
  }
  v3 = rf_ai_resolve_attack_range((int)a1, 0);
  v2 = rf_ai_resolve_attack_range((int)a1, 1);
  return rf_float_maximum_two_values(v2, v3);
}

