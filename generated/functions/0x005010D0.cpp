// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005010D0 rf_event_go_undercover_forward
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_go_undercover forward, vtable0x63E348 slot+4. Pass raw dword event+0x2B8 to0x4EF180. Downstream routine replaces player entity and equipment state; this callback performs no target traversal.
void __thiscall rf_event_go_undercover_forward(int *this)
{
  rf_undercover_enter_replace_player_entity(*(this + 174));
}

