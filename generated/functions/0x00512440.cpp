// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00512440 rf_weapon_record1360_destroy_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weaponflag/accessor provenance,particle descriptors,trails,ricochet/piercing andx87unorderedbranches,original ECX/stack flow and PE bytes): Thiscallweaponrecord1360,no stackargs,void. Normaldestructororder:RFStringsat1344,1316,1272,1256,1228,1208;reverse-destruct3RFStringsstride8at1120;reverse-destruct12recordsstride28at756and3recordsstride28at672 via49FAF0(eachdestroysstring+8then+0);thenRFStrings620,64,40,28,16,8,0. CRT6066BDiteratorstartsbase+count*stride,decrementsbeforecallback;SEHmemberunwindtailsincludedinexistingfunctionchunks. Doesnotfree therecorditself,arraybackingofweaponregistry,weaponcount,integerresourcehandles,liveprojectilesorbitmap/VBMpointees. DirectsourcefieldoffsetsverifiedagainstrawECXadjustments,notmisidentifiedConcurrencySEHlabels. No
// repeated-destruction/ownershipvalidationoutsideRFStringdestructor.
// UNREALRED VERIFIED [combat-native-weapon-layout-20261111]: Fresh disassembly confirms exact owned inline storage:3 state records stride28 at+672;12 action records stride28 at+756;3 RFStrings stride8 at+1120. These are verified physical capacities, NOT checked parser limits. 508990 clears both active counts. Empty first +Action file leaves count0 then Foley write targets+748, within third STATE record sound member, not outside whole WeaponInfo; host lacks that alias consumer until explicitly modeled. Nonempty state/action overflow overwrites adjacent fields.
void __thiscall rf_weapon_record1360_destroy_members(char *this)
{
  rf_string_destroy_buffer(this + 1344);
  rf_string_destroy_buffer(this + 1316);
  rf_string_destroy_buffer(this + 1272);
  rf_string_destroy_buffer(this + 1256);
  rf_string_destroy_buffer(this + 1228);
  rf_string_destroy_buffer(this + 1208);
  `eh vector destructor iterator'(this + 1120, 8u, 3, rf_string_destroy_buffer);
  `eh vector destructor iterator'(this + 756, 0x1Cu, 12, (void (__thiscall *)(void *))rf_two_rfstring_prefix_destroy);
  `eh vector destructor iterator'(this + 672, 0x1Cu, 3, (void (__thiscall *)(void *))rf_two_rfstring_prefix_destroy);
  rf_string_destroy_buffer(this + 620);
  rf_string_destroy_buffer(this + 64);
  rf_string_destroy_buffer(this + 40);
  rf_string_destroy_buffer(this + 28);
  rf_string_destroy_buffer(this + 16);
  rf_string_destroy_buffer(this + 8);
  rf_string_destroy_buffer(this);
}

