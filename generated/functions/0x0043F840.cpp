// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043F840 sub_43F840
// UNREALRED VERIFIED [burn-motion-20261029]: Fade age strictly>12 disables the three flame emitters; strictly>17 removes the owner. On shared elapsed225ms ticks, age>5 decrements smoke alpha byte and removes on zero; remaining fields decay by their decoded 0.95/0.90/0.75 factors. Therefore12/17 seconds measure fading after rebind, not a live burning entity lifetime.
// UNREALRED VERIFIED [combat-native-followup-20261104]: Fade mutation uses runtime emitter radius min/max+68/+72, delay min/max+48/+52 and velocity min/max+36/+40. Shared elapsed tick: flame radius/delay*=.95, velocity*=.90; smoke radius/velocity*=.75, delay unchanged; voice gain*=.95. After age>5 decrement START alpha byte smoke+135 with byte semantics and remove only when decremented value==0. This is not a continuous alpha fade or a live ignition timeout.
// UNREALRED VERIFIED [combat-burn-owner-20261104]: Fade age advances after smoke/flame/spread/audio. Strict >12 disables flames and transitions common flags only if any flame remains enabled; strict >17 releases. Shared pulse after age>5 decrements smoke START alpha byte with uint8 wrap, freeing when result==0. Flame min/max radius+68/+72 and delay+48/+52 *=.95, speed+36/+40 *=.90; smoke radius/speed *=.75, delay unchanged; voice gain*=.95. Do not clamp alpha or fade continuously.
char __cdecl sub_43F840(float *a1)
{
  int v1; // eax
  char result; // al
  int v3; // [esp+0h] [ebp-Ch]
  int v4; // [esp+4h] [ebp-8h]

  if ( a1[12] > 12.0
    && (*(_BYTE *)(*(_DWORD *)a1 + 320) || *(_BYTE *)(*((_DWORD *)a1 + 1) + 320)
                                        || *(_BYTE *)(*((_DWORD *)a1 + 2) + 320)) )
  {
    rf_particle_emitter_disable(*(_BYTE **)a1);
    rf_particle_emitter_disable(*((_BYTE **)a1 + 1));
    rf_particle_emitter_disable(*((_BYTE **)a1 + 2));
    v1 = rf_corpse_resolve_handle_type7(*((_DWORD *)a1 + 4));
    *(_DWORD *)(v1 + 668) &= ~0x200u;
    *(_DWORD *)(v1 + 668) |= 0x100u;
  }
  if ( a1[12] > 17.0 )
  {
    v4 = rf_entity_resolve_handle(*((_DWORD *)a1 + 4));
    if ( v4 )
      sub_40A2A0((int *)(v4 + 672));
    return (unsigned __int8)rf_burn_effect_release_record(a1, 0);
  }
  result = rf_replicator_has_elapsed(&unk_6E6710);
  if ( result )
  {
    if ( a1[12] > 5.0 && !--*(_BYTE *)(*((_DWORD *)a1 + 3) + 135) )
    {
      v3 = rf_entity_resolve_handle(*((_DWORD *)a1 + 4));
      if ( v3 )
        sub_40A2A0((int *)(v3 + 672));
      return (unsigned __int8)rf_burn_effect_release_record(a1, 0);
    }
    *(float *)(*(_DWORD *)a1 + 68) = *(float *)(*(_DWORD *)a1 + 68) * 0.949999988079071;
    *(float *)(*((_DWORD *)a1 + 1) + 68) = *(float *)(*((_DWORD *)a1 + 1) + 68) * 0.949999988079071;
    *(float *)(*((_DWORD *)a1 + 2) + 68) = *(float *)(*((_DWORD *)a1 + 2) + 68) * 0.949999988079071;
    *(float *)(*((_DWORD *)a1 + 3) + 68) = *(float *)(*((_DWORD *)a1 + 3) + 68) * 0.75;
    *(float *)(*(_DWORD *)a1 + 72) = *(float *)(*(_DWORD *)a1 + 72) * 0.949999988079071;
    *(float *)(*((_DWORD *)a1 + 1) + 72) = *(float *)(*((_DWORD *)a1 + 1) + 72) * 0.949999988079071;
    *(float *)(*((_DWORD *)a1 + 2) + 72) = *(float *)(*((_DWORD *)a1 + 2) + 72) * 0.949999988079071;
    *(float *)(*((_DWORD *)a1 + 3) + 72) = *(float *)(*((_DWORD *)a1 + 3) + 72) * 0.75;
    *(float *)(*(_DWORD *)a1 + 48) = *(float *)(*(_DWORD *)a1 + 48) * 0.949999988079071;
    *(float *)(*((_DWORD *)a1 + 1) + 48) = *(float *)(*((_DWORD *)a1 + 1) + 48) * 0.949999988079071;
    *(float *)(*((_DWORD *)a1 + 2) + 48) = *(float *)(*((_DWORD *)a1 + 2) + 48) * 0.949999988079071;
    *(float *)(*(_DWORD *)a1 + 52) = *(float *)(*(_DWORD *)a1 + 52) * 0.949999988079071;
    *(float *)(*((_DWORD *)a1 + 1) + 52) = *(float *)(*((_DWORD *)a1 + 1) + 52) * 0.949999988079071;
    *(float *)(*((_DWORD *)a1 + 2) + 52) = *(float *)(*((_DWORD *)a1 + 2) + 52) * 0.949999988079071;
    *(float *)(*(_DWORD *)a1 + 36) = *(float *)(*(_DWORD *)a1 + 36) * 0.8999999761581421;
    *(float *)(*((_DWORD *)a1 + 1) + 36) = *(float *)(*((_DWORD *)a1 + 1) + 36) * 0.8999999761581421;
    *(float *)(*((_DWORD *)a1 + 2) + 36) = *(float *)(*((_DWORD *)a1 + 2) + 36) * 0.8999999761581421;
    *(float *)(*((_DWORD *)a1 + 3) + 36) = *(float *)(*((_DWORD *)a1 + 3) + 36) * 0.75;
    *(float *)(*(_DWORD *)a1 + 40) = *(float *)(*(_DWORD *)a1 + 40) * 0.8999999761581421;
    *(float *)(*((_DWORD *)a1 + 1) + 40) = *(float *)(*((_DWORD *)a1 + 1) + 40) * 0.8999999761581421;
    *(float *)(*((_DWORD *)a1 + 2) + 40) = *(float *)(*((_DWORD *)a1 + 2) + 40) * 0.8999999761581421;
    *(float *)(*((_DWORD *)a1 + 3) + 40) = *(float *)(*((_DWORD *)a1 + 3) + 40) * 0.75;
    a1[10] = a1[10] * 0.949999988079071;
    return (char)a1;
  }
  return result;
}

