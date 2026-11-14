// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EF770 sub_4EF770
// UNREALRED VERIFIED [combat-ammo-undercover-gate-20261111]: Getter returns shared87FC01 UNDERCOVER activebyte. Fresh xrefs/producers:4EF150 resets0;4EF180 replacement-player enter sets1LAST;4EF4D0 exit clears0FIRST. Pickup474E90/4750C0 restrictnon-handgun receivingWEAPONIDs whenbyte==1; not an ammoordinal/weapon-type/authority predicate. Current host lacks positive undercover replacement producer, so complete positive-mode pickup policy remains explicit mission dependency. Separate SP difficulty ammo-scale table661294 contains F32(1.5,0.9,0.8,0.6) by exact16originalPEbytes; MP/split pickup skips thatscaling.
unsigned __int8 __cdecl sub_4EF770()
{
  return byte_87FC01[0];
}

