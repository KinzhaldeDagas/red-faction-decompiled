// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00515E60 rf_room_reset_descending_id_counter
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, room destruction/reconstruction,shared-vertex portal-side voting,detail references and intrusive list edge cases,original ECX/stack flow and PE bytes): Cdecl no arguments,void. Single global DWORD store0x663AF4=0x7FFFFFFF; no calls,room traversal,allocation or record resets. Room constructor515AB0 copies current global into roomDWORD36 then decrements global. Reset does not renumber existing rooms,validate uniqueness,clear room arrays or prevent later wrap.
void rf_room_reset_descending_id_counter()
{
  dword_663AF4 = 0x7FFFFFFF;
}

