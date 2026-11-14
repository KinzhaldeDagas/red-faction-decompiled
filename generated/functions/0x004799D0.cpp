// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004799D0 rf_liquid_room_transitions_clear
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, liquid transition lifecycle, native x87 unordered comparisons, stable pointer erase, static runtime ownership and level-browser flow): 
// Cdecl no arguments. Iterates dynamic pointer count of global vector6FC46C, raw-deletes each24-byte transition, then releases vector backing storage and zeros count/capacity. Does
// not modify rooms, liquid enable bytes, depths or surfaces; does not destroy room objects. Return register is delegate artifact.
void **rf_liquid_room_transitions_clear()
{
  void **v0; // eax
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(unk_6FC46C); ++i )
  {
    v0 = (void **)sub_552200(unk_6FC46C, i);
    operator delete(*v0);
  }
  return rf_pointer_array_release_storage((void **)unk_6FC46C);
}

