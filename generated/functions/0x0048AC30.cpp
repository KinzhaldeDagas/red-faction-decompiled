// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048AC30 rf_mover_stop_noop
// UNREALRED VERIFIED [mission-mover-activation-20261013] Empty function in this retail executable. Called by immediate mover stop0x48ABB0 before clearing target index. Does not emit stop audio or change child transforms.
void rf_mover_stop_noop()
{
  ;
}

