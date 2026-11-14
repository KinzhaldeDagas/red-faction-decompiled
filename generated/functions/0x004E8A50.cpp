// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E8A50 rf_local_fpgun_mark_remote_charge_selected
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player configuration packing/file I/O, fpgun type records and parser ECX/stack ABI): No args. If global local-fpgun player exists, set ONLY its BYTE4164=1; otherwise no writes and EAX not initialized. On write EAX=global player pointer, not boolean. Weapon-switch caller invokes after requested weapon resolves to remote charge; function always targets GLOBAL player, not the caller weapon-switch player argument. Paired with match reset byte4164=0 and6D70 fallback to detonator when zero; no weapon/ammo/ownership check inside this setter.
int rf_local_fpgun_mark_remote_charge_selected()
{
  int result; // eax

  if ( rf_local_fpgun_player )
  {
    result = rf_local_fpgun_player;
    *(_BYTE *)(rf_local_fpgun_player + 4164) = 1;
  }
  return result;
}

