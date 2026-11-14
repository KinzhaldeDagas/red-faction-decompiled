// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00494950 rf_multiplayer_apply_sound_payload52
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet12/50/51/52/53/54 registry, sound/score/glass layouts, chat routing, RCON source admission and
// native string bounds): Recovered494950..494A07,lastRET494A06; compiled descriptor52 sound. Cdecl payload, source extra word ignored; no length or own runtime/authority/source
// guard. Payload14 bytes: eventWORD0,position binary32 XYZ2/6/10. Native MOVSX sign-extends event16 to32 before positional sound(event,position,1.0,global17F10B0,0); coordinates pass
// through x87 FLD/FSTP. No event range, finite coordinate, distance or duplicate checks here. Nearby server sender494A10 supplies identical14-byte payload/17-byte unreliable envelope
// and filters recipients by radius; receiver does not repeat audience selection. Callback result ignored.
void __cdecl rf_multiplayer_apply_sound_payload52(const unsigned __int8 *payload)
{
  float v1[3]; // [esp+Ch] [ebp-14h] BYREF
  int v2; // [esp+18h] [ebp-8h]
  __int16 v3; // [esp+1Ch] [ebp-4h]

  v2 = 0;
  rf_vector3_default_construct_noop(v1);
  v3 = *(_WORD *)&payload[v2];
  v2 += 2;
  v1[0] = *(float *)&payload[v2];
  v2 += 4;
  v1[1] = *(float *)&payload[v2];
  v2 += 4;
  v1[2] = *(float *)&payload[v2];
  v2 += 4;
  rf_gamesound_play_positional_event(v3, v1, 1.0, (int)&unk_17F10B0, 0);
}

