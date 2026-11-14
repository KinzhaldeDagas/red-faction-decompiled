// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BC5B0 rf_object_contact_response_dispatch
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, object room/attachment ownership, shape-based ground lighting, native dispatcher table and resolver/view distinctions): Cdecl common object pointer. Unsigned type DWORD36 dispatches full eight-entry original jump table:0 entity,1 item,2 projectile,3 physical debris,4 clutter,7 corpse;5/6 and out-of-range (including negative signed values) return EAX0. Each admitted callback receives object in ECX with no stack arguments, and its EAX is propagated unchanged; statuses are not normalized to bool or unified across object kinds. No own null/flag/health/contact guard or follow-up deletion/physics response.
int __cdecl rf_object_contact_response_dispatch(_DWORD *a1)
{
  int result; // eax

  switch ( a1[9] )
  {
    case 0:
      result = rf_entity_contact_effects_and_response_code((int)a1);
      break;
    case 1:
      result = rf_item_contact_try_pickup((int)a1);
      break;
    case 2:
      result = rf_projectile_contact_response_dispatch((int)a1);
      break;
    case 3:
      result = rf_physical_debris_contact_response(a1);
      break;
    case 4:
      result = rf_clutter_contact_response_code((int)a1);
      break;
    case 7:
      result = rf_corpse_update_drop_transition((int)a1);
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

