// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00490A00 rf_projectile_contact_continue_if_not_done
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Cdecl(contact-point3f*,projectile pointer),normalized full EAX Boolean. Constructs no-op local physics hit record,then calls
// projectile_trace_contact_continue(projectile,point,&DoneBYTE,&RicochetBYTE,localResult). Returns1 only handled result nonzero AND Done==0; short-circuit means Done read only on
// handled path. Ricochet output ignored. Delegate may change projectile remaining distance/position and contact point; wrapper does not interpret local hit fields,apply extra damage
// or test a ricochet requirement.
BOOL __cdecl rf_projectile_contact_continue_if_not_done(float *a1, int a2)
{
  float v3[19]; // [esp+0h] [ebp-50h] BYREF
  char v4; // [esp+4Eh] [ebp-2h] BYREF
  char v5; // [esp+4Fh] [ebp-1h] BYREF

  rf_physics_hit_record_construct_noop((char *)v3);
  return rf_projectile_trace_contact_continue(a2, a1, &v4, &v5, v3) && !v4;
}

