// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044C2A0 rf_hud_message_record_construct_color_member_noop
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Thiscall ECX receiver, no stack arguments, returns exact original receiver bits in EAX. Calls571990 with ECX=receiver+256, then
// restores original receiver for return. Shared RGBA default constructor is verified NO-OP, so this body writes NO bytes of receiver storage: message text, packed color, duration and
// other fields remain as supplied. No allocation, zeroing, white-color initialization, NULL/size guard, vtable assignment or resource ownership change. The compiler stack-local
// receiver save is not a record-field write.
int __thiscall rf_hud_message_record_construct_color_member_noop(int this)
{
  rf_rgba8_default_construct_noop((void *)(this + 256));
  return this;
}

