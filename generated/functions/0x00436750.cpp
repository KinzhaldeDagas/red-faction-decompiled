// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00436750 rf_entity_clear_holster_if_mapped_weapon_owned
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(entity), void. NULL or raw entity2064 holsterbit0x800 CLEAR exits. Snapshot primary676 into local; if
// equal global911C88, replace ONLY LOCAL checked index with global911C78, without changing selected weapon. Ownership403D00(AI=entity672,mapped index) must return EXACT AL1; its own
// signed0..63/ownership-byte admission is delegated. On pass clear holsterbit FIRST, then438AC0(entity) ANY nonzero calls4E72C0(entity Player pointer5168) draw request; ignore
// return. Callback failure cannot restore prior bit. Does not call guarded holster predicate436710, change selected index, directly stop/start firing, reset own deadlines or test
// readiness, attachment type, death/authority/player-locality.
void __cdecl rf_entity_clear_holster_if_mapped_weapon_owned(_DWORD *a1)
{
  unsigned int v1; // [esp+0h] [ebp-4h]

  if ( a1 && (a1[516] & 0x800) != 0 )
  {
    v1 = a1[169];
    if ( v1 == unk_911C88 )
      v1 = dword_911C78;
    if ( sub_403D00((int)(a1 + 168), v1) )
    {
      a1[516] &= ~0x800u;
      if ( sub_438AC0((int)a1) )
        rf_fpgun_request_draw_action(a1[1292]);
    }
  }
}

