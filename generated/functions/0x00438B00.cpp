// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00438B00 sub_438B00
// UNREALRED VERIFIED [combat-particle-vbm-20261104]: VClip-level no_z_check eligibility is438AC0(entity), oruse-vehicle withresolvedoccupant435170 whoseentitypasses438AC0.438AC0 requires commonplayerflag AND nonnull+0x1430. Caller506E20 applies this toBOTH VBM andinline using explicit entityhandle arg_14(a6), not generic graphicowner/instigator. Anonymousliquid/death/clutter routes pass-1. Do not unconditionallydisabledepth for the authored flag.
bool __cdecl sub_438B00(_DWORD *a1)
{
  int v2; // [esp+0h] [ebp-8h]
  int v3; // [esp+4h] [ebp-4h]

  if ( sub_438AC0((int)a1) )
    return 1;
  if ( !rf_object_is_use_vehicle(a1) )
    return 0;
  v3 = sub_435170((int)a1);
  if ( v3 < 0 )
    return 0;
  v2 = rf_entity_resolve_handle(v3);
  return v2 && sub_438AC0(v2);
}

