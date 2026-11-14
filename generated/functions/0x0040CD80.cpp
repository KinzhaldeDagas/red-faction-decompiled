// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040CD80 rf_ai_pause_updates_and_stop_entity_firing
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI/corpse-carry/inventory/projectile update chains, original field layouts and float constants and native
// signed/x87/stack/callback ABI): No arguments. Iterates complete entity intrusive list from68211C to sentinel681E90 following next+652 AFTER callbacks. For every entity stops
// firing(handle+44,selected weapon+676), then zeroes THREE floats vector+336 only. Does not zero linear velocity+324 or other pose/state fields. Writes global BYTE6663D1=1 AFTER
// traversal;403DE0 skips only exact1. EAX is incidental last zero-helper result/list head on empty list. No player/death/inactive/authority filtering.
float *rf_ai_pause_updates_and_stop_entity_firing()
{
  float *result; // eax
  int i; // [esp+0h] [ebp-4h]

  result = (float *)unk_68211C;
  for ( i = unk_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
  {
    rf_entity_stop_weapon_firing(*(_DWORD *)(i + 44), *(_DWORD *)(i + 676));
    result = rf_vector3_zero_return_destination((float *)(i + 336));
  }
  byte_6663D1 = 1;
  return result;
}

