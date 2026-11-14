// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051ECE0 rf_renderer_get_visible_room_array
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, plane splits,intrusive face lists,room/portal visibility,clip apertures and decal submission,original ECX/stack flow and PE bytes): Cdecl outRooms,outCount caller-pop8. Raw C7 at51ECE6 writes IMMEDIATE ADDRESS0x00940A48 into *outRooms, NOT DWORD contents of first room entry. Then copy signed DWORD countA42074 into *outCount. EAX remains outRooms argument address and is returned. Borrowed global array, not a copied snapshot/allocation; no null or alias guard, no reset. If outputs alias same cell the second count store overwrites address. Projected-shadow dispatcher513ABE treats first output as room-pointer array and iterates count with independent8-work-entry cap.
void ***__cdecl rf_renderer_get_visible_room_array(void ***out_rooms, int *out_count)
{
  *out_rooms = (void **)unk_940A48;
  *out_count = dword_A42074;
  return out_rooms;
}

