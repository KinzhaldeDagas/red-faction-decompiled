// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044E130 sub_44E130
// UNREALRED VERIFIED [hud-admission-20261027] HUD reset initializes BOTH current ammo-display visibility (0x661888) and target (0x66188C) to float 1.0 via FLD1/FSTP. Caller is the common HUD reset 0x44A980. A newly created/reloaded host HUD starts fully visible; a selected weapon name change is not this reset path.
void sub_44E130()
{
  flt_661888 = 1.0;
  flt_66188C = 1.0;
}

