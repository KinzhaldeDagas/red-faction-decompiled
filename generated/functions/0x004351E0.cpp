// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004351E0 rf_entity_restore_saved_class_motion_and_clear_source
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(required entity,LOWBYTE spawnEffect), incidental RFString-pointer EAX. ONLY spawnEffect==EXACT1 calls
// first-DWORD room getter; nonNULL room calls506E20 VClip spawn with eight slots(global681E24,room,entity COMMON60,SAME COMMON60,FLOAT1,-1,0,BYTE1), result ignored. Every other byte
// skips room/effect. ALWAYS then4356E0(entity): sets physics424bit1 and requests fall descriptor3/8 with context ADDRESS7BEB0C. Ambient source2052!=-1 receives gainFLOAT0, no
// stop/release here; ALWAYS invalidate2052=-1. Then dereference auxiliary record2128 firstFLOAT and overwrite SHARED gameplay class(entity660) FLOAT80; assign literal CString run to
// SHARED class RFString48, return its assignment EAX. Those are class-definition writes, not per-entity speed/name stores. Does NOT reselect descriptor after changing class string,
// free auxiliary record2128, clear its field, or test entity/class/auxiliary NULL. Prefix effects remain if later pointer/string operation fails.
_DWORD *__cdecl rf_entity_restore_saved_class_motion_and_clear_source(int a1, char a2)
{
  int first_dword; // [esp+10h] [ebp-4h]

  if ( a2 == 1 )
  {
    first_dword = rf_receiver_get_first_dword((void *)a1);
    if ( first_dword )
      rf_vclip_spawn_runtime_effect(unk_681E24, first_dword, a1 + 60, a1 + 60, 1.0, -1, 0, 1);
  }
  rf_entity_select_fall_movement_descriptor((_DWORD *)a1);
  if ( *(_DWORD *)(a1 + 2052) != -1 )
    rf_ambient_voice_set_source_gain(*(_DWORD *)(a1 + 2052), 0.0);
  *(_DWORD *)(a1 + 2052) = -1;
  *(float *)(*(_DWORD *)(a1 + 660) + 80) = **(float **)(a1 + 2128);
  return rf_string_assign_from_cstr((_DWORD *)(*(_DWORD *)(a1 + 660) + 48), (char *)off_632F50);
}

