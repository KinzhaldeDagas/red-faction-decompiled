// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00510670 rf_weapon_spawn_impact_vclips
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile lifetime and attachments,weapon selectors,near-miss unordered branches,model and animation caches,original ECX/stack flow and PE bytes): Unchecked weapon index. Loops signed record impact count+1104; each i calls506E20(record handles+1108[i],a2,a3,a4,F32 radii+1144[i],a6,a5,1). Last two supplied arguments are reordered a6 before a5; final literal1. No count cap/index validation or failure aggregation. EAX is loop residue, not a reliable success result; zero/nonpositive count does not initialize it.
int __cdecl rf_weapon_spawn_impact_vclips(int a1, void *a2, float *a3, float *a4, float *a5, int a6)
{
  int result; // eax
  int i; // [esp+10h] [ebp-4h]

  for ( i = 0; i < unk_912450[340 * a1]; ++i )
  {
    rf_vclip_spawn_runtime_effect(
      unk_912454[340 * a1 + i],
      a2,
      a3,
      a4,
      COERCE_FLOAT_(*((float *)&unk_912478 + 340 * a1 + i)),
      a6,
      a5,
      1);
    result = i + 1;
  }
  return result;
}

