// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00441340 rf_foley_registry_choose_sound_by_index
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI/corpse-carry/inventory/projectile update chains, original field layouts and float constants and native
// signed/x87/stack/callback ABI): One signed cdecl registry index. Rejects index<0 OR index>=signed DWORD6E6728 with EAX=-1. Otherwise loads Foley set DWORD6E6748+56*index and
// returns directly the result of choose-random-sound(set); no own set-null/count guard or resource load here. Used by40C650 with entity class DWORD+1780; registry record stride is56,
// not the entity/weapon record stride.
int __cdecl rf_foley_registry_choose_sound_by_index(int a1)
{
  if ( a1 >= 0 && a1 < unk_6E6728 )
    return rf_foley_choose_random_sound(unk_6E6748[14 * a1]);
  else
    return -1;
}

