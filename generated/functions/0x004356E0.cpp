// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004356E0 rf_entity_select_fall_movement_descriptor
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, push-region/GeoMod/use-selector/physics batch chains, original float constants and field widths and native
// signed/x87/stack/callback ABI): One cdecl required entity pointer. ORs physics DWORD+424 bit1, queries class contact-geomod flag0x400 predicate, selects movement registry index8 if
// nonzero AL else index3 through445740, writes returned descriptor pointer to entity+2136, then writes ADDRESS7BEB0C to entity+2140. Registry helper may fall back to unloaded slot0,
// so do not guarantee returned descriptor is index3/8 or authored. Native EAX retains descriptor pointer. Does not clear linear/angular velocities, reset timers or dispatch the
// selected movement callback here.
char *__cdecl rf_entity_select_fall_movement_descriptor(_DWORD *a1)
{
  char *result; // eax

  a1[106] |= 1u;
  if ( rf_entity_class_has_contact_geomod_flag400((int)a1) )
    result = sub_445740(8u);
  else
    result = sub_445740(3u);
  a1[534] = result;
  a1[535] = &unk_7BEB0C;
  return result;
}

