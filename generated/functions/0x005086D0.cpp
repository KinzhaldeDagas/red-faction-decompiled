// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005086D0 rf_weapon_apply_multiplayer_runtime_values
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weapon contact/decal control flow,ammo registry,rail trail pool,constructor layout and native argument/return ABI,original ECX/stack flow and PE bytes): Calls4AEFE0 (this binary constant-return-zero stub), stores EAX into runtime difficulty6612A4, then signed i0..<global911C68, stride1360 at912000. Exact source->runtime offsets: DWORD604->608 maxammo, F321296->1300 AIrange, DWORD132->136 clip, F32220->224 spread,232->236 altspread,244->248 AIspread,256->260 AIaltspread,284->288 AI damage scale,528->520 damage radius,184->176 lifetime,196->192 velocity. Copies through x87 F32 loads/stores for floats; no fixed64 cap, finite/range checks, derived product+204 refresh, allocation or parser cursor use. Uses multiplayer source slots regardless runtime-mode flag. EAX is loop residue (positive count) or getter0 if skipped, not
// success.
// UNREALRED VERIFIED [original-ai-difficulty-profile-20261112]: MP weapon profile postprocess first calls4AEFE0 (literal-zero stub in this executable) and stores EAX0 into ACTIVE6612A4; it does not overwrite CONFIGURED6612A8. This is separate from host-authored LAN bot skill/progression.
int rf_weapon_apply_multiplayer_runtime_values()
{
  int result; // eax
  char *v1; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  result = rf_splitscreen_query_zero_stub();
  dword_6612A4 = result;
  for ( i = 0; i < dword_911C68; ++i )
  {
    v1 = (char *)&rf_weapon_records + 1360 * i;
    *((_DWORD *)v1 + 152) = *((_DWORD *)v1 + 151);
    *((float *)v1 + 325) = *((float *)v1 + 324);
    *((_DWORD *)v1 + 34) = *((_DWORD *)v1 + 33);
    *((float *)v1 + 56) = *((float *)v1 + 55);
    *((float *)v1 + 59) = *((float *)v1 + 58);
    *((float *)v1 + 62) = *((float *)v1 + 61);
    *((float *)v1 + 65) = *((float *)v1 + 64);
    *((float *)v1 + 72) = *((float *)v1 + 71);
    *((float *)v1 + 130) = *((float *)v1 + 132);
    *((float *)v1 + 44) = *((float *)v1 + 46);
    *((float *)v1 + 48) = *((float *)v1 + 49);
    result = i + 1;
  }
  return result;
}

