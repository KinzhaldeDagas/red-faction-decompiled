// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00476D00 rf_unhide_global_owner_present
// UNREALRED VERIFIED [mission-visibility-20261020] UnHide bypass gate is exactly global owner pointer0x6FB24C !=0. Fresh writers: initialization475FE0 clears it;4768B0 assigns lookup475E80 result;476BF0 clears after restoring player and attached vehicle. Do not substitute UE world pause or a guessed camera-frustum condition.
// UNREALRED VERIFIED [mission-unhide-20261020] Bypass remains pointer0x6FB24C !=0. The current standalone UnrealRed UnHide adapter supplies false because that sequence-owner lifecycle has not been implemented; world pause and hidden camera state are not substituted.
bool rf_unhide_global_owner_present()
{
  return dword_6FB24C != 0;
}

